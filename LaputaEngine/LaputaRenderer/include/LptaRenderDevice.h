#ifndef _LPTARENDERDEVICE_H_
#define _LPTARENDERDEVICE_H_
#include <memory>
#include <vector>
#include <Windows.h>
#include "LptaResource.h"
#include "renderer/RenderStates.h"
#include "vertices/LptaVertices.h"
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

class LptaMesh;

class LptaVertexCache;
class LptaSkinManager;
class LptaTextureManager;
class LptaMaterialManager;

class LptaViewport;
class LptaColor;

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
typedef LptaResource::ID VERTEX_SHADER_ID;
typedef LptaResource::ID PIXEL_SHADER_ID;

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
    // Manager Accessors
    ///////////////////////////////////////////////////////
    virtual LptaVertexCache *GetVertexCache(void) const = 0;
    virtual LptaSkinManager *GetSkinManager(void) const = 0;
    virtual LptaMaterialManager *GetMaterialManager(void) const = 0;
    virtual LptaTextureManager *GetTextureManager(void) const = 0;

    ///////////////////////////////////////////////////////////////////////////
    // Shader Configuring
    /////////////////////////////////////////////////////////////////
    virtual VERTEX_SHADER_ID AddVertexShader(const std::string &program) = 0;
    virtual HRESULT ActivateVertexShader(VERTEX_SHADER_ID shaderId, VERTEX_TYPE vertexType) = 0;

    virtual PIXEL_SHADER_ID AddPixelShader(const std::string &program) = 0;
    virtual HRESULT ActivatePixelShader(PIXEL_SHADER_ID shaderId) = 0;
 
    ///////////////////////////////////////////////////////////////////////////
    // Rendering
    /////////////////////////////////////////////////////////////////
    virtual HRESULT UseWindow(UINT) = 0;
    virtual bool Cache(LptaMesh &mesh) = 0;
    virtual HRESULT BeginRendering(bool clearPixel, bool clearDepth, bool clearStencil) = 0;
    virtual HRESULT Render(const LptaMesh &mesh) = 0;
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

    virtual void SetCullingMode(RENDER_CULL_MODE cullMode) = 0;
    virtual void SetZBufferMode(RENDER_DEPTH_MODE depthMode) = 0;
    virtual void SetShadeMode(RENDER_SHADE_MODE shadeMode, const LptaColor &wireColor) = 0;
    virtual void SetShadeMode(RENDER_SHADE_MODE shadeMode) = 0;
    virtual void SetPointMode(RENDER_POINT_MODE pointMode) = 0;
    virtual void SetPointMode(RENDER_POINT_MODE pointMode, float pointSize) = 0;

    ///////////////////////////////////////////////////////////////////////////
    // Conversions
    /////////////////////////////////////////////////////////////////
    virtual lpta_3d::LptaRay Transform2DTo3D(const lpta_3d::POINT &point2D) = 0;
    virtual lpta_3d::POINT Transform3DTo2D(const lpta_3d::POINT &point3D) = 0;

    ///////////////////////////////////////////////////////////////////////////
    // Lighting
    /////////////////////////////////////////////////////////////////
    virtual void SetAmbientLight(float r, float g, float b) = 0; 
};

typedef std::unique_ptr<LptaRenderDevice> LPTA_DEVICE;

}

#endif