#include "LptaD3DMatrix.h"

#define MATRIX_ROWS 4
#define MATRIX_COLS 4

namespace lpta_d3d
{

LptaD3DMatrix::LptaD3DMatrix(const lpta_3d::LptaMatrix &m) : LptaMatrix(m)
{
}

LptaD3DMatrix::LptaD3DMatrix(void)
{
}

LptaD3DMatrix::~LptaD3DMatrix(void)
{
}

LptaD3DMatrix LptaD3DMatrix::MakeFrom(const D3DXMATRIX &m)
{
    LptaD3DMatrix result;
    for (unsigned int row = 0; row < MATRIX_ROWS; ++row) {
        for (unsigned int col = 0; col < MATRIX_COLS; ++col) {
            result.AssignAt(row, col, ((float *)(&m))[row * MATRIX_COLS + col]);
        }
    }
    return result;
}


D3DXMATRIX LptaD3DMatrix::ConvertToDxMatrix(void) const
{
    D3DXMATRIX result;
    for (unsigned int row = 0; row < MATRIX_ROWS; ++row) {
        for (unsigned int col = 0; col < MATRIX_COLS; ++col) {
            ((float *)(&result))[row * MATRIX_COLS + col] = this->Get(row, col);
        }
    }
    return result;
}

}