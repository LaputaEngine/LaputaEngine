#ifndef _LPTAD3DUTILS_H_
#define _LPTAD3DUTILS_H_

#include <vector>
#include <string>
#include <d3d9.h>

namespace LptaD3DUtils {
	unsigned int GetBitsFor(D3DFORMAT format);
	std::string GetTitleFor(D3DDEVTYPE deviceType);

	std::wstring ToUnicode(const std::string &str);

	struct DisplayFormatComparator
	{
		bool operator()(const D3DDISPLAYMODE &first, const D3DDISPLAYMODE &second)
		{
			if (first.Width != second.Width)
			{
				return first.Width < second.Width;
			}
			else if (first.Height != second.Height)
			{
				return first.Height < second.Height;
			}
			else
			{
				return first.RefreshRate < second.RefreshRate;
			}
		}
	};
}

#endif