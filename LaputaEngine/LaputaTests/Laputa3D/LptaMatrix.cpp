#include <gtest/gtest.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "LptaVector.h"
#include "LptaNormalVector.h"
#include "LptaMatrix.h"
#include "LptaQuat.h"
#include "errors/InvalidRotationAxis.h"
#include "errors/MatrixInversionError.h"

#define ACCEPTABLE_ERROR 1e-5f

class LptaExposedMatrix : public LptaMatrix
{
public:
    LptaExposedMatrix(void) : LptaMatrix()
    {}
    LptaExposedMatrix(const LptaMatrix &m) : LptaMatrix(m)
    {}

    void AssignAt(unsigned int row, unsigned int col, float val)
    {
        LptaMatrix::AssignAt(row, col, val);
    }
};

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

TEST(LptaMatrixTest, MakeFromQuaternion)
{
    LptaQuat quat(1, 1, 1, 1);
    LptaMatrix matrix = LptaMatrix::MakeFrom(quat);
    float expected[4][4] = {
        { -3.0f, 0.0f, 4.0f, 0.0f },
        { 4.0f, -3.0f, 0.0f, 0.0f },
        { 0.0f, 4.0f, -3.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 1.0f }
    };
    for (unsigned int i = 0; i < 4; ++i) {
        for (unsigned int j = 0; j < 4; ++j) {
            ASSERT_EQ(expected[i][j], matrix.Get(i, j));
        }
    }
}

TEST(LptaMatrixTest, MakeRotateYAxisMatrixNormalCase)
{
    LptaVector v(1.0f, 2.0f, 0.0f);
    LptaMatrix m = LptaMatrix::MakeRotateYAxisMatrix((float)M_PI_2);
    LptaVector rotated = v * m;
    ASSERT_NEAR(0.0f, rotated.GetX(), ACCEPTABLE_ERROR);
    ASSERT_NEAR(2.0f, rotated.GetY(), ACCEPTABLE_ERROR);
    ASSERT_NEAR(-1.0f, rotated.GetZ(), ACCEPTABLE_ERROR);
}

TEST(LptaMatrixTest, MakeRotateXAxisMatrixNormalCase)
{
    LptaVector v(2.0f, 0.0f, -1.0f);
    LptaMatrix m = LptaMatrix::MakeRotateXAxisMatrix((float)M_PI_2);
    LptaVector rotated = v * m;
    ASSERT_NEAR(2.0f, rotated.GetX(), ACCEPTABLE_ERROR);
    ASSERT_NEAR(1.0f, rotated.GetY(), ACCEPTABLE_ERROR);
    ASSERT_NEAR(0.0f, rotated.GetZ(), ACCEPTABLE_ERROR);
}

TEST(LptaMatrixTest, MakeRotateZAxisMatrixNormalCase)
{
    LptaVector v(1.0f, 0.0f, 2.0f);
    LptaMatrix m = LptaMatrix::MakeRotateZAxisMatrix((float)M_PI_2);
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
    ASSERT_NEAR(-1.0f, rotated.GetZ(), ACCEPTABLE_ERROR);

    // simulate x axis rotation
    axis = LptaVector(1.0f, 0.0f, 0.0f);
    v = LptaVector(2.0f, 0.0f, -1.0f);
    m = LptaMatrix::MakeRotationMatrixFor(axis, (float)M_PI_2);
    rotated = v * m;
    ASSERT_NEAR(2.0f, rotated.GetX(), ACCEPTABLE_ERROR);
    ASSERT_NEAR(1.0f, rotated.GetY(), ACCEPTABLE_ERROR);
    ASSERT_NEAR(0.0f, rotated.GetZ(), ACCEPTABLE_ERROR);

    // simulate z axis rotation
    axis = LptaVector(0.0f, 0.0f, 1.0f);
    v = LptaVector(0.0f, 1.0f, 2.0f);
    m = LptaMatrix::MakeRotationMatrixFor(axis, (float)M_PI_2);
    rotated = v * m;
    ASSERT_NEAR(-1.0f, rotated.GetX(), ACCEPTABLE_ERROR);
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

TEST(LptaMatrixTest, MakeInverseForNormalCase_Identity)
{
    LptaMatrix m = LptaMatrix::MakeIdentityMatrix();
    LptaMatrix inverted = LptaMatrix::MakeInverseFor(m);
    for (unsigned int row = 0; row < LPTA_MATRIX_ROWS; ++row) {
        for (unsigned int col = 0; col < LPTA_MATRIX_COLUMNS; ++col) {
            if (row == col) {
                ASSERT_EQ(1.0f, inverted.Get(row, col));
            }
            else {
                ASSERT_EQ(0.0f, inverted.Get(row, col));
            }
        }
    }
}

TEST(LptaMatrixTest, MakeInverseFor_Filled)
{
    LptaExposedMatrix m = LptaMatrix::MakeIdentityMatrix();
    for (unsigned row = 0; row < LPTA_MATRIX_ROWS; ++row) {
        for (unsigned int col = 0; col < LPTA_MATRIX_COLUMNS; ++col) {
            if (row != col) {
                m.AssignAt(row, col, (float)((row * LPTA_MATRIX_ROWS) + col));
            }
        }
    }
    LptaMatrix inverted = LptaMatrix::MakeInverseFor(m);
    const float values[] = {
        -1.149920f, 0.362041f, 0.082935f, 0.003190f,
        0.663477f, -0.314992f, 0.015949f, 0.039075f,
        0.350877f, -0.017544f, -0.087719f, 0.035088f,
        0.261563f, -0.003987f, 0.025518f, -0.037480f,
    };

    for (unsigned int i = 0; i < sizeof(values) / sizeof(float); ++i) {
        unsigned int row = i / LPTA_MATRIX_ROWS;
        unsigned int col = i % LPTA_MATRIX_ROWS;
        ASSERT_NEAR(values[i], inverted.Get(row, col), ACCEPTABLE_ERROR);
    }
}

TEST(LptaMatrixTest, MakeInverseFor_InvalidMatrix)
{
    LptaExposedMatrix m;
    for (unsigned int i = 0; i < LPTA_MATRIX_ROWS * LPTA_MATRIX_COLUMNS; ++i) {
        int row = i / LPTA_MATRIX_ROWS;
        int col = i % LPTA_MATRIX_ROWS;
        m.AssignAt(row, col, (float)i);
    }
    ASSERT_THROW(LptaMatrix::MakeInverseFor(m), MatrixInversionError);
}