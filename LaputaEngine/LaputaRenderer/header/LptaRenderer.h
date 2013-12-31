#ifndef _LPTARENDERER_H_
#define _LPTARENDERET_H_

#include <memory>
#include <string>
#include <Windows.h>
#include "LptaStatusCodes.h"
#include "LptaRenderDevice.h"

class LptaRenderer
{
public:
    LptaRenderer(HINSTANCE hInst);
    ~LptaRenderer(void);

    LPTA_RESULT CreateDevice(std::string api);
    void Release(void);
    LPTAFXRENDERER GetDevice(void);

private:
    std::shared_ptr<LptaRenderDevice> renderDevice;
    HINSTANCE hInst;
    HMODULE dllHandle;
};

#endif