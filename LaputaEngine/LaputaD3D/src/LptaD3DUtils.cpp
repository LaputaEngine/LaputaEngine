#include "LptaD3DUtils.h"
#include <algorithm>
#include <sstream>

bool CompareFormats(const D3DDISPLAYMODE &first, const D3DDISPLAYMODE &second);

unsigned int lpta_d3d_utils::GetBitsFor(D3DFORMAT format)
{
    switch (format) {
        case D3DFMT_A2B10G10R10: return 32;
        case D3DFMT_R8G8B8: return 24;
        case D3DFMT_A8R8G8B8: return 24;
        case D3DFMT_X8R8G8B8: return 24;
        case D3DFMT_R5G6B5: return 16;
        case D3DFMT_X1R5G5B5: return 15;
        case D3DFMT_A1R5G5B5: return 15;
        case D3DFMT_X4R4G4B4: return 12;
        case D3DFMT_A4R4G4B4: return 12;
        case D3DFMT_R3G3B2: return 8;
        case D3DFMT_A8R3G3B2: return 8;
        default: return 0;
    }
}

std::string lpta_d3d_utils::GetTitleFor(D3DDEVTYPE deviceType)
{
    switch (deviceType) {
    case D3DDEVTYPE_HAL: return "DEVICE_TYPE_HAL";
    case D3DDEVTYPE_REF: return "DEVICE_TYPE_REF";
    case D3DDEVTYPE_SW: return "DEVICE_TYPE_SW";
    default: return "UNKNOWN_DEVICE_TYPE";
    }
}

std::wstring lpta_d3d_utils::ToUnicode(const std::string &str)
{
    std::wstringstream ss;
    ss << str.c_str();
    return ss.str();
}