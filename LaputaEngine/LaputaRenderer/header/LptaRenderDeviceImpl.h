#ifndef _LPTARENDERDEVICEIMPL_H_
#define _LPTARENDERDEVICEIMPL_H_

#include "LptaRenderDevice.h"

#define MAX_3DHWND 8

class LptaRenderDeviceImpl : public LptaRenderDevice
{
protected:
	HWND mainWindow;
	HWND renderWindows[MAX_3DHWND];
	UINT numWindows;
	UINT numActiveWindows;
	HINSTANCE dll;
	DWORD screenWidth;
	DWORD screenHeight;
	bool isWindows;
	string adapterName;
	FILE *logFile;
	bool isRunning;
};

#endif