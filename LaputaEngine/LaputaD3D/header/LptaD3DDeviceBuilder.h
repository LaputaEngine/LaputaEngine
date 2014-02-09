#ifndef _LPTAD3DDEVICEBUILDER_H_
#define _LPTAD3DDEVICEBUILDER_H_

#include <Windows.h>
#include <vector>
#include "LptaDeviceBuilder.h"
using std::vector;

namespace lpta_d3d
{

class LptaD3DDeviceBuilder : public lpta::LptaDeviceBuilder
{
public:
    LptaD3DDeviceBuilder(HINSTANCE hDll);
    ~LptaD3DDeviceBuilder(void);

    virtual HRESULT Make(HWND hWnd, const vector<HWND> &childWnds, LPTA_DEVICE *device);
private:
    HINSTANCE hDll;

    unsigned int minDepth = 16;
    unsigned int minStencil = 0;
    bool saveLog = false;
};

}

#endif