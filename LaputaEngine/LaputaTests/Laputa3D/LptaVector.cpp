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

TEST(LptaVectorTest, AddToNormalCase)
{
	LptaVector v0(0.0f, 0.0f, 0.0f);
	LptaVector v1(1.0f, 2.0f, 3.0f);
	v0 += v1;
	ASSERT_EQ(1.0f, v0.GetX());
	ASSERT_EQ(2.0f, v0.GetY());
	ASSERT_EQ(3.0f, v0.GetZ());
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