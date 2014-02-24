#include <Windows.h>
#include "LptaRenderDeviceImpl.h"

namespace lpta
{

LptaRenderDeviceImpl::LptaRenderDeviceImpl(HINSTANCE hDll, HWND hWnd, const vector<HWND> &childWnds) :
    mainWindow(hWnd), dll(hDll)

{
    numWindows = min(childWnds.size(), MAX_3DHWND);
    if (numWindows > 0) {
        for (unsigned int i = 0; i < numWindows; ++i) {
            renderWindows[i] = childWnds[i];
        }
    }
    else {
        numWindows = 1;
        renderWindows[0] = hWnd;
    }
    mainWindow = hWnd;
}

}