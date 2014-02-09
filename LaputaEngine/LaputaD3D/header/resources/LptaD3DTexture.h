#include <string>
#include <d3d9.h>
#include "LptaTexture.h"
using std::string;

namespace lpta_d3d
{

class LptaD3DTexture : public lpta::LptaTexture
{
protected:
    static const unsigned long ERROR_TEXTURE_COLOR = 0xFF7F00FF;
    static const unsigned int ERROR_TEXTURE_WIDTH = 64;
    static const unsigned int ERROR_TEXTURE_HEIGHT = ERROR_TEXTURE_WIDTH;

public:
    LptaD3DTexture(LPDIRECT3DDEVICE9 d3ddev, ID id, const string &filename, 
        float alpha, const COLOR_KEYS &colorKeys);
    ~LptaD3DTexture(void);

private:
    static DATA D3DLoadTextureFile(LPDIRECT3DDEVICE9 d3ddev, const string &filename, bool alpha);
};

}