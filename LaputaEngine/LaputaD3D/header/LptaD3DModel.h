#ifndef _LPTAD3DMODEL_H_
#define _LPTAD3DMODEL_H_
#include <vector>
#include <d3d9.h>
#include <Windows.h>
#include "adapter/AdapterInfo.h"
using std::vector;

struct LPTADEVICEINFO;
struct LPTACOMBOINFO;

class LptaD3DModel
{
public:
	LptaD3DModel(LPDIRECT3D9 d3d);
	~LptaD3DModel(void);

	void Model(HWND dialog);

	LPDIRECT3D9 GetD3D() const;

	const vector<D3DFORMAT> & GetFormats(void) const;

	void UpdateAdapterOptions(void) const;
private:
	LPDIRECT3D9 d3d;

	vector<D3DFORMAT> displayFormats;
	vector<AdapterInfo> adapterInfos;

	HWND fullscreenToggle;
	HWND windowedToggle;
	HWND adapterSelection;
	HWND backBufferSelection;
	HWND modeSelection;
	HWND formatSelection;
	HWND deviceSelection;
};

#endif