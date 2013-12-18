#ifndef _LPTAD3DMODEL_H_
#define _LPTAD3DMODEL_H_
#include <vector>
#include <d3d9.h>
#include <Windows.h>
using std::vector;

struct LPTADEVICEINFO;
struct LPTACOMBOINFO;

struct LPTAADAPTERINFO 
{
	D3DADAPTER_IDENTIFIER9 identifier;
	UINT nAdapter;
	vector<D3DDISPLAYMODE> displayeModes;
	vector<LPTADEVICEINFO> devices;
};

struct LPTADEVICEINFO
{
	UINT nAdapter;
	D3DDEVTYPE type;
	D3DCAPS9 capabilities;
	vector<LPTACOMBOINFO> combos;
};

struct LPTACOMBOINFO
{
	UINT nAdapter;
	D3DDEVTYPE type;
	bool isWindowed;

	D3DFORMAT pixelBufferFormat;
	D3DFORMAT backBufferFormat;
	D3DFORMAT stencilDepthFormat;

	DWORD vertexProcessingBehavior;
	D3DMULTISAMPLE_TYPE multisampleType;
};


class LptaD3DModel
{
public:
	LptaD3DModel(LPDIRECT3D9 d3d);
	~LptaD3DModel(void);

	void Model(HWND dialog);

	LPDIRECT3D9 GetD3D() const;

	const vector<D3DFORMAT> & GetDisplayModes(void) const;

private:
	LPDIRECT3D9 d3d;

	vector<D3DFORMAT> displayModes;
	vector<LPTAADAPTERINFO> adapterInfos;

	HWND fullscreenToggle;
	HWND windowedToggle;
	HWND adapterSelection;
	HWND backBufferSelection;
	HWND modeSelection;
	HWND deviceSelection;
};

#endif