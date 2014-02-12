#include <gtest/gtest.h>
#include "LptaVector.h"
#include "LptaNormalVector.h"
#include "LptaBoundingBox.h"
#include "LptaRay.h"
#include "LptaAABB.h"
using namespace lpta_3d;

TEST(LptaAABBTest, PlanesNormalCase)
{
    LptaAABB bb(POINT(-1.0f, -1.0f, -1.0f), POINT(1.0f, 1.0f, 1.0f));
    LptaBBPlanes planes = bb.GetPlanes();
    LptaRay frontToBack(POINT(0.0f, 0.0f, -1.5f), LptaVector(0.0f, 0.0f, 1.0f));
    ASSERT_TRUE(frontToBack.Intersects(planes[planes.FRONT]));
    LptaRay backToFront(POINT(0.0f, 0.0f, 1.5f), LptaVector(0.0f, 0.0f, -1.0f));
    ASSERT_TRUE(backToFront.Intersects(planes[planes.BACK]));
    LptaRay leftToRight(POINT(-1.5f, 0.0f, 0.0f), LptaVector(1.0f, 0.0f, 0.0f));
    ASSERT_TRUE(leftToRight.Intersects(planes[planes.LEFT]));
    LptaRay rightToLeft(POINT(1.5f, 0.0f, 0.0f), LptaVector(-1.0f, 0.0f, 0.0f));
    ASSERT_TRUE(rightToLeft.Intersects(planes[planes.RIGHT]));
    LptaRay topToBottom(POINT(0.0f, 1.0f, 0.0f), LptaVector(0.0f, -1.0f, 0.0f));
    ASSERT_TRUE(topToBottom.Intersects(planes[planes.TOP]));
    LptaRay bottomToTop(POINT(0.0f, -1.0f, 0.0f), LptaVector(0.0f, 1.0f, 0.0f));
    ASSERT_TRUE(bottomToTop.Intersects(planes[planes.BOTTOM]));
}