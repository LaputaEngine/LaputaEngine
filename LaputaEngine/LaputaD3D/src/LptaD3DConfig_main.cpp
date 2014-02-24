#include <exception>
#include "LptaD3DConfig.h"
#include "LptaD3D.h"
#include "LptaD3DUtils.h"
#include "resource.h"
using std::vector;

namespace lpta_d3d
{

void DiscoverAdapters(LptaD3DConfig *model, const LPDIRECT3D9 d3d, vector<AdapterInfo> &adapterInfos);
void DiscoverDisplayModesFor(AdapterInfo &adapterInfo, LptaD3DConfig *model, const LPDIRECT3D9 d3d);
bool ValidDisplayMode(const D3DDISPLAYMODE &displayMode);

LPTA_D3D_CONFIG LptaD3DConfig::_d3dConfig;

///////////////////////////////////////////////////////////////////////////
// Singleton factory
/////////////////////////////////////////////////////////////////
LPTA_D3D_CONFIG LptaD3DConfig::GetConfig(void)
{
    if (!_d3dConfig) {
        throw new std::domain_error("no config object to return");
    }
    return _d3dConfig;
}
LPTA_D3D_CONFIG LptaD3DConfig::GetConfig(const LPDIRECT3D9 d3d)
{
    if (!_d3dConfig) {
        _d3dConfig = LPTA_D3D_CONFIG(new LptaD3DConfig(d3d));
    }
    return GetConfig();
}

LptaD3DConfig::~LptaD3DConfig(void)
{
}


///////////////////////////////////////////////////////////////////////////
// Singleton instance -- initialization
/////////////////////////////////////////////////////////////////
LptaD3DConfig::LptaD3DConfig(const LPDIRECT3D9 d3d)
{
    selectedAdapter = 0;
    deviceType = D3DDEVTYPE_HAL;
    ZeroMemory(&parameters, sizeof(D3DPRESENT_PARAMETERS));
    parameters.BackBufferFormat = lpta_d3d::RENDER_FORMAT;
    parameters.BackBufferWidth = lpta_d3d::DEFAULT_WIDTH;
    parameters.BackBufferHeight = lpta_d3d::DEFAULT_HEIGHT;
    parameters.Windowed = lpta_d3d::DEFAULT_WINDOWED;
    parameters.SwapEffect = lpta_d3d::DEFAULT_SWAP_EFFECT;
    DiscoverAdapters(this, d3d, adapterInfos); // depends on render formats
}
void DiscoverAdapters(LptaD3DConfig *model, const LPDIRECT3D9 d3d, vector<AdapterInfo> &adapterInfos)
{
    for (unsigned int i = 0; i < d3d->GetAdapterCount(); i++) {
        D3DADAPTER_IDENTIFIER9 identifier;
        d3d->GetAdapterIdentifier(i, 0, &identifier);
        AdapterInfo currentInfo(i, identifier);
        
        DiscoverDisplayModesFor(currentInfo, model, d3d);
        adapterInfos.push_back(currentInfo);
    }
}
void DiscoverDisplayModesFor(AdapterInfo &adapterInfo, LptaD3DConfig *model, const LPDIRECT3D9 d3d)
{
    D3DFORMAT format = lpta_d3d::RENDER_FORMAT;
    for (unsigned int i = 0; i < d3d->GetAdapterModeCount(adapterInfo.GetAdapterIndex(), format); i++) {
        D3DDISPLAYMODE displayMode;
        d3d->EnumAdapterModes(adapterInfo.GetAdapterIndex(), format, i, &displayMode);
        if (ValidDisplayMode(displayMode)) {
            adapterInfo.AddDisplayMode(displayMode);
        }
    }
}
bool ValidDisplayMode(const D3DDISPLAYMODE &displayMode)
{
    return displayMode.Width >= lpta_d3d::MIN_WIDTH &&
        displayMode.Height >= lpta_d3d::MIN_HEIGHT &&
        lpta_d3d_utils::GetBitsFor(displayMode.Format) >= lpta_d3d::MIN_BITS;
}

///////////////////////////////////////////////////////////////////////////
// Queries
/////////////////////////////////////////////////////////////////
D3DPRESENT_PARAMETERS LptaD3DConfig::GetParameters(void) const
{
    return parameters;
}

UINT LptaD3DConfig::GetSelectedAdapter(void) const
{
    return selectedAdapter;
}

D3DDEVTYPE LptaD3DConfig::GetDeviceType(void) const
{
    return deviceType;
}

}