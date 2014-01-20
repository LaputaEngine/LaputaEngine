#include <gtest/gtest.h>
#include "LptaVector.h"
#include "LptaPlane.h"

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