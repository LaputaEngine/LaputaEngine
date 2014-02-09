#ifndef _LPTARENDERDEVICEIMPL_H_
#define _LPTARENDERDEVICEIMPL_H_

#include "memory"
#include "LptaRenderDevice.h"
#include "LptaSkinManager.h"
using std::unique_ptr;

#define MAX_3DHWND 8

class LptaRenderDeviceImpl : public LptaRenderDevice
{
protected:
    HWND mainWindow;
    HWND renderWindows[MAX_3DHWND];
    unsigned int numWindows;
    unsigned int numActiveWindows;
    HINSTANCE dll;
    DWORD screenWidth;
    DWORD screenHeight;
    bool isWindows;
    string adapterName;
    FILE *logFile;
    bool isRunning;

    unique_ptr<lpta::LptaSkinManager> skinManager;
};

#endif