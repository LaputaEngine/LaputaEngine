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
	d3d->Release();
	config.reset();
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
	return S_OK;
}

// this should be hidden inside the model

void LptaD3D::SelectRadioButton(HWND handle)
{
	SendMessage(handle, BM_SETCHECK, BST_CHECKED, 0);
}

void LptaD3D::Release(void)
{

}

bool LptaD3D::IsRunning(void)
{
	return FALSE;
}

HRESULT LptaD3D::BeginRendering(bool, bool, bool)
{
	return S_OK;
}

HRESULT LptaD3D::Clear(bool, bool, bool)
{
	return S_OK;
}

void LptaD3D::EndRendering(void)
{

}

void LptaD3D::SetClearColor(float, float, float)
{

}

HRESULT LptaD3D::UseWindow(UINT numWindows)
{
	return S_OK;
}

