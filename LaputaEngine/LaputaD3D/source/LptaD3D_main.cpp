#include "resource.h"
#include "LptaD3D.h"
#include "LptaD3DConfig.h"
using std::unique_ptr;
using std::move;

#pragma comment (lib, "d3d9.lib")

LptaD3D::LptaD3D(HINSTANCE dll)
{
	this->dll = dll;
	this->isRunning = false;

	this->d3d = Direct3DCreate9(D3D_SDK_VERSION);
	this->clearColor = lpta_d3d::DEFAULT_CLEAR_COLOR;
	this->isSceneRunning = false;

	config = LptaD3DConfig::GetConfig(this->d3d);
}

LptaD3D::~LptaD3D(void)
{
	config.reset();
	Release();
}

void LptaD3D::Release(void)
{
	if (NULL != d3ddev) {
		d3ddev->Release();
		d3ddev = NULL;
	}
	if (NULL != d3d) {
		d3d->Release();
		d3d = NULL;
	}
	for (unsigned int i = 0; i < numWindows; i++) {
		renderWindows[i] = NULL;
		chain[i]->Release();
		chain[i] = NULL;
	}
	numWindows = 0;
}

bool LptaD3D::IsRunning(void)
{
	return FALSE;
}

HRESULT LptaD3D::BeginRendering(bool clearPixel, bool clearDepth, bool clearStencil)
{
	Clear(clearPixel, clearDepth, clearStencil);
	d3ddev->BeginScene();
	isSceneRunning = true;
	return S_OK;
}

HRESULT LptaD3D::Clear(bool clearPixel, bool clearDepth, bool clearStencil)
{
	DWORD clearFlag = 0;
	if (clearPixel) {
		clearFlag |= D3DCLEAR_TARGET;
	}
	/*if (clearDepth) {
		clearFlag |= D3DCLEAR_ZBUFFER;
	}*/
	/*if (clearStencil) {
		clearFlag |= D3DCLEAR_STENCIL;
	}*/
	if (isSceneRunning) {
		d3ddev->EndScene();
	}
	if (clearFlag != 0) {
		bool failed = false;
		if (FAILED(d3ddev->Clear(0, NULL, clearFlag, clearColor, 1.0f, 0))) {
			failed = true;
		}
	}
	if (isSceneRunning) {
		d3ddev->BeginScene();
	}
	return S_OK;
}

void LptaD3D::EndRendering(void)
{
	d3ddev->EndScene();
	//TODO: get rid of this nasty hack
	//d3ddev->Present(NULL, NULL, NULL, NULL);
	for (unsigned int i = 0; i < numWindows; i++) {
		chain[i]->Present(NULL, NULL, renderWindows[i], NULL, 0);
	}
	isSceneRunning = false;
}

void LptaD3D::SetClearColor(float r, float g, float b)
{
	this->clearColor = D3DCOLOR_COLORVALUE(r, g, b, 1.0f);
}

HRESULT LptaD3D::UseWindow(UINT windowIndex)
{
	if (0 < windowIndex || windowIndex >= numWindows) {
		return S_OK;
	}
	LPDIRECT3DSURFACE9 surf = NULL;
	chain[windowIndex]->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &surf);
	d3ddev->SetRenderTarget(0, surf);
	surf->Release();
	return S_OK;
}

void LptaD3D::RunRenderer(void)
{
	isRunning = true;
	isSceneRunning = false;
}
