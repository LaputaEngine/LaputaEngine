#include <gtest/gtest.h>
#include "LptaVector.h"
#include "LptaNormalVector.h"
#include "LptaBoundingBox.h"
#include "LptaRay.h"
#include "LptaAABB.h"

TEST(LptaAABBTest, PlanesNormalCase)
{
	LptaAABB bb(COORDINATE(-1.0f, -1.0f, -1.0f), COORDINATE(1.0f, 1.0f, 1.0f));
	LptaBBPlanes planes = bb.GetPlanes();
	LptaRay frontToBack(COORDINATE(0.0f, 0.0f, -1.5f), LptaVector(0.0f, 0.0f, 1.0f));
	ASSERT_TRUE(frontToBack.Intersects(planes[planes.FRONT]));
	LptaRay backToFront(COORDINATE(0.0f, 0.0f, 1.5f), LptaVector(0.0f, 0.0f, -1.0f));
	ASSERT_TRUE(backToFront.Intersects(planes[planes.BACK]));
	LptaRay leftToRight(COORDINATE(-1.5f, 0.0f, 0.0f), LptaVector(1.0f, 0.0f, 0.0f));
	ASSERT_TRUE(leftToRight.Intersects(planes[planes.LEFT]));
	LptaRay rightToLeft(COORDINATE(1.5f, 0.0f, 0.0f), LptaVector(-1.0f, 0.0f, 0.0f));
	ASSERT_TRUE(rightToLeft.Intersects(planes[planes.RIGHT]));
	LptaRay topToBottom(COORDINATE(0.0f, 1.0f, 0.0f), LptaVector(0.0f, -1.0f, 0.0f));
	ASSERT_TRUE(topToBottom.Intersects(planes[planes.TOP]));
	LptaRay bottomToTop(COORDINATE(0.0f, -1.0f, 0.0f), LptaVector(0.0f, 1.0f, 0.0f));
	ASSERT_TRUE(bottomToTop.Intersects(planes[planes.BOTTOM]));
}