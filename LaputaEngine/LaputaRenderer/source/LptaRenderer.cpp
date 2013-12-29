#include <sstream>
#include "LptaRendererStatusCodes.h"
#include "LptaRenderer.h"

LptaRenderer::LptaRenderer(HINSTANCE hInst)
{
	this->hInst = hInst;
	this->renderDevice = NULL;
	this->dllHandle = NULL;
}

LptaRenderer::~LptaRenderer(void)
{
	Release();
	if (dllHandle) {
		FreeLibrary(dllHandle);
		dllHandle = NULL;
	}
}

LPTA_RESULT LptaRenderer::CreateDevice(std::string api)
{
	if (api == "Direct3D") {
		dllHandle = LoadLibrary(L"LaputaD3D.dll");
		if (!dllHandle) {
			MessageBox(NULL, L"Loading LaputaD3D.dll failed.", L"LaputaEngine - error", 
					   MB_OK | MB_ICONERROR);
			return LPTA_RDR_FAIL;
		}
	}
	else {
		std::wstringstream ss;
		ss << "API " << api.c_str() << " not supported";
		MessageBox(NULL, ss.str().c_str(), L"LaputaEngine - error",
				   MB_OK | MB_ICONERROR);
		return LPTA_RDR_FAIL;
	}
	
	CREATERENDERDEVICE _CreateRenderDevice = 0;
	HRESULT hr;

	_CreateRenderDevice = (CREATERENDERDEVICE)GetProcAddress(dllHandle, "CreateRenderDevice");
	
	if (!_CreateRenderDevice) {
		LPVOID errorMessage;
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			GetLastError(),
			0, // Default language
			(LPWSTR) &errorMessage,
			0,
			NULL
			);
		MessageBox(NULL, (LPWSTR) errorMessage, L"LaputaEngine - error", MB_OK | MB_ICONERROR);
		return LPTA_RDR_FAIL;
	}

	hr = _CreateRenderDevice(dllHandle, renderDevice);
	if (FAILED(hr)) {
		MessageBox(NULL, L"CreateRenderDevice() from lib failed.", L"LaputaEngine - error", MB_OK | MB_ICONERROR);
		renderDevice = NULL;
		return LPTA_RDR_FAIL;
	}
	return LPTA_OK;
}

LPTAFXRENDERER LptaRenderer::GetDevice(void)
{
	return renderDevice;
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
		renderDevice = NULL;
	}
}