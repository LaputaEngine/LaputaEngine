#include <memory>
#include <Windows.h>
#include "LptaRenderDevice.h"
#include "LptaRendererStatus.h"
#include "LptaD3D.h"
using std::shared_ptr;

HRESULT CreateRenderDevice(HINSTANCE dll, LPTAFXRENDERER& pInterface)
{
	if (!pInterface) {
		pInterface = shared_ptr<LptaD3D>(new LptaD3D(dll));
		return LPTA_OK;
	}

	return LPTA_FAIL;
}

HRESULT ReleaseRenderDevice(LPTAFXRENDERER& pInterface)
{
	if (!pInterface) {
		return LPTA_FAIL;
	}

	pInterface.reset();
	return LPTA_OK;
}