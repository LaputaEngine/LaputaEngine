#ifndef _LPTARENDERER_H_
#define _LPTARENDERET_H_

#include <memory>
#include <string>
#include <Windows.h>
#include "LptaRenderDevice.h"

class LptaRenderer
{
public:
	LptaRenderer(HINSTANCE hInst);
	~LptaRenderer(void);

	HRESULT CreateDevice(std::string api);
	void Release(void);
	LPTAFXRENDERER GetDevice(void);
	HINSTANCE GetModele(void);

private:
	std::shared_ptr<LptaRenderDevice> renderDevice;
	HINSTANCE hInst;
	HMODULE dllHandle;
};

#endif