#include <gtest/gtest.h>
#include <vector>
#include "LptaVector.h"
#include "LptaColor.h"
#include "vertices/LptaUUVertexCollection.h"
#include "vertices/LptaULVertexCollection.h"
#include "vertices/LptaD3DStaticBuffer.h"
#include "vertices/LptaD3DVertexCollectionVisitor.h"

TEST(LptaD3DVertexCollectionVisitorTest, VisitUU)
{
    lpta::UU_VERTEX vertex = {
        lpta_3d::POINT(0.0f, 0.0f, 0.0f),
        lpta_3d::LptaVector(1.0f, 0.0f, 0.0f),
        0.0f, 0.0f
    };
    lpta::LptaUUVertexCollection uu;
    uu.AddVertex(vertex);
    uu.AddVertex(vertex);
    lpta_d3d::LptaD3DVertexCollectionVisitor visitor;
    uu.Accept(&visitor);
    const std::vector<lpta_d3d::LptaD3DStaticBuffer> transformed = visitor.GetTransforms();
    ASSERT_EQ(2, transformed.size());
}

TEST(LptaD3DVertexCollectionVisitorTest, VisitUL)
{
    lpta::UL_VERTEX vertex = {
        lpta_3d::POINT(0.0f, 0.0f, 0.0f),
        lpta::LptaColor(1.0f, 1.0f, 1.0f, 0.5),
        0.0f, 0.0f
    };
    lpta::LptaULVertexCollection ul;
    ul.AddVertex(vertex);
    ul.AddVertex(vertex);
    lpta_d3d::LptaD3DVertexCollectionVisitor visitor;
    ul.Accept(&visitor);
    const std::vector<lpta_d3d::LptaD3DStaticBuffer> transformed = visitor.GetTransforms();
    ASSERT_EQ(2, transformed.size());
}