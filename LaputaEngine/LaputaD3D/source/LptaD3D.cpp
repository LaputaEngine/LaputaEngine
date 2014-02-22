#include "resource.h"
#include "LptaD3D.h"
#include "LptaD3DConfig.h"
#include "Lpta3D.h"
#include "LptaVector.h"
#include "LptaNormalVector.h"
#include "LptaPlane.h"
#include "LptaFrustum.h"
using lpta_3d::LptaVector;
using lpta_3d::LptaNormalVector;
using std::unique_ptr;
using std::move;

#pragma comment (lib, "d3d9.lib")

namespace lpta_d3d
{

// SetViewLookAt
inline bool IsValidVector(const LptaVector &vector);

// GetFrustum
inline lpta_3d::LptaPlane LeftFrustumPlane(const D3DMATRIX &viewProj);
inline lpta_3d::LptaPlane RightFrustumPlane(const D3DMATRIX &viewProj);
inline lpta_3d::LptaPlane TopFrustumPlane(const D3DMATRIX &viewProj);
inline lpta_3d::LptaPlane BottomFrustumPlane(const D3DMATRIX &viewProj);
inline lpta_3d::LptaPlane NearFrustumPlane(const D3DMATRIX &viewProj);
inline lpta_3d::LptaPlane FarFrustumPlane(const D3DMATRIX &viewProj);

// CalcWorldViewProj
inline void SetWorldViewProj(D3DXMATRIX *out, 
    const D3DXMATRIX &world, const D3DXMATRIX &view, const D3DXMATRIX &proj);

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
    return S_OK;
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
    lpta::CLIPPING_PLANES clipPlanes = {
        fmax(planeNear, lpta::CLIPPING_PLANE_MIN),
        fmin(planeFar, lpta::CLIPPING_PLANE_MAX)
    };
    if (clipPlanes.planeNear >= clipPlanes.planeFar) {
        return;
    }
    this->clippingPlanes = clipPlanes;

    Adjust2D();

    float Q = 1.0f / (clippingPlanes.planeFar - clippingPlanes.planeNear);
    float X = -Q * clippingPlanes.planeNear;
    for (D3DMATRIX &m : orthogonals) {
        m._33 = Q;
        m._43 = X;
    }

    Q *= clippingPlanes.planeFar;
    X = -Q * clippingPlanes.planeNear;
    for (D3DMATRIX &m : perspectives) {
        m._33 = Q;
        m._43 = X;
    }
}

HRESULT LptaD3D::GetFrustum(lpta_3d::LptaFrustum *frustum)
{
    *frustum = lpta_3d::LptaFrustum(
        LeftFrustumPlane(viewProj), RightFrustumPlane(viewProj),
        TopFrustumPlane(viewProj), BottomFrustumPlane(viewProj),
        NearFrustumPlane(viewProj), FarFrustumPlane(viewProj)
    );
    return S_OK;
}
lpta_3d::LptaPlane LeftFrustumPlane(const D3DMATRIX &viewProj)
{
    LptaVector direction(
        -(viewProj._14 + viewProj._11),
        -(viewProj._24 + viewProj._21),
        -(viewProj._34 + viewProj._31));
    float distance = -(viewProj._44 + viewProj._41) / direction.Length();
    return lpta_3d::LptaPlane(LptaNormalVector::MakeFrom(direction), distance);
}
lpta_3d::LptaPlane RightFrustumPlane(const D3DMATRIX &viewProj)
{
    LptaVector direction(
        -(viewProj._14 - viewProj._11),
        -(viewProj._24 - viewProj._21),
        -(viewProj._34 - viewProj._31));
    float distance = -(viewProj._44 - viewProj._41) / direction.Length();
    return lpta_3d::LptaPlane(LptaNormalVector::MakeFrom(direction), distance);
}
lpta_3d::LptaPlane TopFrustumPlane(const D3DMATRIX &viewProj)
{
    LptaVector direction(
        -(viewProj._14 - viewProj._12),
        -(viewProj._24 - viewProj._22),
        -(viewProj._34 - viewProj._32));
    float distance = -(viewProj._44 - viewProj._42) / direction.Length();
    return lpta_3d::LptaPlane(LptaNormalVector::MakeFrom(direction), distance);
}
lpta_3d::LptaPlane BottomFrustumPlane(const D3DMATRIX &viewProj)
{
    LptaVector direction(
        -(viewProj._14 + viewProj._12),
        -(viewProj._24 + viewProj._22),
        -(viewProj._34 + viewProj._32));
    float distance = -(viewProj._44 + viewProj._42);
    return lpta_3d::LptaPlane(LptaNormalVector::MakeFrom(direction), distance);
}
lpta_3d::LptaPlane NearFrustumPlane(const D3DMATRIX &viewProj)
{
    LptaVector direction(
        -viewProj._13,
        -viewProj._23,
        -viewProj._33);
    float distance = -viewProj._43 / direction.Length();
    return lpta_3d::LptaPlane(LptaNormalVector::MakeFrom(direction), distance);
}
lpta_3d::LptaPlane FarFrustumPlane(const D3DMATRIX &viewProj)
{
    LptaVector direction(
        -(viewProj._14 - viewProj._13),
        -(viewProj._24 - viewProj._23),
        -(viewProj._34 - viewProj._33));
    float distance = -(viewProj._44 - viewProj._43) / direction.Length();
    return lpta_3d::LptaPlane(LptaNormalVector::MakeFrom(direction), distance);
}

void LptaD3D::Adjust2D(void)
{
    AdjustProj2D();
    AdjustView2D();
}
void LptaD3D::AdjustProj2D(void)
{
    memset(&proj2D, 0, sizeof(D3DMATRIX));
    float clippingPlaneDist = clippingPlanes.planeFar - clippingPlanes.planeNear;
    proj2D._11 = 2.0f / (float)this->screenWidth;
    proj2D._22 = 2.0f / (float)this->screenHeight;
    proj2D._33 = 1.0f / (clippingPlaneDist);
    proj2D._43 = -clippingPlanes.planeFar * (1.0f / clippingPlaneDist);
    proj2D._44 = 1.0f;
}
void LptaD3D::AdjustView2D(void)
{
    memset(&view2D, 0, sizeof(D3DMATRIX));
    view2D._11 = view2D._33 = view2D._44 = 1.0f;

    float tx = (float)(-((int)screenWidth) + screenWidth * 0.5);
    float ty = screenWidth - screenHeight * 0.5f;
    float tz = clippingPlanes.planeNear + 0.1f;

    view2D._22 = -1.0f;
    view2D._41 = tx;
    view2D._42 = ty;
    view2D._43 = tz;
}

HRESULT LptaD3D::CalcPerspViewProjection(float fov, float aspectRatio, D3DMATRIX *m)
{
    if (fabs(clippingPlanes.planeFar - clippingPlanes.planeNear) < lpta::CLIPPING_PLANE_MIN) {
        return E_FAIL;
    }
    float sinFov = sinf(fov / 2);
    if (sinFov < lpta::CLIPPING_PLANE_MIN) {
        return E_FAIL;
    }float cosFov = cosf(fov / 2);

    float w = aspectRatio * (cosFov / sinFov);
    float h = 1.0f * (cosFov / sinFov);
    float Q = clippingPlanes.planeFar / (clippingPlanes.planeFar - clippingPlanes.planeNear);

    memset(m, 0, sizeof(D3DMATRIX));
    m->_11 = w;
    m->_22 = h;
    m->_33 = Q;
    m->_34 = 1.0f;
    m->_43 = -Q * clippingPlanes.planeNear;
    return S_OK;
}

void LptaD3D::CalcViewProjection(void)
{
    switch (mode) {
    case lpta::MODE_2D:
        D3DXMatrixMultiply(&viewProj, &proj2D, &view2D);
        break;
    case lpta::MODE_PERSPECTIVE:
        D3DXMatrixMultiply(&viewProj, &perspectives.at(stage), &view3D);
        break;
    case lpta::MODE_ORTHOGONAL:
        D3DXMatrixMultiply(&viewProj, &orthogonals.at(stage), &view3D);
        break;
    default:
        // log error
        ;
    }
}

void LptaD3D::CalcWorldViewProjection(void)
{
    switch (mode) {
    case lpta::MODE_2D:
        SetWorldViewProj(&worldViewProjection, world, view2D, proj2D);
        break;
    case lpta::MODE_PERSPECTIVE:
        SetWorldViewProj(&worldViewProjection, world, view3D, perspectives.at(stage));
        break;
    case lpta::MODE_ORTHOGONAL:
        SetWorldViewProj(&worldViewProjection, world, view3D, orthogonals.at(stage));
        break;
    default:
        // log error
        ;
    }
}
inline void SetWorldViewProj(D3DXMATRIX *out, 
    const D3DXMATRIX &world, const D3DXMATRIX &view, const D3DXMATRIX &proj)
{
    // out = (world * view) * proj
    D3DXMatrixMultiply(out, &world, &view);
    D3DXMatrixMultiply(out, out, &proj);
}

void LptaD3D::RunRenderer(void)
{
    isRunning = true;
    isSceneRunning = false;
}

}
