#include "LptaRenderer.h"
#include <sstream>

LptaRenderer::LptaRenderer(HINSTANCE hInst)
{
	this->hInst = hInst;
	this->renderDevice = NULL;
	this->dllHandle = NULL;
}

LptaRenderer::~LptaRenderer(void)
{
	Release();
}

HRESULT LptaRenderer::CreateDevice(std::string api)
{
	if (api == "Direct3D") {
		dllHandle = LoadLibrary(L"LaputaD3D.dll");
		if (!dllHandle) {
			MessageBox(NULL, L"Loading LaputaD3D.dll failed.", L"LaputaEngine - error", 
					   MB_OK | MB_ICONERROR);
			return E_FAIL;
		}
	}
	else {
		std::wstringstream ss;
		ss << "API " << api.c_str() << " not supported";
		MessageBox(NULL, ss.str().c_str(), L"LaputaEngine - error",
				   MB_OK | MB_ICONERROR);
		return E_FAIL;
	}

	CREATERENDERDEVICE _CreateRenderDevice = 0;
	HRESULT hr;

	_CreateRenderDevice = (CREATERENDERDEVICE)GetProcAddress(dllHandle, "CreateRenderDevice");

	if (!_CreateRenderDevice) {
		return E_FAIL;
	}

	hr = _CreateRenderDevice(dllHandle, renderDevice);
	if (FAILED(hr)) {
		MessageBox(NULL, L"CreateRenderDevice() from lib failed.", L"LaputaEngine - error", MB_OK | MB_ICONERROR);
		renderDevice = NULL;
		return E_FAIL;
	}

	return S_OK;
}

void LptaRenderer::Release(void)
{
	RELEASERENDERDEVICE _ReleaseRenderDevice = 0;
	HRESULT hr;

	if (dllHandle) {
		_ReleaseRenderDevice = (RELEASERENDERDEVICE)GetProcAddress(dllHandle, "ReleaseRenderDevice");
	}
	if (renderDevice) {
		hr = _ReleaseRenderDevice(renderDevice);
		if (FAILED(hr)) {
			renderDevice = NULL;
		}
	}
}