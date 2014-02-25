#ifndef _LPTAD3D_H_
#define _LPTAD3D_H_

#include <d3dx9.h>
#include "LptaMaterialManager.h"
#include "LptaSkinManager.h"
#include "LptaMaterialManager.h"
#include "resources/LptaD3DTextureManager.h"
#include "resources/LptaD3DVertexShaderManager.h"
#include "resources/LptaD3DPixelShaderManager.h"
#include "LptaD3DConfig.h"
#include "LptaRenderDeviceImpl.h"
using std::unique_ptr;

namespace lpta_d3d
{
const int MIN_WIDTH = 800;
const int MIN_HEIGHT = 600;
const int MIN_BITS = 16;

const D3DFORMAT RENDER_FORMAT = D3DFMT_X8R8G8B8;

const D3DDEVTYPE DEVICE_TYPES[] = {
    D3DDEVTYPE_HAL,
    D3DDEVTYPE_REF,
};
const int NUM_DEVICE_TYPES = sizeof(DEVICE_TYPES) / sizeof(D3DDEVTYPE);

const D3DCOLOR DEFAULT_CLEAR_COLOR = D3DCOLOR_COLORVALUE(0.0f, 0.0f, 0.0f, 1.0f);

class LptaD3D : public lpta::LptaRenderDeviceImpl
{
public:
    LptaD3D(HINSTANCE hDLL, HWND hWnd, const vector<HWND> &childWnds);
    ~LptaD3D(void);

    ///////////////////////////////////////////////////////////////////////////
    // Shader Configuring
    /////////////////////////////////////////////////////////////////
    virtual HRESULT LoadShader(void *data);
    virtual HRESULT LoadShaderFromFile(const std::string &filename);
    virtual HRESULT LoadAndCompileShader(std::string shader);
    virtual HRESULT LoadAndCompileShaderFromFile(const std::string &filename);
 
    ///////////////////////////////////////////////////////////////////////////
    // Rendering
    /////////////////////////////////////////////////////////////////
    void Release(void);
    bool IsRunning(void);
    HRESULT BeginRendering(bool clearPixel, bool clearDepth, bool clearStencil);
    HRESULT Clear(bool clearPixel, bool clearDepth, bool clearStencil);
    void EndRendering(void);
    void SetClearColor(float r, float g, float b);
    HRESULT UseWindow(UINT nWindow);

    ///////////////////////////////////////////////////////////////////////////
    // World View Orientation
    /////////////////////////////////////////////////////////////////
    virtual void SetWorldTransform(const lpta_3d::LptaMatrix &world);
    virtual HRESULT SetView3D(const lpta_3d::LptaVector &right, const lpta_3d::LptaVector &up, 
        const lpta_3d::LptaVector &dir, 
        const lpta_3d::POINT &point);
    virtual HRESULT SetViewLookAt(const lpta_3d::POINT &point, const lpta_3d::POINT &subject, 
        const lpta_3d::LptaVector &worldUp);
    virtual void SetClippingPlanes(float planeNear, float planeFar);

    virtual HRESULT GetFrustum(lpta_3d::LptaFrustum *frustum);

    ///////////////////////////////////////////////////////////////////////////
    // Internal State Mutator
    /////////////////////////////////////////////////////////////////
    virtual HRESULT SetMode2D(void);
    virtual HRESULT SetMode3D(lpta::RENDER_STAGE stage, lpta::RENDER_MODE mode);
    virtual HRESULT InitStage(float fov, const lpta::LptaViewport &viewport, 
        lpta::RENDER_STAGE stage);

    ///////////////////////////////////////////////////////////////////////////
    // Conversions
    /////////////////////////////////////////////////////////////////
    virtual lpta_3d::LptaRay Transform2DTo3D(const lpta_3d::POINT &point2D);
    virtual lpta_3d::POINT Transform3DTo2D(const lpta_3d::POINT &point3D);

private:
    // SetMode Helper
    HRESULT SetModeWithShader(lpta::RENDER_STAGE stage, lpta::RENDER_MODE mode);
    HRESULT SetModeWithoutShader(lpta::RENDER_STAGE stage, lpta::RENDER_MODE mode);
    //
    void Adjust2D(void);
    void AdjustProj2D(void);
    void AdjustView2D(void);
    // todo: cleanup, this is unlike the others, refactor once we know more of where it's used
    HRESULT CalcPerspProjection(float fov, float aspectRatio, D3DXMATRIX *m);
    void CalcViewProjection(void);
    void CalcWorldViewProjection(void);
    void RunRenderer(void);

    LPDIRECT3D9 d3d;
    LPDIRECT3DDEVICE9 d3ddev;
    LPDIRECT3DSWAPCHAIN9 chain[MAX_3DHWND];

    LPDIRECT3DVERTEXDECLARATION9 declVertex;
    LPDIRECT3DVERTEXDECLARATION9 declLitVertex;

    unique_ptr<LptaD3DVertexShaderManager> vertexShaderManager;
    unique_ptr<LptaD3DPixelShaderManager> pixelShaderManager;

    D3DCOLOR clearColor;
    bool isSceneRunning;
    bool isUsingShader;

    D3DXMATRIX view2D;
    D3DXMATRIX view3D;
    D3DXMATRIX proj2D;
    std::array<D3DXMATRIX, MAX_STAGES> perspectives;
    std::array<D3DXMATRIX, MAX_STAGES> orthogonals;
    D3DXMATRIX world;
    D3DXMATRIX viewProj;
    D3DXMATRIX worldViewProjection;

    void Log(char *, ...);

    friend class LptaD3DDeviceBuilder;
};

}

#endif