#include "LptaD3DConfig.h"
#include <sstream>
#include "resource.h"

void PopulateAdapterSelections(vector<AdapterInfo> &adapterInfos, HWND comboBox);
void AddComboBoxItem(HWND comboxBox, const wchar_t *title, void *data);

///////////////////////////////////////////////////////////////////////////
// User dialog methods
/////////////////////////////////////////////////////////////////
void LptaD3DConfig::ConnectTo(HWND dialog)
{
	fullscreenToggle = GetDlgItem(dialog, IDC_FULLSCREEN);
	windowedToggle = GetDlgItem(dialog, IDC_WINDOWED);
	adapterSelection = GetDlgItem(dialog, IDC_ADAPTER);
	modeSelection = GetDlgItem(dialog, IDC_MODE);
	formatSelection = GetDlgItem(dialog, IDC_FORMAT);
	backBufferSelection = GetDlgItem(dialog, IDC_BACKFMT);
	deviceSelection = GetDlgItem(dialog, IDC_DEVICE);

	PopulateAdapterSelections(adapterInfos, adapterSelection);
	UpdateAdapterOptions();
}
void PopulateAdapterSelections(vector<AdapterInfo> &adapterInfos, HWND comboBox)
{
	SendMessage(comboBox, CB_RESETCONTENT, 0, 0);
	vector<AdapterInfo>::iterator adapter;
	for (adapter = adapterInfos.begin(); adapter != adapterInfos.end(); adapter++) {
		std::string adapterDescription = adapter->GetDescription();
		std::wstring wDescription(adapterDescription.begin(), adapterDescription.end());
		AddComboBoxItem(comboBox, wDescription.c_str(), &(*adapter));
	}
	SendMessage(comboBox, CB_SETCURSEL, 0, NULL);
}

BOOL CALLBACK DlgProcWrapper(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return LptaD3DConfig::GetConfig()->DlgProc(hWnd, message, wParam, lParam);
}

void LptaD3DConfig::ShowUserDialog(HINSTANCE hDLL, HWND hWnd)
{
	DialogBox(hDLL, MAKEINTRESOURCE(dlgChangeDevice), hWnd, DlgProcWrapper);
}

BOOL CALLBACK LptaD3DConfig::DlgProc(HWND dialog, UINT message, WPARAM wParam, LPARAM lParam)
{
	BOOL isWindow = FALSE;
	LPTA_D3D_CONFIG config = LptaD3DConfig::GetConfig();


	switch (message) {
	case WM_INITDIALOG:
		config->ConnectTo(dialog);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_ADAPTER:
			config->UpdateAdapterOptions();
			return TRUE;
		case IDOK:
		case IDCANCEL:
			EndDialog(dialog, 0);
			return TRUE;
		}
	default:
		break;
	}
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////
// User dialog helper methods
/////////////////////////////////////////////////////////////////
void LptaD3DConfig::UpdateAdapterOptions(void) const
{
	UINT current = (UINT)SendMessage(adapterSelection, CB_GETCURSEL, 0, 0);
	AdapterInfo *adapter = (AdapterInfo *)SendMessage(adapterSelection, CB_GETITEMDATA, current, 0);
	SendMessage(modeSelection, CB_RESETCONTENT, 0, 0);
	SendMessage(modeSelection, CB_SETCURSEL, 0, 0);
	DISPLAY_MODES displayModes = adapter->GetDisplayModes();
	DISPLAY_MODES::iterator displayMode;
	for (displayMode = displayModes.begin(); displayMode != displayModes.end(); displayMode++) {
		std::wstringstream ss;
		ss << displayMode->Width << " x " << displayMode->Height << " @ " << displayMode->RefreshRate;
		AddComboBoxItem(modeSelection, ss.str().c_str(), (void *)&(*displayMode));
	}
	SendMessage(modeSelection, CB_SETCURSEL, 0, 0);
}

void AddComboBoxItem(HWND comboBox, const wchar_t *title, void *data)
{
	int itemIndex = (int)SendMessage(comboBox, CB_ADDSTRING, NULL, (LPARAM)title);
	SendMessage(comboBox, CB_SETITEMDATA, (WPARAM)itemIndex, (LPARAM)data);
}
