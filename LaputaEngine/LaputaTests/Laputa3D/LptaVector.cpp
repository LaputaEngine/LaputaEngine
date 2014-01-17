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
    ASSERT_EQ(0.0f, v.GetX());
    ASSERT_EQ(1.0f, v.GetY());
    ASSERT_EQ(2.0f, v.GetZ());
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

TEST(LptaVectorTest, NormalizeNormalCase)
{
    LptaVector v(1.0f, 2.0f, 2.0f);
    v.Normalize();
    ASSERT_NEAR(1.0f / 3.0f, v.GetX(), 0.001);
    ASSERT_NEAR(2.0f / 3.0f, v.GetY(), 0.001);
    ASSERT_NEAR(2.0f / 3.0f, v.GetZ(), 0.001);
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

TEST(LptaVectorTest, MultipleByMatrixNormalCase)
{
    LptaVector v(1.0f, 2.0f, 3.0f);
    LPTA_MATRIX m = LptaMatrix::MakeIdentityMatrix();
    LptaVector result = v * m;
    ASSERT_EQ(1.0f, result.GetX());
    ASSERT_EQ(2.0f, result.GetY());
    ASSERT_EQ(3.0f, result.GetZ());
}

TEST_F(LptaVectorNoSSETest, MultipleByMatrixNormalCase)
{
    ::LptaVector v(1.0f, 2.0f, 3.0f);
    LPTA_MATRIX m = LptaMatrix::MakeIdentityMatrix();
    ::LptaVector result = v * m;
    ASSERT_EQ(1.0f, result.GetX());
    ASSERT_EQ(2.0f, result.GetY());
    ASSERT_EQ(3.0f, result.GetZ());
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

// todo: **** NOTE **** see notes in implementation file.
TEST(LptaVectorTest, CrossVectorNormalCaseX)
{
	LptaVector u(0.0f, 0.0f, 1.0f);
	LptaVector v(0.0f, 1.0f, 0.0f);
	LptaVector crossProduct = u.Cross(v);
	ASSERT_EQ(-1.0f, crossProduct.GetX());
	ASSERT_EQ(0.0f, crossProduct.GetY());
	ASSERT_EQ(0.0f, crossProduct.GetZ());
}

TEST(LptaVectorTest, CrossVectorNormalCaseY)
{
	LptaVector u(1.0f, 0.0f, 0.0f);
	LptaVector v(0.0f, 0.0f, 1.0f);
	LptaVector crossProduct = u.Cross(v);
	ASSERT_EQ(0.0f, crossProduct.GetX());
	ASSERT_EQ(-1.0f, crossProduct.GetY());
	ASSERT_EQ(0.0f, crossProduct.GetZ());
}

TEST(LptaVectorTest, CrossVectorNormalCaseZ)
{
	LptaVector u(1.0f, 0.0f, 0.0f);
	LptaVector v(0.0f, 1.0f, 0.0f);
	LptaVector crossProduct = u.Cross(v);
	ASSERT_EQ(0.0f, crossProduct.GetX());
	ASSERT_EQ(0.0f, crossProduct.GetY());
	ASSERT_EQ(1.0f, crossProduct.GetZ());
}

TEST(LptaVectorTest, CrossVectorNormalCaseArbitrary)
{
	LptaVector u(1.0f, 2.0f, 3.0f);
	LptaVector v(4.0f, 2.0f, 9.0f);
	LptaVector crossProduct = u.Cross(v);
	ASSERT_EQ(12.0f, crossProduct.GetX());
	ASSERT_EQ(3.0f, crossProduct.GetY());
	ASSERT_EQ(-6.0f, crossProduct.GetZ());
}