#include <d3dx9.h>
#include "LptaRenderDeviceImpl.h"
#define MAX_3DHWND 8

enum LptaD3DEnum;

class LptaD3D : public LptaRenderDeviceImpl
{
public:
	LptaD3D(HINSTANCE hDLL);
	~LptaD3D(void);

	HRESULT Init(HWND, const HWND*, int, int, int, bool);
	BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

	void Release(void);
	bool IsRunning(void);
	HRESULT BeginRendering(bool, bool, bool);
	HRESULT Clear(bool, bool, bool);
	void EndRendering(void);
	void SetClearColor(float, float, float);
	HRESULT UseWindow(UINT nWindow);

private:
	LptaD3DEnum *pEnum;
	LPDIRECT3D9 d3D;
	LPDIRECT3DDEVICE9 pDevice;
	LPDIRECT3DSWAPCHAIN9 chain[MAX_3DHWND];
	D3DPRESENT_PARAMETERS d3dpp;
	D3DCOLOR clearColor;
	bool isSceneRunning;
	bool stencil;

	HRESULT Go(void);

	void Log(char *, ...);
};