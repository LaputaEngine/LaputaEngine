#ifndef _LPTAD3D_H_
#define _LPTAD3D_H_

#include <d3dx9.h>
#include "LptaD3DModel.h"
#include "LptaRenderDeviceImpl.h"
using std::unique_ptr;

#define MAX_3DHWND 8

namespace lpta_d3d
{
	const int MIN_WIDTH = 800;
	const int MIN_HEIGHT = 600;
	const int MIN_BITS = 16;

	const D3DFORMAT RENDER_FORMATS[] = {D3DFMT_X8R8G8B8, D3DFMT_X1R5G5B5, D3DFMT_R5G6B5};
	const int NUM_RENDER_FORMATS = sizeof(RENDER_FORMATS) / sizeof(D3DFORMAT);
}

class LptaD3D : public LptaRenderDeviceImpl
{
public:
	LptaD3D(HINSTANCE hDLL);
	~LptaD3D(void);

	HRESULT Init(HWND, const std::shared_ptr<HWND>, int, int, bool);
	BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

	void Release(void);
	bool IsRunning(void);
	HRESULT BeginRendering(bool, bool, bool);
	HRESULT Clear(bool, bool, bool);
	void EndRendering(void);
	void SetClearColor(float, float, float);
	HRESULT UseWindow(UINT nWindow);

private:
	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 d3ddev;
	unique_ptr<LptaD3DModel> configuration;
	LPDIRECT3DSWAPCHAIN9 chain[MAX_3DHWND];
	D3DCOLOR clearColor;
	bool isSceneRunning;
	bool stencil;

	static void SelectRadioButton(HWND handle);

	HRESULT Go(void);

	void Log(char *, ...);
};

#endif