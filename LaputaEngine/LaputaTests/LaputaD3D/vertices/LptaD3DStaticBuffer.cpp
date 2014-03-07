#include <gtest/gtest.h>
#include "LaputaD3D/LptaD3D_Helper.h"
#include "LptaVector.h"
#include "LptaNormalVector.h"
#include "vertices/LptaUUVertices.h"
#include "vertices/LptaVertices.h"
#include "vertices/LptaD3DStaticBuffer.h"
using namespace lpta_d3d;

class LptaD3DStaticBufferTest : public D3D9Test
{
public:
    const unsigned int TEST_SIZE = 50;

public:
    LptaD3DStaticBufferTest(void)
    {
        for (unsigned int i = 0; i < TEST_SIZE; ++i) {
            lpta::UU_VERTEX vertex = {
                lpta_3d::POINT(static_cast<float>(i), 0.0f, 0.0f),
                lpta_3d::LptaNormalVector::MakeFrom(1.0f, 1.0f, 1.0f),
                0.0f, 0.0f
            };
            testVertices.AddVertex(vertex);
        }
    }

protected:
    lpta::LptaUUVertices testVertices;
};

TEST_F(LptaD3DStaticBufferTest, CreateBuffer)
{
    lpta::INDICES indices;
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);
    LptaD3DStaticBuffer *buffer = new LptaD3DStaticBuffer(d3ddev, &testVertices, indices, false);
    delete buffer;
    buffer = new LptaD3DStaticBuffer(d3ddev, &testVertices, indices, true);
    delete buffer;
}