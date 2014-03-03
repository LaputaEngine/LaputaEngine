#include <gtest/gtest.h>
#include "LptaNormalVector.h"
using namespace lpta_3d;

TEST(LptaNormalVectorTest, SetX)
{
    LptaNormalVector v = LptaNormalVector::MakeFrom(2.0f, 1.0f, 3.0f);
    ASSERT_TRUE(v.IsNormal());
    v.SetX(0.5f);
    ASSERT_TRUE(v.IsNormal());
}

TEST(LptaNormalVectorTest, SetY)
{
    LptaNormalVector v = LptaNormalVector::MakeFrom(2.0f, 1.0f, 3.0f);
    ASSERT_TRUE(v.IsNormal());
    v.SetY(0.5f);
    ASSERT_TRUE(v.IsNormal());
}

TEST(LptaNormalVectorTest, SetZ)
{
    LptaNormalVector v = LptaNormalVector::MakeFrom(2.0f, 1.0f, 3.0f);
    ASSERT_TRUE(v.IsNormal());
    v.SetX(0.5f);
    ASSERT_TRUE(v.IsNormal());
}