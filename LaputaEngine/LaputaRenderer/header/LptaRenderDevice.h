#ifndef _LPTARENDERDEVICE_H_
#define _LPTARENDERDEVICE_H_
#include <memory>
#include <vector>
#include <Windows.h>
using std::vector;

class LptaRenderDevice
{
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
};

typedef std::unique_ptr<LptaRenderDevice> LPTA_DEVICE;

#endif