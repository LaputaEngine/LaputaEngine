#include "resource.h"
#include "LptaD3D.h"
using std::unique_ptr;
using std::move;

#pragma comment (lib, "d3d9.lib")

LptaD3D *g_Renderer = NULL;

BOOL CALLBACK DlgProcWrapper(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return g_Renderer->DlgProc(hWnd, message, wParam, lParam);
}

LptaD3D::LptaD3D(HINSTANCE dll)
{
	this->dll = dll;
	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	configuration = unique_ptr<LptaD3DModel>(new LptaD3DModel(d3d));
	g_Renderer = this;
}

LptaD3D::~LptaD3D(void)
{

}

HRESULT LptaD3D::Init(HWND hWnd, const std::shared_ptr<HWND> h3DWnd, int mindDepth, int minStencil, bool saveLog)
{
	DialogBox(dll, MAKEINTRESOURCE(dlgChangeDevice), hWnd, DlgProcWrapper);
	return S_OK;
}

BOOL CALLBACK LptaD3D::DlgProc(HWND dialog,
	UINT message, WPARAM wParam, LPARAM lParam)
{
	BOOL isWindow = FALSE;

	

	switch (message) {
	case WM_INITDIALOG:
		configuration->Model(dialog);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
		case IDCANCEL:
			EndDialog(dialog, 0);
			return TRUE;
		}
	default:
		break;
	}
	return FALSE;
}
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

