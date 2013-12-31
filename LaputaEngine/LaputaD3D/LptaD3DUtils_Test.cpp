#include <gtest/gtest.h>
#include <d3d9.h>
#include "LptaD3DUtils.h"
using namespace LptaD3DUtils;

TEST(D3D9Utils, GetTitleForNormalCase)
{
	ASSERT_EQ(GetTitleFor(D3DDEVTYPE_HAL), "DEVICE_TYPE_HAL");
}