#ifndef _LPTARENDERDEVICE_H_
#define _LPTARENDERDEVICE_H_
#include <memory>
#include <vector>
#include <Windows.h>
using std::vector;

namespace lpta_3d
{

class LptaVector;
typedef LptaVector POINT;
class LptaPlane;
class LptaFrustum;
class LptaRay;
class LptaMatrix;

}

namespace lpta
{

class LptaViewport;

typedef struct CLIPPING_PLANES_TYPE
{
    float planeNear;
    float planeFar;
} CLIPPING_PLANES;

typedef enum RENDER_MODE_TYPE
{
    MODE_PERSPECTIVE,
    MODE_2D,
    MODE_ORTHOGONAL,
} RENDER_MODE;

typedef unsigned int RENDER_STAGE;

const float CLIPPING_PLANE_MIN = 0.01f;
const float CLIPPING_PLANE_MAX = 1.0f;

class LptaRenderDevice
{
public:
    static const unsigned int MAX_STAGES = 4;

public:
    LptaRenderDevice(void) {};
    virtual ~LptaRenderDevice(void) {};

    ///////////////////////////////////////////////////////////////////////////
    // Initialization/Release
    /////////////////////////////////////////////////////////////////
    virtual void Release(void) = 0;
    virtual bool IsRunning(void) = 0;

    ///////////////////////////////////////////////////////////////////////////
    // Rendering
    /////////////////////////////////////////////////////////////////
    virtual HRESULT UseWindow(UINT) = 0;
    virtual HRESULT BeginRendering(bool clearPixel, bool clearDepth, bool clearStencil) = 0;
    virtual void EndRendering(void) = 0;
    virtual HRESULT Clear(bool clearPixel, bool clearDepth, bool clearStencil) = 0;
    virtual void SetClearColor(float r, float g, float b) = 0;

    ///////////////////////////////////////////////////////////////////////////
    // World View Orientation
    /////////////////////////////////////////////////////////////////
    virtual void SetWorldTransform(const lpta_3d::LptaMatrix &world) = 0;
    virtual HRESULT SetView3D(const lpta_3d::LptaVector &right, const lpta_3d::LptaVector &up, 
        const lpta_3d::LptaVector &dir, 
        const lpta_3d::POINT &point) = 0;
    virtual HRESULT SetViewLookAt(const lpta_3d::POINT &point, const lpta_3d::POINT &subject, 
        const lpta_3d::LptaVector &worldUp) = 0;
    virtual void SetClippingPlanes(float planeNear, float planeFar) = 0;

    virtual HRESULT GetFrustum(lpta_3d::LptaFrustum *furstum) = 0;

    ///////////////////////////////////////////////////////////////////////////
    // Internal State Mutator
    /////////////////////////////////////////////////////////////////
    virtual HRESULT SetMode2D(void) = 0;
    virtual HRESULT SetMode3D(RENDER_STAGE stage, RENDER_MODE mode) = 0;
    virtual HRESULT InitStage(float fov, const LptaViewport &viewport, RENDER_STAGE stage) = 0;

    ///////////////////////////////////////////////////////////////////////////
    // Conversions
    /////////////////////////////////////////////////////////////////
    virtual lpta_3d::LptaRay Transform2DTo3D(const lpta_3d::POINT &point2D) = 0;
    virtual lpta_3d::POINT Transform3DTo2D(const lpta_3d::POINT &point3D) = 0;
};

typedef std::unique_ptr<LptaRenderDevice> LPTA_DEVICE;

}

#endif