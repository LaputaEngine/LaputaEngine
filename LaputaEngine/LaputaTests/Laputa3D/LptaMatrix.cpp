#include <gtest/gtest.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "LptaVector.h"
#include "LptaMatrix.h"
#include "errors/InvalidRotationAxis.h"

#define ACCEPTABLE_ERROR 1e-5f

TEST(LptaMatrixTest, MakeIdentityMatrixNormalCase)
{
    LptaMatrix m = LptaMatrix::MakeIdentityMatrix();
    for (unsigned int row = 0; row < LPTA_MATRIX_ROWS; ++row) {
        for (unsigned int col = 0; col < LPTA_MATRIX_COLUMNS; ++col) {
            if (row == col) {
                ASSERT_EQ(1.0f, m.Get(row, col));
            }
            else {
                ASSERT_EQ(0.0f, m.Get(row, col));
            }
        }
    }
}

TEST(LptaMatrixTest, MakeRotateYAxisMatrixNormalCase)
{
    // rotate cw from x axis to z axis
    LptaVector v(1.0f, 2.0f, 0.0f);
    LptaMatrix m = LptaMatrix::MakeRotateYAxisMatrix((float)M_PI_2);
    LptaVector rotated = v * m;
    ASSERT_NEAR(0.0f, rotated.GetX(), ACCEPTABLE_ERROR);
    ASSERT_NEAR(2.0f, rotated.GetY(), ACCEPTABLE_ERROR);
    ASSERT_NEAR(1.0f, rotated.GetZ(), ACCEPTABLE_ERROR);
}

TEST(LptaMatrixTest, MakeRotateXAxisMatrixNormalCase)
{
    // rotate ccw one quadrant
    LptaVector v(2.0f, 0.0f, -1.0f);
    LptaMatrix m = LptaMatrix::MakeRotateXAxisMatrix((float)M_PI_2);
    LptaVector rotated = v * m;
    ASSERT_NEAR(2.0f, rotated.GetX(), ACCEPTABLE_ERROR);
    ASSERT_NEAR(-1.0f, rotated.GetY(), ACCEPTABLE_ERROR);
    ASSERT_NEAR(0.0f, rotated.GetZ(), ACCEPTABLE_ERROR);
}

TEST(LptaMatrixTest, MakeRotateZAxisMatrixNormalCase)
{
    // rotate cw one quadrant
    LptaVector v(1.0f, 0.0f, 2.0f);
    LptaMatrix m = LptaMatrix::MakeRotateZAxisMatrix((float)-M_PI_2);
    LptaVector rotated = v * m;
    ASSERT_NEAR(0.0f, rotated.GetX(), ACCEPTABLE_ERROR);
    ASSERT_NEAR(1.0f, rotated.GetY(), ACCEPTABLE_ERROR);
    ASSERT_NEAR(2.0f, rotated.GetZ(), ACCEPTABLE_ERROR);
}

TEST(LptaMatrixTest, MakeRotationMatrixForNormalCase)
{
    // simulate y axis rotation
    LptaVector axis(0.0f, 1.0f, 0.0f);
    LptaVector v(1.0f, 2.0f, 0.0f);
    LptaMatrix m = LptaMatrix::MakeRotationMatrixFor(axis, (float)M_PI_2);
    LptaVector rotated = v * m;
    ASSERT_NEAR(0.0f, rotated.GetX(), ACCEPTABLE_ERROR);
    ASSERT_NEAR(2.0f, rotated.GetY(), ACCEPTABLE_ERROR);
    ASSERT_NEAR(1.0f, rotated.GetZ(), ACCEPTABLE_ERROR);

    // simulate x axis rotation
    axis = LptaVector(1.0f, 0.0f, 0.0f);
    v = LptaVector(2.0f, 0.0f, -1.0f);
    m = LptaMatrix::MakeRotationMatrixFor(axis, (float)M_PI_2);
    rotated = v * m;
    ASSERT_NEAR(2.0f, rotated.GetX(), ACCEPTABLE_ERROR);
    ASSERT_NEAR(-1.0f, rotated.GetY(), ACCEPTABLE_ERROR);
    ASSERT_NEAR(0.0f, rotated.GetZ(), ACCEPTABLE_ERROR);

    // simulate z axis rotation
    axis = LptaVector(0.0f, 0.0f, 1.0f);
    v = LptaVector(0.0f, 1.0f, 2.0f);
    m = LptaMatrix::MakeRotationMatrixFor(axis, (float)M_PI_2);
    rotated = v * m;
    ASSERT_NEAR(1.0f, rotated.GetX(), ACCEPTABLE_ERROR);
    ASSERT_NEAR(0.0f, rotated.GetY(), ACCEPTABLE_ERROR);
    ASSERT_NEAR(2.0f, rotated.GetZ(), ACCEPTABLE_ERROR);

    // todo: add real arbitray axis
}

TEST(LptaMatrixTest, MakeRotationMatrixForNotNormalRotationAxis)
{
    LptaVector axis(1.0f, 1.0f, 1.0f);
    LptaVector v(1.0f, 2.0f, 3.0f);
    ASSERT_THROW({
        LptaMatrix m = LptaMatrix::MakeRotationMatrixFor(axis, (float)M_PI_2);
    }, InvalidRotationAxis);
}