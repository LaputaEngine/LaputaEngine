#ifndef _LPTARENDERDEVICE_H_
#define _LPTARENDERDEVICE_H_
#include <memory>
#include <Windows.h>

class LptaRenderDevice
{
public:
	LptaRenderDevice(void) {};
	virtual ~LptaRenderDevice(void) {};

	///////////////////////////////////////////////////////////////////////////
	// Initialization/Release
	/////////////////////////////////////////////////////////////////
	virtual HRESULT Init(HWND, const std::shared_ptr<HWND>, int, int, int, bool) = 0;
	virtual void Release(void) = 0;
	virtual bool IsRunning(void) = 0;

	///////////////////////////////////////////////////////////////////////////
	// Rendering
	/////////////////////////////////////////////////////////////////
	virtual HRESULT UseWindow(UINT) = 0;
	virtual HRESULT BeginRendering(bool, bool, bool) = 0;
	virtual void EndRendering(void) = 0;
	virtual HRESULT Clear(bool, bool, bool) = 0;
	virtual void SetClearColor(float, float, float) = 0;
};

typedef std::shared_ptr<LptaRenderDevice> LPTAFXRENDERER;

extern "C"
{
	HRESULT CreateRenderDevice(HINSTANCE hDLL, const LPTAFXRENDERER& pInterface);
	typedef HRESULT(*CREATERENDERDEVICE) (HINSTANCE hDLL, const LPTAFXRENDERER& pInterface);

	HRESULT ReleaseRenderDevice(const LPTAFXRENDERER& pInterface);
	typedef HRESULT(*RELEASERENDERDEVICE) (const LPTAFXRENDERER& pInterface);
}


#endif