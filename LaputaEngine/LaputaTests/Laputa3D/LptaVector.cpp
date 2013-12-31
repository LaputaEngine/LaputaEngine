#include <gtest/gtest.h>
#include "LptaVector.h"

TEST(LptaVectorTest, AddToNormalCase)
{
	LptaVector v0(0.0f, 0.0f, 0.0f);
	LptaVector v1(1.0f, 2.0f, 3.0f);
	v0 += v1;
	ASSERT_EQ(1.0f, v0.GetX());
	ASSERT_EQ(2.0f, v0.GetY());
	ASSERT_EQ(3.0f, v0.GetZ());
}