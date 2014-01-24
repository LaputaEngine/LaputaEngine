#include <gtest/gtest.h>
#include "LptaVector.h"
#include "LptaOBB.h"
#include "LptaAABB.h"

TEST(LptaOBBTest, ConvertToAABBNormalCase_AlignedOriginConvert)
{
    COORDINATE coordinate(0, 0, 0);
    OBB_AXES axes;
    axes[0] = {
        LptaNormalVector(1.0f, 0.0f, 0.0f),
        1.0f,
    };
    axes[1] = {
        LptaNormalVector(0.0f, 1.0f, 0.0f),
        1.0f,
    };
    axes[2] = {
        LptaNormalVector(0.0f, 0.0f, 1.0f),
        1.0f,
    };
    LptaOBB obb(coordinate, axes);
    LptaAABB aabb = obb.ConvertToAABB();
    
    COORDINATE centre = aabb.GetCentre();
    ASSERT_EQ(0.0f, centre.GetX());
    ASSERT_EQ(0.0f, centre.GetY());
    ASSERT_EQ(0.0f, centre.GetZ());
    
    COORDINATE min = aabb.GetMin();
    ASSERT_EQ(-1.0f, min.GetX());
    ASSERT_EQ(-1.0f, min.GetY());
    ASSERT_EQ(-1.0f, min.GetZ());

    COORDINATE max = aabb.GetMax();
    ASSERT_EQ(1.0f, max.GetX());
    ASSERT_EQ(1.0f, max.GetY());
    ASSERT_EQ(1.0f, max.GetZ());
}

TEST(LptaOBBTest, ConvertToAABBNormalCase_AlignedConvert)
{
    COORDINATE coordinate(1, 0, 0);
    OBB_AXES axes;
    axes[0] = {
        LptaNormalVector(1.0f, 0.0f, 0.0f),
        1.0f,
    };
    axes[1] = {
        LptaNormalVector(0.0f, 1.0f, 0.0f),
        1.0f,
    };
    axes[2] = {
        LptaNormalVector(0.0f, 0.0f, 1.0f),
        1.0f,
    };
    LptaOBB obb(coordinate, axes);
    LptaAABB aabb = obb.ConvertToAABB();

    COORDINATE centre = aabb.GetCentre();
    ASSERT_EQ(1.0f, centre.GetX());
    ASSERT_EQ(0.0f, centre.GetY());
    ASSERT_EQ(0.0f, centre.GetZ());

    COORDINATE min = aabb.GetMin();
    ASSERT_EQ(0.0f, min.GetX());
    ASSERT_EQ(-1.0f, min.GetY());
    ASSERT_EQ(-1.0f, min.GetZ());

    COORDINATE max = aabb.GetMax();
    ASSERT_EQ(2.0f, max.GetX());
    ASSERT_EQ(1.0f, max.GetY());
    ASSERT_EQ(1.0f, max.GetZ());
}

TEST(LptaOBBTest, ConvertToAABBNormalCase_RotatedOriginConvert)
{
    // todo
}