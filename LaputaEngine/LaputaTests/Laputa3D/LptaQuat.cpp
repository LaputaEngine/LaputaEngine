#include <gtest/gtest.h>
#include "LptaQuat.h"
using namespace lpta_3d;

TEST(LptaQuatTest, LptaQuatMultiply)
{
    LptaQuat quat0(1.0f, 1.0f, 1.0f, 1.0f);
    LptaQuat quat1(1.0f, 1.0f, 1.0f, 1.0f);
    LptaQuat result = quat0 * quat1;
    ASSERT_EQ(-2.0f, result.GetW());
    ASSERT_EQ(2.0f, result.GetX());
    ASSERT_EQ(2.0f, result.GetY());
    ASSERT_EQ(2.0f, result.GetZ());
}