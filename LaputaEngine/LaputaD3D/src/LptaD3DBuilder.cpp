#include <d3d9.h>
#include <d3dx9.h>
#include "LptaStatusCodes.h"
#include "LptaD3D.h"
#include "LptaD3DConfig.h"
#include "LptaD3DDeviceBuilder.h"

extern "C" __declspec(dllexport) HRESULT CreateDeviceBuilder(HINSTANCE hDll, 
    LPTA_DEVICE_BUILDER *deviceBuilder)
{
    try {
        if (!(*deviceBuilder)) {
            *deviceBuilder = unique_ptr<lpta_d3d::LptaD3DDeviceBuilder>(
                new lpta_d3d::LptaD3DDeviceBuilder(hDll));
            return LPTA_OK;
        }

        return LPTA_FAIL;
    }
    catch (std::exception e) {
        return LPTA_FAIL;
    }
}

namespace lpta_d3d
{
inline bool InitShaderSupport(const LPDIRECT3DDEVICE9 &d3ddev, 
    LPDIRECT3DVERTEXDECLARATION9 *declVertex,
    LPDIRECT3DVERTEXDECLARATION9 *declLitVertex) {

    D3DCAPS9 caps;
    if (FAILED(d3ddev->GetDeviceCaps(&caps))) {
        return false;
    }
    if (caps.VertexShaderVersion < D3DVS_VERSION(1, 1) || 
        caps.PixelShaderVersion < D3DPS_VERSION(1, 1)) {

        return false;
    }
    D3DVERTEXELEMENT9 declVertexElements[] = {
        {0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
        {0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
        {0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
        D3DDECL_END(),
    };
    D3DVERTEXELEMENT9 declLitVertexElements[] = {
        {0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
        {0, 12, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0},
        {0, 16, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
        D3DDECL_END(),
    };
    d3ddev->CreateVertexDeclaration(declVertexElements, declVertex);
    d3ddev->CreateVertexDeclaration(declLitVertexElements, declLitVertex);
    return true;
}

LptaD3DDeviceBuilder::LptaD3DDeviceBuilder(HINSTANCE hDll) : hDll(hDll)
{
}

LptaD3DDeviceBuilder::~LptaD3DDeviceBuilder(void)
{
}

HRESULT LptaD3DDeviceBuilder::Make(HWND hWnd, const vector<HWND> &childWnds, lpta::LPTA_DEVICE *device)
{
    std::unique_ptr<LptaD3D> d3dDevice = std::unique_ptr<LptaD3D>(new LptaD3D(hDll, hWnd, childWnds));
    d3dDevice->d3d = Direct3DCreate9(D3D_SDK_VERSION);
    LPTA_D3D_CONFIG config = LptaD3DConfig::GetConfig(d3dDevice->d3d);
    config->ShowUserDialog(hDll, hWnd);
    D3DPRESENT_PARAMETERS d3dpp = config->GetParameters();
    d3dpp.hDeviceWindow = d3dDevice->renderWindows[0];
    d3dDevice->screenWidth = d3dpp.BackBufferWidth;
    d3dDevice->screenHeight = d3dpp.BackBufferHeight;
    d3dDevice->d3d->CreateDevice(
        config->GetSelectedAdapter(),
        config->GetDeviceType(),
        hWnd,
        D3DCREATE_MIXED_VERTEXPROCESSING,
        &d3dpp,
        &d3dDevice->d3ddev
        );
    SetWindowPos(hWnd, nullptr, -1, -1, d3dDevice->screenWidth, d3dDevice->screenHeight, SWP_NOMOVE);
    
    for (unsigned int i = 0; i < d3dDevice->numWindows; i++) {
        D3DPRESENT_PARAMETERS swapChainPP = d3dpp;
        swapChainPP.hDeviceWindow = d3dDevice->renderWindows[i];
        d3dDevice->d3ddev->CreateAdditionalSwapChain(&swapChainPP, &d3dDevice->chain[i]);
    }

    d3dDevice->isUsingShader = InitShaderSupport(d3dDevice->d3ddev, 
        &d3dDevice->declVertex, &d3dDevice->declLitVertex);
    d3dDevice->d3ddev->SetFVF(0);
    d3dDevice->vertexShaderManager = 
        unique_ptr<LptaD3DVertexShaderManager>(new LptaD3DVertexShaderManager(d3dDevice->d3ddev));

    d3dDevice->pixelShaderManager =
        unique_ptr<LptaD3DPixelShaderManager>(new LptaD3DPixelShaderManager(d3dDevice->d3ddev));

    d3dDevice->RunRenderer();
    *device = std::move(d3dDevice);

    return S_OK;
}

}