#include <gtest/gtest.h>
#include "LptaVector.h"
#include "LptaAABB.h"
#include "LptaObb.h"
#include "LptaPlane.h"
#include "geometry/Shapes.h"

TEST(LptaPlaneTest, IntersectsNormalCase_Intersects)
{
	LptaPlane plane0(COORDINATE(0.0f, 0.0f, 0.0f), LptaNormalVector(1.0f, 0.0f, 0.0f));
	LptaPlane plane1(COORDINATE(0.0f, 0.0f, 0.0f), LptaNormalVector(0.0f, -1.0f, 0.0f));
	ASSERT_TRUE(plane0.Intersects(plane1));
}

TEST(LptaPlaneTest, IntersectsNormalCase_NoIntersect)
{
	LptaPlane plane0(COORDINATE(0.0f, 0.0f, 0.0f), LptaNormalVector(1.0f, 0.0f, 0.0f));
	LptaPlane plane1(COORDINATE(0.0f, 1.0f, 0.0f), LptaNormalVector(1.0f, 0.0f, 0.0f));
	ASSERT_FALSE(plane0.Intersects(plane1));
}

TEST(LptaPlaneTest, IntersectsOverlapping_NoIntersect)
{
	LptaPlane plane0(COORDINATE(0.0f, 0.0f, 0.0f), LptaNormalVector(1.0f, 0.0f, 0.0f));
	LptaPlane plane1(COORDINATE(0.0f, 0.0f, 0.0f), LptaNormalVector(-1.0f, 0.0f, 0.0f));
	ASSERT_FALSE(plane0.Intersects(plane1));
}

TEST(LptaPlaneTest, IntersectsTriangle_Intersects)
{
    LptaPlane plane(COORDINATE(0.0f, 0.0f, 0.0f), LptaNormalVector::MakeFrom(0.0f, 1.0f, 0.0f));
    LPTA_TRIANGLE triangle = {
        COORDINATE(0.0f, 1.0f, 0.0f),
        COORDINATE(1.0f, -1.0f, 1.0f),
        COORDINATE(-1.0f, -1.0f, 0.0f)
    };
    ASSERT_TRUE(plane.Intersects(triangle));
}

TEST(LptaPlaneTest, IntersectsTriangle_NoIntersect)
{
    LptaPlane plane(COORDINATE(0.0f, 0.0f, 0.0f), LptaNormalVector::MakeFrom(0.0f, 1.0f, 0.0f));
    LPTA_TRIANGLE triangle = {
        COORDINATE(0.0f, 1.0f, 0.0f),
        COORDINATE(1.0f, 0.5f, 1.0f),
        COORDINATE(-1.0f, 0.5f, 0.0f)
    };
    ASSERT_FALSE(plane.Intersects(triangle));
}

TEST(LptaPlaneTest, IntersectsAABBNormalCase_Intersects)
{
	LptaPlane plane(COORDINATE(0.0f, 0.0f, 0.0f), LptaNormalVector(0.0f, 1.0f, 0.0f));
	LptaAABB aabb(COORDINATE(-1.0f, -1.0f, -1.0f), COORDINATE(1.0f, 1.0f, 1.0f));
	ASSERT_TRUE(plane.Intersects(aabb));
}

TEST(LptaPlaneTest, IntersectsAABBNormalCase_NoIntersect)
{
	LptaPlane plane(COORDINATE(-1.00005f, 1.0f, 0.0f), 
        LptaNormalVector::MakeFrom(-1.0f, 1.0f, 0.0f));
	LptaAABB aabb(COORDINATE(-1.0f, -1.0f, -1.0f), COORDINATE(1.0f, 1.0f, 1.0f));
	ASSERT_FALSE(plane.Intersects(aabb));
}

TEST(LptaPlaneTest, IntersectsOBB_Intersects)
{
    LptaPlane plane(COORDINATE(0.0f, 0.0f, 0.0f),
        LptaNormalVector::MakeFrom(1.0f, 1.0f, 0.0f));
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
    LptaOBB obb(COORDINATE(1.0f, 1.0f, 0.0f), axes);
    ASSERT_TRUE(plane.Intersects(obb));
}

TEST(LptaPlaneTest, IntersectOBB_NoIntersect)
{
    LptaPlane plane(COORDINATE(0.0f, 0.0f, 0.0f),
        LptaNormalVector::MakeFrom(-1.0f, 1.0f, 0.0f));
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
    LptaOBB obb(COORDINATE(-1.00005f, 1.0f, 0.0f), axes);
    ASSERT_FALSE(plane.Intersects(obb));
}