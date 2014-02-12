#include <gtest/gtest.h>
#include "LptaVector.h"
#include "LptaOBB.h"
#include "LptaAABB.h"
#include "geometry/Shapes.h"
using namespace lpta_3d;

LptaOBB CreateBasicCubeOBB(float x, float y, float z, float extent)
{
    POINT centre(x, y, z);
    OBB_AXES axes;
    axes[0] = {
        LptaNormalVector(1.0f, 0.0f, 0.0f),
        extent,
    };
    axes[1] = {
        LptaNormalVector(0.0f, 1.0f, 0.0f),
        extent,
    };
    axes[2] = {
        LptaNormalVector(0.0f, 0.0f, 1.0f),
        extent,
    };
    return LptaOBB(centre, axes);
}
LptaOBB CreateOriginBaicCubeOBB(float extent)
{
    return CreateBasicCubeOBB(0.0f, 0.0f, 0.0f, extent);
}

TEST(LptaOBBTest, ConvertToAABBNormalCase_AlignedOriginConvert)
{
    
    LptaOBB obb = CreateOriginBaicCubeOBB(1.0f);
    LptaAABB aabb = obb.ConvertToAABB();
    
    POINT obbCentre = aabb.GetCentre();
    ASSERT_EQ(0.0f, obbCentre.GetX());
    ASSERT_EQ(0.0f, obbCentre.GetY());
    ASSERT_EQ(0.0f, obbCentre.GetZ());
    
    POINT min = aabb.GetMin();
    ASSERT_EQ(-1.0f, min.GetX());
    ASSERT_EQ(-1.0f, min.GetY());
    ASSERT_EQ(-1.0f, min.GetZ());

    POINT max = aabb.GetMax();
    ASSERT_EQ(1.0f, max.GetX());
    ASSERT_EQ(1.0f, max.GetY());
    ASSERT_EQ(1.0f, max.GetZ());
}

TEST(LptaOBBTest, ConvertToAABBNormalCase_AlignedConvert)
{
    LptaOBB obb = CreateBasicCubeOBB(1, 0, 0, 1.0f);
    LptaAABB aabb = obb.ConvertToAABB();

    POINT obbCentre = aabb.GetCentre();
    ASSERT_EQ(1.0f, obbCentre.GetX());
    ASSERT_EQ(0.0f, obbCentre.GetY());
    ASSERT_EQ(0.0f, obbCentre.GetZ());

    POINT min = aabb.GetMin();
    ASSERT_EQ(0.0f, min.GetX());
    ASSERT_EQ(-1.0f, min.GetY());
    ASSERT_EQ(-1.0f, min.GetZ());

    POINT max = aabb.GetMax();
    ASSERT_EQ(2.0f, max.GetX());
    ASSERT_EQ(1.0f, max.GetY());
    ASSERT_EQ(1.0f, max.GetZ());
}

TEST(LptaOBBTest, ConvertToAABBNormalCase_RotatedOriginConvert)
{
    // todo
}

TEST(LptaOBBTest, IntersectsOBB_Intersects_AxisAligned)
{
    LptaOBB obb0 = CreateOriginBaicCubeOBB(1.0f);
    LptaOBB obb1 = CreateOriginBaicCubeOBB(1.0f);
    ASSERT_TRUE(obb0.Intersects(obb1));
    ASSERT_TRUE(obb1.Intersects(obb0));

    LptaOBB obb2 = CreateBasicCubeOBB(0.0f, 2.0f, 0.0f, 1.0f);
    ASSERT_TRUE(obb0.Intersects(obb2));
    ASSERT_TRUE(obb2.Intersects(obb0));

    LptaOBB obb3 = CreateBasicCubeOBB(2.0f, 2.0f, 2.0f, 1.0f);
    ASSERT_TRUE(obb0.Intersects(obb3));
    ASSERT_TRUE(obb3.Intersects(obb0));
}

TEST(LptaOBBTest, IntersectsOBB_Intersects)
{
    POINT centre0(0, 0, 0);
    OBB_AXES axes0;
    axes0[0] = {
        LptaNormalVector::MakeFrom(1.0f, 1.0f, 0.0f),
        10.0f,
    };
    axes0[1] = {
        LptaNormalVector::MakeFrom(1.0f, -1.0f, 0.0f),
        10.0f,
    };
    axes0[2] = {
        LptaNormalVector(0.0f, 0.0f, 1.0f),
        10.0f,
    };
    LptaOBB obb0(centre0, axes0);

    LptaOBB obb1 = CreateBasicCubeOBB(0.0f, 15.142f, 0.0f, 1.0f);
    ASSERT_TRUE(obb0.Intersects(obb1));
    ASSERT_TRUE(obb1.Intersects(obb0));
}

TEST(LptaOBBTest, IntersectsOBB_NoIntersect_AxisAligned)
{
    LptaOBB obb0 = CreateOriginBaicCubeOBB(1.0f);
    LptaOBB obb1 = CreateBasicCubeOBB(0.0f, 3.0f, 0.0f, 1.0f);
    ASSERT_FALSE(obb0.Intersects(obb1));
    ASSERT_FALSE(obb1.Intersects(obb0));

    LptaOBB obb2 = CreateBasicCubeOBB(0.0f, 2.0f, 0.0f, 0.0009f);
    ASSERT_FALSE(obb0.Intersects(obb2));
    ASSERT_FALSE(obb2.Intersects(obb0));

    LptaOBB obb3 = CreateBasicCubeOBB(2.0f, 3.0f, 3.0f, 1.0f);
    ASSERT_FALSE(obb0.Intersects(obb3));
    ASSERT_FALSE(obb3.Intersects(obb0));
}

TEST(LptaOBBTest, IntersectsOBB_NoIntersect)
{
    POINT centre0(0, 0, 0);
    OBB_AXES axes0;
    axes0[0] = {
        LptaNormalVector::MakeFrom(1.0f, 1.0f, 0.0f),
        10.0f,
    };
    axes0[1] = {
        LptaNormalVector::MakeFrom(1.0f, -1.0f, 0.0f),
        10.0f,
    };
    axes0[2] = {
        LptaNormalVector(0.0f, 0.0f, 1.0f),
        10.0f,
    };
    LptaOBB obb0(centre0, axes0);

    LptaOBB obb1 = CreateBasicCubeOBB(0.0f, 15.1422f, 0.0f, 1.0f);
    ASSERT_FALSE(obb0.Intersects(obb1));
    ASSERT_FALSE(obb1.Intersects(obb0));
}

TEST(LptaOBBTest, IntersectsOBB_IntersectsTriangle_AxisAligned)
{
    LptaOBB obb = CreateOriginBaicCubeOBB(1.0f);
    LPTA_TRIANGLE triangle = {
        POINT(0.0f, 0.0f, 0.0f),
        POINT(10.0f, 10.0f, 10.0f),
        POINT(-10.0f, -5.0f, 3.0f)
    };
    ASSERT_TRUE(obb.Intersects(triangle));
}

TEST(LptaOBBTest, IntersectsTriangle_NoIntersect)
{
    LptaOBB obb = CreateOriginBaicCubeOBB(1.0f);
    LPTA_TRIANGLE triangle = {
        POINT(1.0f, 1.0f, 0.0f),
        POINT(2.0f, 0.0f, 1.0f),
        POINT(20.0f, 0.0f, -1.0f)
    };
    ASSERT_FALSE(obb.Intersects(triangle));
}