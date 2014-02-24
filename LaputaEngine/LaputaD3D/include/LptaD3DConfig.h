#ifndef _LPTAD3DMODEL_H_
#define _LPTAD3DMODEL_H_

#include <vector>
#include <memory>
#include <d3d9.h>
#include <Windows.h>
#include "adapter/AdapterInfo.h"
using std::vector;
using std::shared_ptr;


namespace lpta_d3d
{
struct LPTADEVICEINFO;
struct LPTACOMBOINFO;

class LptaD3DConfig;
typedef shared_ptr<LptaD3DConfig> LPTA_D3D_CONFIG;

const UINT DEFAULT_WIDTH = 800;
const UINT DEFAULT_HEIGHT = 600;

const BOOL DEFAULT_WINDOWED = TRUE;

const D3DSWAPEFFECT DEFAULT_SWAP_EFFECT = D3DSWAPEFFECT_DISCARD;

class LptaD3DConfig
{
public:
    ///////////////////////////////////////////////////////////////////////////
    // Singleton factory
    /////////////////////////////////////////////////////////////////
    static LPTA_D3D_CONFIG GetConfig(void);
    static LPTA_D3D_CONFIG GetConfig(const LPDIRECT3D9 d3d);

    ~LptaD3DConfig(void);

    ///////////////////////////////////////////////////////////////////////////
    // Queries
    /////////////////////////////////////////////////////////////////
    D3DPRESENT_PARAMETERS GetParameters(void) const;
    UINT GetSelectedAdapter(void) const;
    D3DDEVTYPE GetDeviceType(void) const;

    ///////////////////////////////////////////////////////////////////////////
    // User dialog methods
    /////////////////////////////////////////////////////////////////
    void ConnectTo(HWND dialog);
    void ShowUserDialog(HINSTANCE hDLL, HWND hWnd);
    BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
    ///////////////////////////////////////////////////////////////////////////
    // Singleton instance
    /////////////////////////////////////////////////////////////////
    static LPTA_D3D_CONFIG _d3dConfig;
    LptaD3DConfig(const LPDIRECT3D9 d3d);

    ///////////////////////////////////////////////////////////////////////////
    // User dialog helper methods
    /////////////////////////////////////////////////////////////////
    void UpdateAdapterOptions(void) const;
    void UpdateParametersFromDialog(void);

    ///////////////////////////////////////////////////////////////////////////
    //
    /////////////////////////////////////////////////////////////////
    vector<AdapterInfo> adapterInfos;
    UINT selectedAdapter;
    D3DDEVTYPE deviceType;
    D3DPRESENT_PARAMETERS parameters;

    ///////////////////////////////////////////////////////////////////////////
    // Dialog specific attributes
    /////////////////////////////////////////////////////////////////
    HWND fullscreenToggle;
    HWND windowedToggle;
    HWND adapterSelection;
    HWND backBufferSelection;
    HWND modeSelection;
    HWND formatSelection;
    HWND deviceSelection;
};

}

#endif