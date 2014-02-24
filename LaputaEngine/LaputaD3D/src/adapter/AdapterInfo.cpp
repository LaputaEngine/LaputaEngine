#include "Adapter/AdapterInfo.h"
#include "LptaD3DUtils.h"

AdapterInfo::AdapterInfo(UINT adapterIndex, D3DADAPTER_IDENTIFIER9 identifier)
{
    this->adapterIndex = adapterIndex;
    this->identifier = identifier;
}

AdapterInfo::~AdapterInfo(void)
{

}

UINT AdapterInfo::GetAdapterIndex(void) const
{
    return adapterIndex;
}

string AdapterInfo::GetDescription(void) const
{
    return string(identifier.Description);
}

const DISPLAY_MODES & AdapterInfo::GetDisplayModes(void) const
{
    return displayModes;
}

void AdapterInfo::AddDisplayMode(const D3DDISPLAYMODE &mode)
{
    displayModes.push_back(mode);
}
void AdapterInfo::AddDisplayModes(const DISPLAY_MODES &modes)
{
    DISPLAY_MODES::const_iterator mode;
    for (mode = modes.begin(); mode != modes.end(); mode++) {
        AddDisplayMode(*mode);
    }
}