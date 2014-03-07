#include <gtest/gtest.h>
#include "LptaD3DVertexCache.h"
#include "LptaD3D_Helper.h"
using namespace lpta_d3d;

class LptaD3DVertexCacheTest : public D3D9Test
{
};

TEST_F(LptaD3DVertexCacheTest, CreateCache)
{
    LptaD3DVertexCache *cache = new LptaD3DVertexCache(d3ddev);
    delete cache;
}