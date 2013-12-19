#include <Windows.h>
#include <d3d9.h>

class AdapterInfo
{
public:
	AdapterInfo(UINT adapterIndex);
	~AdapterInfo(void);
private:
	UINT adapterIndex;
};