#include "LptaMatrix.h"

LptaMatrix::~LptaMatrix(void)
{
}

LPTA_MATRIX LptaMatrix::MakeIdentityMatrix(void)
{
    LPTA_MATRIX matrix = LPTA_MATRIX(new LptaMatrix());
    matrix->AssignAt(0, 0, 1.0f);
    matrix->AssignAt(1, 1, 1.0f);
    matrix->AssignAt(2, 2, 1.0f);
    matrix->AssignAt(3, 3, 1.0f);
    return matrix;
}

LptaMatrix::LptaMatrix(void)
{
    for (unsigned int row = 0; row < LPTA_MATRIX_ROWS; ++row) {
        for (unsigned int col = 0; col < LPTA_MATRIX_COLUMNS; ++col) {
            m.at(row).fill(0.0f);
        }
    }
}