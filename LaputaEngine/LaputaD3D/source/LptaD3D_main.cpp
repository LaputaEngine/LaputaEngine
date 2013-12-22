#include "resource.h"
#include "LptaD3D.h"
#include "LptaD3DConfig.h"
using std::unique_ptr;
using std::move;

#pragma comment (lib, "d3d9.lib")

LptaD3D::LptaD3D(HINSTANCE dll)
{
	this->d3d = Direct3DCreate9(D3D_SDK_VERSION);
	this->dll = dll;

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
}

bool LptaD3D::IsRunning(void)
{
	return FALSE;
}

HRESULT LptaD3D::BeginRendering(bool, bool, bool)
{
	d3ddev->BeginScene();
	return S_OK;
}

HRESULT LptaD3D::Clear(bool, bool, bool)
{
	return S_OK;
}

void LptaD3D::EndRendering(void)
{
	d3ddev->EndScene();
	d3ddev->Present(NULL, NULL, NULL, NULL);
}

void LptaD3D::SetClearColor(float, float, float)
{

}

HRESULT LptaD3D::UseWindow(UINT numWindows)
{
	return S_OK;
}

