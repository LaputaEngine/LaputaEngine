#ifndef _LPTADEVICEBUILDER_H_
#define _LPTADEVICEBUILDER_H_

#include <memory>
#include <vector>
#include <Windows.h>
#include "LptaRenderDevice.h"
using std::unique_ptr;
using std::vector;

namespace lpta
{

class LptaDeviceBuilder
{
public:
    virtual HRESULT Make(HWND hWnd, const vector<HWND> &childWnds, LPTA_DEVICE *device) = 0;
};

}

typedef unique_ptr<lpta::LptaDeviceBuilder> LPTA_DEVICE_BUILDER;
extern "C"
{
    typedef HRESULT(*CREATEDEVICEBUILDER) (HINSTANCE hDLL, LPTA_DEVICE_BUILDER *deviceBuilder);
}

#endif