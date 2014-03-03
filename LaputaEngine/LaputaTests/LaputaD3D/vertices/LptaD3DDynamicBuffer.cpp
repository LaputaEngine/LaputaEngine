#include "LaputaD3D/LptaD3D_Helper.h"
#include "LptaVector.h"
#include "LptaColor.h"
#include "vertices/LptaVertices.h"
#include "vertices/LptaUUVertices.h"
#include "vertices/LptaULVertices.h"
#include "vertices/LptaD3DDynamicBuffer.h"
using namespace lpta_d3d;

class LptaD3DDynamicBufferTest : public D3D9Test
{
};

TEST_F(LptaD3DDynamicBufferTest, GetVertexType)
{
    {
        LptaD3DDynamicBuffer buffer(d3ddev, lpta::VERTEX_TYPE::VT_UU, 10, 10);
        ASSERT_EQ(lpta::VERTEX_TYPE::VT_UU, buffer.GetVertexType());
    }
    {
        LptaD3DDynamicBuffer buffer(d3ddev, lpta::VERTEX_TYPE::VT_UL, 10, 10);
        ASSERT_EQ(lpta::VERTEX_TYPE::VT_UL, buffer.GetVertexType());
    }
}

TEST_F(LptaD3DDynamicBufferTest, CanFit)
{
    lpta::UL_VERTEX vertex = {
        lpta_3d::POINT(0.0f, 0.0f, 0.0f),
        lpta::LptaColor(1.0f, 1.0f, 1.0f, 1.0f),
        0.0f, 0.0f
    };
    lpta::LptaULVertices ul;
    for (unsigned int i = 0; i < 5; ++i) {
        ul.AddVertex(vertex);
    }
    {
        LptaD3DDynamicBuffer adequate(d3ddev, lpta::VERTEX_TYPE::VT_UL, 5, 5);
        ASSERT_TRUE(adequate.CanFit(ul));
    }
    {
        LptaD3DDynamicBuffer tooSmall(d3ddev, lpta::VERTEX_TYPE::VT_UL, 4, 4);
        ASSERT_FALSE(tooSmall.CanFit(ul));
    }
    {
        LptaD3DDynamicBuffer incompat(d3ddev, lpta::VERTEX_TYPE::VT_UU, 5, 5);
        ASSERT_FALSE(incompat.CanFit(ul));
    }
}

TEST_F(LptaD3DDynamicBufferTest, AddVertices)
{
    lpta::UL_VERTEX vertex = {
        lpta_3d::POINT(0.0f, 0.0f, 0.0f),
        lpta::LptaColor(1.0f, 1.0f, 1.0f, 1.0f),
        0.0f, 0.0f
    };
    lpta::LptaULVertices ul;
    for (unsigned int i = 0; i < 5; ++i) {
        ul.AddVertex(vertex);
    }
    {
        LptaD3DDynamicBuffer adequate(d3ddev, lpta::VERTEX_TYPE::VT_UL, 5, 5);
        ASSERT_TRUE(adequate.AddVertices(&ul));
        ASSERT_FALSE(adequate.AddVertices(&ul));
    }
    {
        LptaD3DDynamicBuffer tooSmall(d3ddev, lpta::VERTEX_TYPE::VT_UL, 3, 3);
        ASSERT_FALSE(tooSmall.AddVertices(&ul));
    }
    {
        LptaD3DDynamicBuffer incompat(d3ddev, lpta::VERTEX_TYPE::VT_UU, 5, 5);
        ASSERT_FALSE(incompat.AddVertices(&ul));
    }
}