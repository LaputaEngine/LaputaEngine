#include <sstream>
#include "LptaD3DModel.h"
#include "LptaD3D.h"
#include "LptaD3DUtils.h"
#include "resource.h"
using std::vector;
using std::iterator;
using std::string;

void DiscoverAdapters(LptaD3DModel *model, const LPDIRECT3D9 d3d, vector<AdapterInfo> &adapterInfos);
void DiscoverDisplayModesFor(AdapterInfo &adapterInfo, LptaD3DModel *model, const LPDIRECT3D9 d3d);
bool ValidDisplayMode(const D3DDISPLAYMODE &displayMode);

void PopulateAdapterSelections(vector<AdapterInfo> &adapterInfos, HWND comboBox);
void AddComboBoxItem(HWND comboxBox, const wchar_t *title, void *data);

LptaD3DModel::LptaD3DModel(LPDIRECT3D9 d3d)
{
	this->d3d = d3d;
	for (unsigned int i = 0; i < lpta_d3d::NUM_RENDER_FORMATS; i++) {
		displayModes.push_back(lpta_d3d::RENDER_FORMATS[i]);
	}
	DiscoverAdapters(this, d3d, adapterInfos); // depends on render formats
}
void DiscoverAdapters(LptaD3DModel *model, const LPDIRECT3D9 d3d, vector<AdapterInfo> &adapterInfos)
{
	for (unsigned int i = 0; i < d3d->GetAdapterCount(); i++) {
		D3DADAPTER_IDENTIFIER9 identifier;
		d3d->GetAdapterIdentifier(i, 0, &identifier);
		AdapterInfo currentInfo(i, identifier);
		
		DiscoverDisplayModesFor(currentInfo, model, d3d);
		adapterInfos.push_back(currentInfo);
	}
}
void DiscoverDisplayModesFor(AdapterInfo &adapterInfo, LptaD3DModel *model, const LPDIRECT3D9 d3d)
{
	vector<D3DFORMAT> displayModes = model->GetDisplayModes();
	vector<D3DFORMAT>::iterator mode;
	for (mode = displayModes.begin(); mode != displayModes.end();  mode++) {
		for (unsigned int i = 0; i < d3d->GetAdapterModeCount(adapterInfo.GetAdapterIndex(), *mode); i++) {
			D3DDISPLAYMODE displayMode;
			d3d->EnumAdapterModes(adapterInfo.GetAdapterIndex(), *mode, i, &displayMode);
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

LptaD3DModel::~LptaD3DModel(void)
{

}

void LptaD3DModel::Model(HWND dialog)
{
	fullscreenToggle = GetDlgItem(dialog, IDC_FULLSCREEN);
	windowedToggle = GetDlgItem(dialog, IDC_WINDOWED);
	adapterSelection = GetDlgItem(dialog, IDC_ADAPTER);
	modeSelection = GetDlgItem(dialog, IDC_MODE);
	formatSelection = GetDlgItem(dialog, IDC_FORMAT);
    backBufferSelection = GetDlgItem(dialog, IDC_BACKFMT);
	deviceSelection = GetDlgItem(dialog, IDC_DEVICE);

	PopulateAdapterSelections(adapterInfos, adapterSelection);
}
void PopulateAdapterSelections(vector<AdapterInfo> &adapterInfos, HWND comboBox)
{
	//SendMessage(comboBox, CB_RESETCONTENT, 0, 0);
	vector<AdapterInfo>::iterator adapter;
	for (adapter = adapterInfos.begin(); adapter != adapterInfos.end(); adapter++) {
		std::string adapterDescription = adapter->GetDescription();
		std::wstring wDescription(adapterDescription.begin(), adapterDescription.end());
		AddComboBoxItem(comboBox, wDescription.c_str(), &(*adapter));
	}
	SendMessage(comboBox, CB_SETCURSEL, 0, NULL);
}

void AddComboBoxItem(HWND comboBox, const wchar_t *title, void *data)
{
	int itemIndex = (int)SendMessage(comboBox, CB_ADDSTRING, NULL, (LPARAM)title);
	SendMessage(comboBox, CB_SETITEMDATA, (WPARAM)itemIndex, (LPARAM)data);
}

LPDIRECT3D9 LptaD3DModel::GetD3D() const
{
	return d3d;
}

const vector<D3DFORMAT> & LptaD3DModel::GetDisplayModes(void) const
{
	return displayModes;
}