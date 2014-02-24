#include "LptaD3DConfig.h"
#include <sstream>
#include "LptaD3D.h"
#include "resource.h"

namespace lpta_d3d
{

void PopulateAdapterSelections(vector<AdapterInfo> &adapterInfos, HWND comboBox);
void PopulateDeviceTypeSelections(HWND comboBox);

HRESULT GetComboBoxSelection(HWND comboBox);
void AddComboBoxItem(HWND comboxBox, const string &title, LPARAM data);

///////////////////////////////////////////////////////////////////////////
// User dialog methods
/////////////////////////////////////////////////////////////////
void LptaD3DConfig::ConnectTo(HWND dialog)
{
    fullscreenToggle = GetDlgItem(dialog, IDC_FULLSCREEN);
    windowedToggle = GetDlgItem(dialog, IDC_WINDOWED);
    adapterSelection = GetDlgItem(dialog, IDC_ADAPTER);
    modeSelection = GetDlgItem(dialog, IDC_MODE);
    deviceSelection = GetDlgItem(dialog, IDC_DEVICE);

    PopulateAdapterSelections(adapterInfos, adapterSelection);
    PopulateDeviceTypeSelections(deviceSelection);
    UpdateAdapterOptions();
    SendMessage(windowedToggle, BM_SETCHECK, BST_CHECKED, 0);
}
void PopulateAdapterSelections(vector<AdapterInfo> &adapterInfos, HWND comboBox)
{
    SendMessage(comboBox, CB_RESETCONTENT, 0, 0);
    vector<AdapterInfo>::iterator adapter;
    for (adapter = adapterInfos.begin(); adapter != adapterInfos.end(); adapter++) {
        AddComboBoxItem(comboBox, adapter->GetDescription(), (LPARAM)&(*adapter));
    }
    SendMessage(comboBox, CB_SETCURSEL, 0, 0);
}
void PopulateDeviceTypeSelections(HWND comboBox)
{
    SendMessage(comboBox, CB_RESETCONTENT, 0, 0);
    for (unsigned int i = 0; i < lpta_d3d::NUM_DEVICE_TYPES; i++) {
        D3DDEVTYPE deviceType = lpta_d3d::DEVICE_TYPES[i];
        AddComboBoxItem(comboBox, lpta_d3d_utils::GetTitleFor(deviceType), deviceType);
    }
    SendMessage(comboBox, CB_SETCURSEL, 0, 0);
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
            if (HIWORD(wParam) == CBN_SELCHANGE) {
                config->UpdateAdapterOptions();
                return TRUE;
            }
            break;
        case IDOK:
            UpdateParametersFromDialog();
            EndDialog(dialog, 1);
            return TRUE;
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
    AdapterInfo *adapter = (AdapterInfo *)GetComboBoxSelection(adapterSelection);
    SendMessage(modeSelection, CB_RESETCONTENT, 0, 0);
    SendMessage(modeSelection, CB_SETCURSEL, 0, 0);
    DISPLAY_MODES displayModes = adapter->GetDisplayModes();
    for (unsigned int i = 0; i < displayModes.size(); i++) {
        D3DDISPLAYMODE displayMode = displayModes[i];
        std::stringstream ss;
        ss << displayMode.Width << " x " << displayMode.Height << " @ " << displayMode.RefreshRate;
        AddComboBoxItem(modeSelection, ss.str(), (LPARAM)i);
    }
    SendMessage(modeSelection, CB_SETCURSEL, 0, 0);
}

void LptaD3DConfig::UpdateParametersFromDialog(void)
{
    AdapterInfo *adapter = (AdapterInfo *)GetComboBoxSelection(adapterSelection);
    unsigned int displayModeIndex = (unsigned int)GetComboBoxSelection(modeSelection);
    D3DDISPLAYMODE displayMode = adapter->GetDisplayModes()[displayModeIndex];
    selectedAdapter = adapter->GetAdapterIndex();
    parameters.BackBufferWidth = displayMode.Width;
    parameters.BackBufferHeight = displayMode.Height;
    parameters.Windowed = SendMessage(windowedToggle, BM_GETCHECK, 0, 0) == BST_CHECKED;
    deviceType = (D3DDEVTYPE)GetComboBoxSelection(deviceSelection);
}

HRESULT GetComboBoxSelection(HWND comboBox)
{
    UINT currentIndex = (UINT)SendMessage(comboBox, CB_GETCURSEL, 0, 0);
    return SendMessage(comboBox, CB_GETITEMDATA, currentIndex, 0);
}

void AddComboBoxItem(HWND comboBox, const string &title, LPARAM data)
{
    std::wstring wTitle = lpta_d3d_utils::ToUnicode(title);
    int itemIndex = (int)SendMessage(comboBox, CB_ADDSTRING, NULL, (LPARAM)wTitle.c_str());
    SendMessage(comboBox, CB_SETITEMDATA, (WPARAM)itemIndex, data);
}

}