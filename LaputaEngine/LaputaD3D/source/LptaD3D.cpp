#include "resource.h"
#include "LptaD3D.h"
#include "LptaD3DConfig.h"
#include "Lpta3D.h"
#include "LptaVector.h"
#include "LptaNormalVector.h"
using lpta_3d::LptaVector;
using lpta_3d::LptaNormalVector;
using std::unique_ptr;
using std::move;

#pragma comment (lib, "d3d9.lib")

namespace lpta_d3d
{

// SetViewLookAt
inline bool IsValidVector(const LptaVector &vector);

LptaD3D::LptaD3D(HINSTANCE dll, HWND hWnd, const vector<HWND> &childWnds) :
    LptaRenderDeviceImpl(dll, hWnd, childWnds)
{
    this->isRunning = false;
    
    this->d3ddev = NULL;
    this->d3d = NULL;
    for (unsigned int i = 0; i < MAX_3DHWND; ++i) {
        chain[i] = NULL;
    }
    
    this->clearColor = lpta_d3d::DEFAULT_CLEAR_COLOR;
    this->isSceneRunning = false;
}

LptaD3D::~LptaD3D(void)
{
    Release();
}

///////////////////////////////////////////////////////////////////////////
// Rendering
/////////////////////////////////////////////////////////////////
void LptaD3D::Release(void)
{
    if (NULL != d3ddev) {
        d3ddev->Release();
        d3ddev = NULL;
    }
    if (NULL != d3d) {
        d3d->Release();
        d3d = NULL;
    }
    for (unsigned int i = 0; i < numWindows; i++) {
        renderWindows[i] = NULL;
        if (NULL != chain[i]) {
            chain[i]->Release();
            chain[i] = NULL;
        }
    }
    numWindows = 0;
    dll = NULL;
}

bool LptaD3D::IsRunning(void)
{
    return FALSE;
}

HRESULT LptaD3D::BeginRendering(bool clearPixel, bool clearDepth, bool clearStencil)
{
    Clear(clearPixel, clearDepth, clearStencil);
    d3ddev->BeginScene();
    isSceneRunning = true;
    return S_OK;
}

HRESULT LptaD3D::Clear(bool clearPixel, bool clearDepth, bool clearStencil)
{
    DWORD clearFlag = 0;
    if (clearPixel) {
        clearFlag |= D3DCLEAR_TARGET;
    }
    /*if (clearDepth) {
        clearFlag |= D3DCLEAR_ZBUFFER;
    }*/
    /*if (clearStencil) {
        clearFlag |= D3DCLEAR_STENCIL;
    }*/
    if (isSceneRunning) {
        d3ddev->EndScene();
    }
    if (clearFlag != 0) {
        bool failed = false;
        if (FAILED(d3ddev->Clear(0, NULL, clearFlag, clearColor, 1.0f, 0))) {
            failed = true;
        }
    }
    if (isSceneRunning) {
        d3ddev->BeginScene();
    }
    return S_OK;
}

void LptaD3D::EndRendering(void)
{
    d3ddev->EndScene();
    //TODO: get rid of this nasty hack
    //d3ddev->Present(NULL, NULL, NULL, NULL);
    for (unsigned int i = 0; i < numWindows; i++) {
        chain[i]->Present(NULL, NULL, renderWindows[i], NULL, 0);
    }
    isSceneRunning = false;
}

void LptaD3D::SetClearColor(float r, float g, float b)
{
    this->clearColor = D3DCOLOR_COLORVALUE(r, g, b, 1.0f);
}

HRESULT LptaD3D::UseWindow(UINT windowIndex)
{
    if (windowIndex < 0 || numWindows <= windowIndex) {
        return S_OK;
    }
    LPDIRECT3DSURFACE9 surf = NULL;
    chain[windowIndex]->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &surf);
    d3ddev->SetRenderTarget(0, surf);
    surf->Release();
    return S_OK;
}

///////////////////////////////////////////////////////////////////////////
// World View Orientation
/////////////////////////////////////////////////////////////////
HRESULT LptaD3D::SetView3D(const lpta_3d::LptaVector &right, const lpta_3d::LptaVector &up, 
    const lpta_3d::LptaVector &dir, 
    const lpta_3d::POINT &point)
{
    if (!IsRunning()) {
        return E_FAIL;
    }
    D3DMATRIX m = {
        right.GetX(),  up.GetX(),  dir.GetX(),  0.0f,
        right.GetY(),  up.GetY(),  dir.GetY(),  0.0f,
        right.GetZ(),  up.GetZ(),  dir.GetZ(),  0.0f,
        right * point, up * point, dir * point, 1.0f,
    };
    view3D = m;

    if (!isUsingShader) {
        HRESULT result = d3ddev->SetTransform(D3DTS_VIEW, &view3D);
        if (FAILED(result)) {
            return result;
        }
    }

    CalcViewProjection();
    CalcWorldViewProjection();
}

HRESULT LptaD3D::SetViewLookAt(const lpta_3d::POINT &point, const lpta_3d::POINT &subject, 
    const lpta_3d::LptaVector &worldUp)
{
    LptaVector dir = subject - point;
    LptaNormalVector normalizedDir = LptaNormalVector::MakeFrom(dir);

    LptaVector up;
    {
        float cosAngle = worldUp * normalizedDir;
        LptaVector temp = normalizedDir * cosAngle;
        up = worldUp - temp;
    }
    if (!IsValidVector(up)) {
        LptaVector temp = normalizedDir * normalizedDir.GetY();
        up = LptaVector(0.0f, 1.0f, 0.0f) - temp;
        if (!IsValidVector(up)) {
            LptaVector temp = normalizedDir * normalizedDir.GetZ();
            up = LptaVector(0.0f, 0.0f, 1.0f) - temp;
            if (!IsValidVector(up)) {
                return E_FAIL;
            }
        }
    }
    LptaNormalVector normalizedUp = LptaNormalVector::MakeFrom(up);
    LptaVector right = normalizedUp.Cross(normalizedDir);
    return SetView3D(right, normalizedUp, normalizedDir, point);
}
bool IsValidVector(const LptaVector& vector)
{
    return fabs(vector.Length()) >= LPTA_EPSILON;
}

void LptaD3D::SetClippingPlanes(float planeNear, float planeFar)
{

}

HRESULT LptaD3D::GetFrustum(lpta_3d::LptaPlane *plane)
{
    return S_OK;
}

void LptaD3D::CalcViewProjection(void)
{
}

void LptaD3D::CalcWorldViewProjection(void)
{
}

void LptaD3D::RunRenderer(void)
{
    isRunning = true;
    isSceneRunning = false;
}

}
