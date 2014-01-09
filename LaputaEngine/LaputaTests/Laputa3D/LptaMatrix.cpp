#include <gtest/gtest.h>
#include "LptaMatrix.h"

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