#include <memory>
#include <d3d9.h>
#include <cimage/CImg.h>
#include "resources/errors/TextureD3DFailure.h"
#include "resources/errors/TextureFileNotFound.h"
#include "resources/LptaD3DTexture.h"
using std::shared_ptr;

namespace lpta_d3d
{
// D3DLoadTextureFile
#define RED_CHANNEL 0
#define GREEN_CHANNEL 1
#define BLUE_CHANNEL 2
#define ALPHA_CHANNEL 3
struct Color24Bit
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
};
struct Color32Bit
{
    unsigned char a;
    unsigned char r;
    unsigned char g;
    unsigned char b;
};
inline void CopyCImgToD3DRect24Bit(const cimg_library::CImg<unsigned char> &image, 
    D3DLOCKED_RECT d3dLockedRect);
inline void CopyCImgToD3DRect32Bit(const cimg_library::CImg<unsigned char> &image, 
    D3DLOCKED_RECT d3dLockedRect);

LptaD3DTexture::LptaD3DTexture(LPDIRECT3DDEVICE9 d3ddev, ID id, const string &filename, 
    float alpha, const COLOR_KEYS &colorKeys) : 
    LptaTexture(id, filename, D3DLoadTextureFile(d3ddev, filename, alpha), alpha, colorKeys)
{
}

LptaD3DTexture::~LptaD3DTexture(void)
{
    (std::static_pointer_cast<IDirect3DTexture9>(GetData()))->Release();
}

#define TO_4_BYTE 4
lpta::LptaTexture::DATA LptaD3DTexture::D3DLoadTextureFile(LPDIRECT3DDEVICE9 d3ddev, 
    const string &filename, bool alpha)
{
    using namespace cimg_library;
    try {
        CImg<unsigned char> image(filename.c_str());
        D3DFORMAT format = alpha ? D3DFMT_A8R8G8B8 : D3DFMT_R8G8B8;
        LPDIRECT3DTEXTURE9 textureData = NULL;
        D3DLOCKED_RECT d3dLockedRect;
        HRESULT result = d3ddev->CreateTexture(
            image.width(), image.height(),
            1, 0,
            format,
            D3DPOOL_MANAGED,
            &textureData,
            NULL
        );
        if (FAILED(result)) {
            throw TextureD3DFailure("could not allocate memory for texture");
        }
        result = textureData->LockRect(0, &d3dLockedRect, NULL, 0);
        if (FAILED(result)) {
            textureData->Release();
            throw TextureD3DFailure("could not lock image buffer for copy");
        }
        if (alpha) {
            CopyCImgToD3DRect32Bit(image, d3dLockedRect);
        }
        else {
            CopyCImgToD3DRect24Bit(image, d3dLockedRect);
        }
        textureData->UnlockRect(0);
        return DATA(textureData);
    }
    catch (cimg_library::CImgIOException) {
        throw TextureFileNotFound(filename);
    }
}
#define NUM_BYTES 3
void CopyCImgToD3DRect24Bit(const cimg_library::CImg<unsigned char> &image, 
    D3DLOCKED_RECT d3dLockedRect)
{
    unsigned int colorsPerLine = d3dLockedRect.Pitch / NUM_BYTES;
    Color24Bit *buffer = static_cast<Color24Bit*>(d3dLockedRect.pBits);
    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            Color24Bit color = {
                image(x, y, RED_CHANNEL),
                image(x, y, GREEN_CHANNEL),
                image(x, y, BLUE_CHANNEL),
            };
            buffer[(y * colorsPerLine) + x] = color;
        }
    }
}
void CopyCImgToD3DRect32Bit(const cimg_library::CImg<unsigned char> &image, 
    D3DLOCKED_RECT d3dLockedRect)
{
    bool hasAlphaChannel = image.spectrum() > ALPHA_CHANNEL;
    unsigned int colorsPerLine = d3dLockedRect.Pitch >> 1;
    Color32Bit *buffer = static_cast<Color32Bit*>(d3dLockedRect.pBits);
    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            Color32Bit color = {
                hasAlphaChannel? image(x, y, ALPHA_CHANNEL) : 0x00,
                image(x, y, RED_CHANNEL),
                image(x, y, GREEN_CHANNEL),
                image(x, y, BLUE_CHANNEL),
            };
            buffer[(y * colorsPerLine) + x] = color;
        }
    }
}

}