#include <exception>
#include "LptaD3DConfig.h"
#include "LptaD3D.h"
#include "LptaD3DUtils.h"
#include "resource.h"
using std::vector;

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
	for (unsigned int i = 0; i < lpta_d3d::NUM_RENDER_FORMATS; i++) {
		displayFormats.push_back(lpta_d3d::RENDER_FORMATS[i]);
	}
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
	vector<D3DFORMAT> formats = model->GetFormats();
	vector<D3DFORMAT>::iterator format;
	for (format = formats.begin(); format != formats.end();  format++) {
		for (unsigned int i = 0; i < d3d->GetAdapterModeCount(adapterInfo.GetAdapterIndex(), *format); i++) {
			D3DDISPLAYMODE displayMode;
			d3d->EnumAdapterModes(adapterInfo.GetAdapterIndex(), *format, i, &displayMode);
			if (ValidDisplayMode(displayMode)) {
				adapterInfo.AddDisplayMode(displayMode);
			}
		}
	}
}
bool ValidDisplayMode(const D3DDISPLAYMODE &displayMode)
{
	return displayMode.Width >= lpta_d3d::MIN_WIDTH &&
		displayMode.Height >= lpta_d3d::MIN_HEIGHT &&
		LptaD3DUtils::GetBitsFor(displayMode.Format) >= lpta_d3d::MIN_BITS;
}

///////////////////////////////////////////////////////////////////////////
// Accessors
/////////////////////////////////////////////////////////////////
const vector<D3DFORMAT> & LptaD3DConfig::GetFormats(void) const
{
	return displayFormats;
}