#include <vector>
#include <Windows.h>
#include <d3d9.h>
#include "LptaD3DUtils.h"
using std::vector;
using std::string;

typedef vector<D3DDISPLAYMODE> DISPLAY_MODES;

class AdapterInfo
{
public:
	AdapterInfo(UINT adapterIndex, D3DADAPTER_IDENTIFIER9 identifier);
	~AdapterInfo(void);

	UINT GetAdapterIndex(void) const;
	string GetDescription(void) const;
	const DISPLAY_MODES & GetDisplayModes(void) const;

	void AddDisplayMode(const D3DDISPLAYMODE &mode);
	void AddDisplayModes(const DISPLAY_MODES &modes);
private:
	UINT adapterIndex;
	D3DADAPTER_IDENTIFIER9 identifier;
	DISPLAY_MODES displayModes;
};