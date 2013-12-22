#ifndef _LPTAD3D_H_
#define _LPTAD3D_H_

#include <d3dx9.h>
#include "LptaD3DConfig.h"
#include "LptaRenderDeviceImpl.h"
using std::unique_ptr;

#define MAX_3DHWND 8

namespace lpta_d3d
{
	const int MIN_WIDTH = 800;
	const int MIN_HEIGHT = 600;
	const int MIN_BITS = 16;

	const D3DFORMAT RENDER_FORMAT = D3DFMT_X8R8G8B8;

	const D3DDEVTYPE DEVICE_TYPES[] = {
		D3DDEVTYPE_HAL,
		D3DDEVTYPE_REF,
		D3DDEVTYPE_SW,
	};
	const int NUM_DEVICE_TYPES = sizeof(DEVICE_TYPES) / sizeof(D3DDEVTYPE);
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
	LPTA_D3D_CONFIG config;
	LPDIRECT3DSWAPCHAIN9 chain[MAX_3DHWND];
	D3DCOLOR clearColor;
	bool isSceneRunning;
	bool stencil;

	static void SelectRadioButton(HWND handle);

	HRESULT Go(void);

	void Log(char *, ...);
};

#endif