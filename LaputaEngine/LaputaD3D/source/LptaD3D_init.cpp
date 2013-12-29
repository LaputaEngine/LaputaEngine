#include <memory>
#include <Windows.h>
#include "LptaRenderDevice.h"
#include "LptaRendererStatusCodes.h"
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

HRESULT LptaD3D::Init(HWND hWnd, const vector<HWND> &childWnds, int minDepth, int minStencil, bool saveLog)
{
	if (childWnds.size() > MAX_3DHWND) {
		numWindows = MAX_3DHWND;
	}
	else {
		numWindows = childWnds.size();
	}
	if (numWindows > 0) {
		for (unsigned int i = 0; i < numWindows; i++) {
			renderWindows[i] = childWnds[i];
		}
	}
	else {
		//TODO: get rid of this nasty hack
		numWindows = 1;
		renderWindows[0] = hWnd;
	}
	mainWindow = hWnd;
	config->ShowUserDialog(dll, hWnd);
	D3DPRESENT_PARAMETERS d3dpp = config->GetParameters();
	d3dpp.hDeviceWindow = renderWindows[0];
	screenWidth = d3dpp.BackBufferWidth;
	screenHeight = d3dpp.BackBufferHeight;
	d3d->CreateDevice(
		config->GetSelectedAdapter(),
		config->GetDeviceType(),
		hWnd,
		D3DCREATE_MIXED_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev
		);
	SetWindowPos(hWnd, NULL, -1, -1, screenWidth, screenHeight, SWP_NOMOVE);
	
	for (unsigned int i = 0; i < numWindows; i++) {
		D3DPRESENT_PARAMETERS swapChainPP = d3dpp;
		swapChainPP.hDeviceWindow = renderWindows[i];
		d3ddev->CreateAdditionalSwapChain(&swapChainPP, &chain[i]);
	}
	RunRenderer();
	return S_OK;
}