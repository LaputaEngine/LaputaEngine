#ifndef _LPTARENDERDEVICEIMPL_H_
#define _LPTARENDERDEVICEIMPL_H_

#include <array>
#include <string>
#include <memory>
#include "LptaViewport.h"
#include "LptaRenderDevice.h"
#include "LptaSkinManager.h"
using std::unique_ptr;

namespace lpta
{

#define MAX_3DHWND 8

class LptaRenderDeviceImpl : public LptaRenderDevice
{
protected:
    LptaRenderDeviceImpl(HINSTANCE hDll, HWND hWnd, const vector<HWND> &childWnds);

protected:
    HWND mainWindow;
    HWND renderWindows[MAX_3DHWND];
    unsigned int numWindows;
    unsigned int numActiveWindows;
    HINSTANCE dll;
    DWORD screenWidth;
    DWORD screenHeight;
    bool isWindows;
    std::string adapterName;
    FILE *logFile;
    bool isRunning;

    unique_ptr<lpta::LptaSkinManager> skinManager;

private:
    RENDER_MODE mode;
    CLIPPING_PLANES clippingPlanes;
    std::array<LptaViewport, MAX_STAGES> viewports;
    RENDER_STAGE stage;
};

}

#endif