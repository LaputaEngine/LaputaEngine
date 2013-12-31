#include <gtest/gtest.h>
#include "LptaVector.h"

class LptaVectorNoSSETest : public ::testing::Test, LptaVector
{
protected:
    virtual void SetUp(void)
    {
        oldSSECapable = sseCapable;
        sseCapable = false;
    }

    virtual void TearDown(void)
    {
        sseCapable = oldSSECapable;
    }

private:
    bool oldSSECapable;
};

TEST(LptaVectorTest, VectorGettersNormalCase)
{
    LptaVector v(0.0f, 1.0f, 2.0f);
    ASSERT_EQ(v.GetX(), 0.0f);
    ASSERT_EQ(v.GetY(), 1.0f);
    ASSERT_EQ(v.GetZ(), 2.0f);
}

TEST(LptaVectorTest, LengthNormalCase)
{
    LptaVector v(1.0f, 2.0f, 2.0f);
    ASSERT_EQ(3.0f, v.Length());
}

TEST_F(LptaVectorNoSSETest, LengthNormalCase)
{
    ::LptaVector v(1.0f, 2.0f, 2.0f);
    ASSERT_EQ(3.0f, v.Length());
}

TEST(LptaVectorTest, AddToNormalCase)
{
    LptaVector v0(0.0f, 0.0f, 0.0f);
    LptaVector v1(1.0f, 2.0f, 3.0f);
    v0 += v1;
    ASSERT_EQ(1.0f, v0.GetX());
    ASSERT_EQ(2.0f, v0.GetY());
    ASSERT_EQ(3.0f, v0.GetZ());
}

TEST(LptaVectorTest, SubtractFromNormalCase)
{
    LptaVector v0(2.0f, 3.0f, 4.0f);
    LptaVector v1(1.0f, 1.0f, 1.0f);
    v0 -= v1;
    ASSERT_EQ(1.0f, v0.GetX());
    ASSERT_EQ(2.0f, v0.GetY());
    ASSERT_EQ(3.0f, v0.GetZ());
}

TEST(LptaVectorTest, MultipliedByNormalCase)
{
    LptaVector v0(1.0f, 2.0f, 3.0f);
    LptaVector v1(2.0f, 2.0f, 2.0f);
    v0 *= v1;
    ASSERT_EQ(2.0f, v0.GetX());
    ASSERT_EQ(4.0f, v0.GetY());
    ASSERT_EQ(6.0f, v0.GetZ());
}

TEST(LptaVectorTest, DividedByNormalCase)
{
    LptaVector v0(4.0f, 6.0f, 8.0f);
    LptaVector v1(2.0f, 2.0f, 2.0f);
    v0 /= v1;
    ASSERT_EQ(2.0f, v0.GetX());
    ASSERT_EQ(3.0f, v0.GetY());
    ASSERT_EQ(4.0f, v0.GetZ());
}

TEST(LptaVectorTest, MultiplyByVectorNormalCase)
{
    LptaVector v0(1.0f, 2.0f, 3.0f);
    LptaVector v1(4.0f, 5.0f, 6.0f);
    float f = v0 * v1;
    ASSERT_EQ(f, 32.0f);
}

TEST(LptaVectorTest, MultiplyByScalarNormalCase)
{
    LptaVector v0(1.0f, 2.0f, 3.0f);
    LptaVector v1 = v0 * 2.0f;
    ASSERT_EQ(2.0f, v1.GetX());
    ASSERT_EQ(4.0f, v1.GetY());
    ASSERT_EQ(6.0f, v1.GetZ());
}

TEST(LptaVectorTest, AddVectorsNormalCase)
{
    LptaVector v0(4.0f, 6.0f, 8.0f);
    LptaVector v1(2.0f, 2.0f, 2.0f);
    LptaVector v2 = v0 + v1;
    ASSERT_EQ(6.0f, v2.GetX());
    ASSERT_EQ(8.0f, v2.GetY());
    ASSERT_EQ(10.0f, v2.GetZ());
}

TEST(LptaVectorTest, SubtractVectorsNormalCase)
{
    LptaVector v0(4.0f, 6.0f, 8.0f);
    LptaVector v1(2.0f, 2.0f, 2.0f);
    LptaVector v2 = v0 - v1;
    ASSERT_EQ(2.0f, v2.GetX());
    ASSERT_EQ(4.0f, v2.GetY());
    ASSERT_EQ(6.0f, v2.GetZ());
}