#include <gtest/gtest.h>
#include "LptaPlane.h"
#include "LptaNormalVector.h"
#include "LptaAABB.h"
#include "LptaRay.h"
using namespace lpta_3d;

TEST(LptaRayTest, ContructorNormalCase)
{
    POINT origin(0.0f, 1.0f, 2.0f);
    LptaVector direction(1.0f, 1.0f, 1.0f);
    LptaRay(origin, direction);
}

TEST(LptaRayTest, IntersectsTriangleNormalCase_Intersects)
{
    POINT origin(0.0f, 0.0f, 0.0f);
    LptaVector direction(0.0f, 0.0f, 1.0f);
    LptaRay ray(origin, direction);
    LPTA_TRIANGLE triangle = {
        POINT(0.0f, 1.0f, 0.0f),
        POINT(1.0f, -1.0f, 0.0f),
        POINT(-1.0f, -1.0f, 0.0f),
    };
    ASSERT_TRUE(ray.Intersects(triangle));
}

TEST(LptaRayTest, IntersectsTriangleNormalCase_NoIntersect)
{
    POINT origin(-1.0f, -1.0f, 0.0f);
    LptaVector direction(1.0f, 0.0f, 1.0f);
    LptaRay ray(origin, direction);
    LPTA_TRIANGLE triangle = {
        POINT(0.0f, 1.0f, 0.0f),
        POINT(1.0f, -1.0f, 0.0f),
        POINT(-1.0f, -1.0f, 0.0f),
    };
    ASSERT_FALSE(ray.Intersects(triangle));
}

TEST(LptaRayTest, IntersectsTriangleNormalCase_Intersect)
{
    POINT origin(0.0f, 0.0f, 0.0f);
    LptaVector direction(1.0f, 0.0f, 1.0f);
    LptaRay ray(origin, direction);
    LptaPlane plane(POINT(1.0f, 1.0f, 0.0f), LptaNormalVector(1.0f, 0.0f, 0.0f));
    ASSERT_TRUE(ray.Intersects(plane));
}

TEST(LptaRayTest, IntersectsTriangleNormalCase_NoIntersect_Parallel)
{
    POINT origin(0.0f, 0.0f, 0.0f);
    LptaVector direction(0.0f, 1.0f, 1.0f);
    LptaRay ray(origin, direction);
    LptaPlane plane(POINT(1.0f, 1.0f, 0.0f), LptaNormalVector(1.0f, 0.0f, 0.0f));
    ASSERT_FALSE(ray.Intersects(plane));
}

TEST(LptaRayTest, IntersectsTriangleNormalCase_NoIntersect_OriginOffset)
{
    POINT origin(1.1f, 0.0f, 0.0f);
    LptaVector direction(1.0f, 0.0f, 1.0f);
    LptaRay ray(origin, direction);
    LptaPlane plane(POINT(1.0f, 1.0f, 0.0f), LptaNormalVector(1.0f, 0.0f, 0.0f));
    ASSERT_FALSE(ray.Intersects(plane));
}

TEST(LptaRayTest, IntersectsAABBNormalCase_IntersectInside)
{
    POINT origin(0.0f, 0.0f, 0.0f);
    LptaVector direction(1.0f, 1.0f, 1.0f);
    LptaRay ray(origin, direction);
    LptaAABB bb(POINT(-1.0f, -1.0f, -1.0f), POINT(1.0f, 1.0f, 1.0f));
    ASSERT_TRUE(ray.Intersects(bb));
}

TEST(LptaRayTest, IntersectsAABBNormalCase_IntersectOutside)
{
    POINT origin(-2.0f, -2.0f, -2.0f);
    LptaVector direction(1.0f, 1.0f, 1.0f);
    LptaRay ray(origin, direction);
    LptaAABB bb(POINT(-1.0f, -1.0f, -1.0f), POINT(1.0f, 1.0f, 1.0f));
    ASSERT_TRUE(ray.Intersects(bb));
}

TEST(LptaRayTest, IntersectsAABBNormalCase_NoIntersect)
{
    // barely misses it
    POINT origin(-2.005f, 0.0f, -2.0f);
    LptaVector direction(1.0f, 1.0f, 1.0f);
    LptaRay ray(origin, direction);
    LptaAABB bb(POINT(-1.0f, -1.0f, -1.0f), POINT(1.0f, 1.0f, 1.0f));
    ASSERT_FALSE(ray.Intersects(bb));
}

TEST(LptaRayTest, IntersectsOBB_Intersects)
{
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
    LptaOBB obb(POINT(0.0f, 0.0f, 0.0f), axes);
    LptaRay ray(POINT(-1.5f, 0.5f, -0.5f), LptaNormalVector::MakeFrom(0.2f, 1.0f, 0.2f));
    ASSERT_TRUE(ray.Intersects(obb));
}

TEST(LptaRayTest, IntersectsOBB_NoIntersect)
{
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
    LptaOBB obb(POINT(0.0f, 0.0f, 0.0f), axes);
    LptaRay ray(POINT(-1.5f, 10.5f, -0.5f), LptaNormalVector::MakeFrom(1.0f, 1.0f, 1.0f));
    ASSERT_FALSE(ray.Intersects(obb));
}

TEST(LptaRayTest, IntersectsOBB_Parallel)
{
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
    LptaOBB obb(POINT(0.0f, 0.0f, 0.0f), axes);
    LptaRay ray(POINT(-1.0f, 1.00001f, 0.0f), LptaNormalVector::MakeFrom(1.0f, 0.0f, 0.0f));
    ASSERT_FALSE(ray.Intersects(obb));
}