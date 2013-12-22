#include <memory>
#include <Windows.h>
#include "LptaRenderDevice.h"
#include "LptaRendererStatus.h"
#include "LptaD3D.h"
using std::shared_ptr;

extern "C" __declspec(dllexport) HRESULT CreateRenderDevice(HINSTANCE dll, LPTAFXRENDERER& pInterface)
{
	if (!pInterface) {
		pInterface = shared_ptr<LptaD3D>(new LptaD3D(dll));
		return LPTA_OK;
	}

	return LPTA_FAIL;
}

extern "C" __declspec(dllexport)HRESULT ReleaseRenderDevice(LPTAFXRENDERER& pInterface)
{
	if (!pInterface) {
		return LPTA_FAIL;
	}

	pInterface.reset();
	return LPTA_OK;
}

HRESULT LptaD3D::Init(HWND hWnd, const std::shared_ptr<HWND> h3DWnd, int mindDepth, int minStencil, bool saveLog)
{
	config->ShowUserDialog(dll, hWnd);
	D3DPRESENT_PARAMETERS d3dpp = config->GetParameters();
	d3dpp.hDeviceWindow = hWnd;
	d3d->CreateDevice(
		config->GetSelectedAdapter(),
		config->GetDeviceType(),
		hWnd,
		D3DCREATE_MIXED_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev
		);
	SetWindowPos(hWnd, NULL, -1, -1, d3dpp.BackBufferWidth, d3dpp.BackBufferHeight, SWP_NOMOVE);
	return S_OK;
}