#include <gtest/gtest.h>
#include "LptaPlane.h"
#include "LptaNormalVector.h"
#include "LptaAABB.h"
#include "LptaRay.h"

TEST(LptaRayTest, ContructorNormalCase)
{
	COORDINATE origin(0.0f, 1.0f, 2.0f);
	LptaVector direction(1.0f, 1.0f, 1.0f);
	LptaRay(origin, direction);
}

TEST(LptaRayTest, IntersectsTriangleNormalCase_Intersects)
{
	COORDINATE origin(0.0f, 0.0f, 0.0f);
	LptaVector direction(0.0f, 0.0f, 1.0f);
	LptaRay ray(origin, direction);
	LPTA_TRIANGLE triangle = {
		COORDINATE(0.0f, 1.0f, 0.0f),
		COORDINATE(1.0f, -1.0f, 0.0f),
		COORDINATE(-1.0f, -1.0f, 0.0f),
	};
	ASSERT_TRUE(ray.Intersects(triangle));
}

TEST(LptaRayTest, IntersectsTriangleNormalCase_NoIntersect)
{
	COORDINATE origin(-1.0f, -1.0f, 0.0f);
	LptaVector direction(1.0f, 0.0f, 1.0f);
	LptaRay ray(origin, direction);
	LPTA_TRIANGLE triangle = {
		COORDINATE(0.0f, 1.0f, 0.0f),
		COORDINATE(1.0f, -1.0f, 0.0f),
		COORDINATE(-1.0f, -1.0f, 0.0f),
	};
	ASSERT_FALSE(ray.Intersects(triangle));
}

TEST(LptaRayTest, IntersectsTriangleNormalCase_Intersect)
{
	COORDINATE origin(0.0f, 0.0f, 0.0f);
	LptaVector direction(1.0f, 0.0f, 1.0f);
	LptaRay ray(origin, direction);
	LptaPlane plane(COORDINATE(1.0f, 1.0f, 0.0f), LptaNormalVector(1.0f, 0.0f, 0.0f));
	ASSERT_TRUE(ray.Intersects(plane));
}

TEST(LptaRayTest, IntersectsTriangleNormalCase_NoIntersect_Parallel)
{
	COORDINATE origin(0.0f, 0.0f, 0.0f);
	LptaVector direction(0.0f, 1.0f, 1.0f);
	LptaRay ray(origin, direction);
	LptaPlane plane(COORDINATE(1.0f, 1.0f, 0.0f), LptaNormalVector(1.0f, 0.0f, 0.0f));
	ASSERT_FALSE(ray.Intersects(plane));
}

TEST(LptaRayTest, IntersectsTriangleNormalCase_NoIntersect_OriginOffset)
{
	COORDINATE origin(1.1f, 0.0f, 0.0f);
	LptaVector direction(1.0f, 0.0f, 1.0f);
	LptaRay ray(origin, direction);
	LptaPlane plane(COORDINATE(1.0f, 1.0f, 0.0f), LptaNormalVector(1.0f, 0.0f, 0.0f));
	ASSERT_FALSE(ray.Intersects(plane));
}

TEST(LptaRayTest, IntersectsAABBNormalCase_IntersectInside)
{
	COORDINATE origin(0.0f, 0.0f, 0.0f);
	LptaVector direction(1.0f, 1.0f, 1.0f);
	LptaRay ray(origin, direction);
	LptaAABB bb(COORDINATE(-1.0f, -1.0f, -1.0f), COORDINATE(1.0f, 1.0f, 1.0f));
	ASSERT_TRUE(ray.Intersects(bb));
}

TEST(LptaRayTest, IntersectsAABBNormalCase_IntersectOutside)
{
	COORDINATE origin(-2.0f, -2.0f, -2.0f);
	LptaVector direction(1.0f, 1.0f, 1.0f);
	LptaRay ray(origin, direction);
	LptaAABB bb(COORDINATE(-1.0f, -1.0f, -1.0f), COORDINATE(1.0f, 1.0f, 1.0f));
	ASSERT_TRUE(ray.Intersects(bb));
}

TEST(LptaRayTest, IntersectsAABBNormalCase_NoIntersect)
{
	// barely misses it
	COORDINATE origin(-2.005f, 0.0f, -2.0f);
	LptaVector direction(1.0f, 1.0f, 1.0f);
	LptaRay ray(origin, direction);
	LptaAABB bb(COORDINATE(-1.0f, -1.0f, -1.0f), COORDINATE(1.0f, 1.0f, 1.0f));
	ASSERT_FALSE(ray.Intersects(bb));
}