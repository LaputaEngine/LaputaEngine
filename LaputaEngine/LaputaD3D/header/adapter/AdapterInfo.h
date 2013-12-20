#include <vector>
#include <Windows.h>
#include <d3d9.h>
using std::vector;
using std::string;

class AdapterInfo
{
public:
	AdapterInfo(UINT adapterIndex, D3DADAPTER_IDENTIFIER9 identifier);
	~AdapterInfo(void);

	UINT GetAdapterIndex(void) const;
	string GetDescription(void) const;
	const vector<D3DDISPLAYMODE> & GetDisplayModes(void) const;

	void AddDisplayMode(const D3DDISPLAYMODE &mode);
private:
	UINT adapterIndex;
	D3DADAPTER_IDENTIFIER9 identifier;
	vector<D3DDISPLAYMODE> displayModes;
};