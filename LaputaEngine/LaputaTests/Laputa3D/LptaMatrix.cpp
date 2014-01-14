#include <gtest/gtest.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "LptaVector.h"
#include "LptaMatrix.h"

#define ACCEPTABLE_ERROR 1e-5f

TEST(LptaMatrixTest, MakeIdentityMatrixNormalCase)
{
    LPTA_MATRIX m = LptaMatrix::MakeIdentityMatrix();
    for (unsigned int row = 0; row < LPTA_MATRIX_ROWS; ++row) {
        for (unsigned int col = 0; col < LPTA_MATRIX_COLUMNS; ++col) {
            if (row == col) {
                ASSERT_EQ(1.0f, m->Get(row, col));
            }
            else {
                ASSERT_EQ(0.0f, m->Get(row, col));
            }
        }
    }
}

TEST(LptaMatrixTest, MakeRotateYAxisMatrixNormalCase)
{
	// rotate cw from x axis to z axis
	LptaVector v(1.0f, 2.0f, 0.0f);
	LPTA_MATRIX m = LptaMatrix::MakeRotateYAxisMatrix((float)M_PI_2);
	LptaVector rotated = v * m;
	ASSERT_NEAR(0.0f, rotated.GetX(), ACCEPTABLE_ERROR);
	ASSERT_NEAR(2.0f, rotated.GetY(), ACCEPTABLE_ERROR);
	ASSERT_NEAR(1.0f, rotated.GetZ(), ACCEPTABLE_ERROR);
}

TEST(LptaMatrixTest, MakeRotateXAxisMatrixNormalCase)
{
	// rotate ccw one quadrant
	LptaVector v(2.0f, 0.0f, -1.0f);
	LPTA_MATRIX m = LptaMatrix::MakeRotateXAxisMatrix((float)M_PI_2);
	LptaVector rotated = v * m;
	ASSERT_NEAR(2.0f, rotated.GetX(), ACCEPTABLE_ERROR);
	ASSERT_NEAR(-1.0f, rotated.GetY(), ACCEPTABLE_ERROR);
	ASSERT_NEAR(0.0f, rotated.GetZ(), ACCEPTABLE_ERROR);
}

TEST(LptaMatrixTest, MakeRotateZAxisMatrixNormalCase)
{
	// rotate cw one quadrant
	LptaVector v(1.0f, 0.0f, 2.0f);
	LPTA_MATRIX m = LptaMatrix::MakeRotateZAxisMatrix((float)-M_PI_2);
	LptaVector rotated = v * m;
	ASSERT_NEAR(0.0f, rotated.GetX(), ACCEPTABLE_ERROR);
	ASSERT_NEAR(1.0f, rotated.GetY(), ACCEPTABLE_ERROR);
	ASSERT_NEAR(2.0f, rotated.GetZ(), ACCEPTABLE_ERROR);
}