#include <gtest/gtest.h>
#include <vector>
#include "LptaVector.h"
#include "LptaColor.h"
#include "LptaD3DColorUtils.h"
#include "vertices/LptaD3DVertex.h"
#include "vertices/LptaUUVertexCollection.h"
#include "vertices/LptaULVertexCollection.h"
#include "vertices/LptaD3DVertexBuffer.h"
#include "vertices/LptaD3DVertexCopier.h"
using lpta_d3d::LptaD3DVertexCopier;

TEST(LptaD3DVertexCopierTest, UUCopier)
{
    lpta::UU_VERTEX vertex = {
        lpta_3d::POINT(0.0f, 0.0f, 0.0f),
        lpta_3d::LptaVector(1.0f, 0.0f, 0.0f),
        0.0f, 0.0f
    };
    lpta::LptaUUVertexCollection uu;
    uu.AddVertex(vertex);
    uu.AddVertex(vertex);
    lpta_d3d::LptaD3DVertexCopier copier(&uu);
    ASSERT_EQ(2, copier.GetNumVertices());
    ASSERT_EQ(sizeof(lpta_d3d::D3D_VERTEX), copier.GetStride());
    ASSERT_EQ(sizeof(lpta_d3d::D3D_VERTEX) * uu.GetNumVertices(), copier.ByteSize());
    lpta_d3d::D3D_VERTEX buffer[2];
    auto result = 
        copier.CopyToBuffer(static_cast<void *>(buffer), sizeof(lpta_d3d::D3D_VERTEX) * 2);
    ASSERT_EQ(copier.SUCCESS, result);
    ASSERT_EQ(0.0f, buffer[0].x);
    ASSERT_EQ(0.0f, buffer[0].y);
    ASSERT_EQ(0.0f, buffer[0].z);
    ASSERT_EQ(1.0f, buffer[0].normal[0]);
    ASSERT_EQ(0.0f, buffer[0].normal[1]);
    ASSERT_EQ(0.0f, buffer[0].normal[2]);
    ASSERT_EQ(0.0f, buffer[0].tu);
    ASSERT_EQ(0.0f, buffer[0].tv);
}

TEST(LptaD3DVertexCopierTest, UUCopier_BadBuffer)
{
    lpta::UU_VERTEX vertex = {
        lpta_3d::POINT(1.0f, 2.0f, 3.0f),
        lpta_3d::LptaVector(0.0f, 1.0f, 0.0f),
        0.0f, 0.0f
    };
    lpta::LptaUUVertexCollection uu;
    uu.AddVertex(vertex);
    uu.AddVertex(vertex);
    lpta_d3d::LptaD3DVertexCopier copier(&uu);
    auto result = copier.CopyToBuffer(NULL, sizeof(lpta_d3d::D3D_VERTEX) * 2);
    ASSERT_EQ(copier.FAILURE, result);
    lpta_d3d::D3D_VERTEX inadequate[1];
    result = copier.CopyToBuffer(inadequate, sizeof(lpta_d3d::D3D_VERTEX));
    ASSERT_EQ(copier.FAILURE, result);
}

TEST(LptaD3DVertexCopierTest, ULCopier)
{
    lpta::UL_VERTEX vertex = {
        lpta_3d::POINT(0.0f, 0.0f, 0.0f),
        lpta::LptaColor(1.0f, 1.0f, 1.0f, 0.0f),
        0.0f, 0.0f
    };
    lpta::LptaULVertexCollection ul;
    ul.AddVertex(vertex);
    ul.AddVertex(vertex);
    lpta_d3d::LptaD3DVertexCopier copier(&ul);
    ASSERT_EQ(2, copier.GetNumVertices());
    ASSERT_EQ(sizeof(lpta_d3d::D3D_LVERTEX), copier.GetStride());
    ASSERT_EQ(sizeof(lpta_d3d::D3D_LVERTEX) * ul.GetNumVertices(), copier.ByteSize());
    lpta_d3d::D3D_LVERTEX buffer[2];
    void *casted = static_cast<void *>(buffer);
    auto result = copier.CopyToBuffer(casted, sizeof(lpta_d3d::D3D_LVERTEX) * 2);
    ASSERT_EQ(copier.SUCCESS, result);
    ASSERT_EQ(0.0f, buffer[1].x);
    ASSERT_EQ(0.0f, buffer[1].y);
    ASSERT_EQ(0.0f, buffer[1].z);
    lpta_d3d_utils::Color32Bit color = buffer[1].color;
    DWORD dwColor = *(reinterpret_cast<DWORD *>(&color));
    ASSERT_EQ(0xFFFFFF00, dwColor);
    ASSERT_EQ(0.0f, buffer[1].tu);
    ASSERT_EQ(0.0f, buffer[1].tv);
}

TEST(LptaD3DVertexCopierTest, ULCopier_BadBuffer)
{
    lpta::UL_VERTEX vertex = {
        lpta_3d::POINT(0.0f, 0.0f, 0.0f),
        lpta::LptaColor(1.0f, 1.0f, 1.0f, 0.0f),
        0.0f, 0.0f
    };
    lpta::LptaULVertexCollection ul;
    ul.AddVertex(vertex);
    ul.AddVertex(vertex);
    lpta_d3d::LptaD3DVertexCopier copier(&ul);
    auto result = copier.CopyToBuffer(NULL, sizeof(lpta_d3d::D3D_LVERTEX) * 2);
    ASSERT_EQ(copier.FAILURE, result);
    lpta_d3d::D3D_LVERTEX inadequate[1];
    result = copier.CopyToBuffer(inadequate, sizeof(lpta_d3d::D3D_LVERTEX));
    ASSERT_EQ(copier.FAILURE, result);
}