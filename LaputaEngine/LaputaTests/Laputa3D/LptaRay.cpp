#include <gtest/gtest.h>
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