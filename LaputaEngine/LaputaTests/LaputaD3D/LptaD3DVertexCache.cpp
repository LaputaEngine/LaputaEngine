#include <gtest/gtest.h>
#include "LptaVector.h"
#include "LptaNormalVector.h"
#include "vertices/LptaVertices.h"
#include "vertices/LptaUUVertices.h"
#include "LptaD3DVertexCache.h"
#include "LptaD3D_Helper.h"
using namespace lpta_3d;
using namespace lpta_d3d;

class LptaD3DVertexCacheTest : public D3D9Test
{
};

TEST_F(LptaD3DVertexCacheTest, CreateCache)
{
    LptaD3DVertexCache *cache = new LptaD3DVertexCache(d3ddev);
    delete cache;
}

TEST_F(LptaD3DVertexCacheTest, CreateStaticBuffer)
{
    lpta::UU_VERTEX vertex = {
        lpta_3d::POINT(1.0f, 2.0f, 3.0f),
        lpta_3d::LptaNormalVector::MakeFrom(1.0f, 1.0f, 1.0f),
        0.0f, 1.0f
    };
    lpta::LptaUUVertices uu;
    uu.AddVertex(vertex);
    lpta::INDICES indices;
    indices.push_back(0);
    LptaD3DVertexCache cache(d3ddev);
    lpta::LptaResource::ID id = cache.CreateStaticBuffer(&uu, indices);
    ASSERT_EQ(1, id);
}