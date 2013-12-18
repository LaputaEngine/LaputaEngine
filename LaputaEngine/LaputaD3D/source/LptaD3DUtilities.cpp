#include "LptaD3DUtils.h"

unsigned int LptaD3DUtils::GetBitsFor(D3DFORMAT format)
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