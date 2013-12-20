#include "Adapter/AdapterInfo.h"

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

const vector<D3DDISPLAYMODE> & AdapterInfo::GetDisplayModes(void) const
{
	return displayModes;
}

void AdapterInfo::AddDisplayMode(const D3DDISPLAYMODE &mode)
{
	displayModes.push_back(mode);
}