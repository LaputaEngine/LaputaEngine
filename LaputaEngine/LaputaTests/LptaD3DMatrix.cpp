#include <gtest/gtest.h>
#include <d3dx9.h>
#include "LptaD3DMatrix.h"
using lpta_d3d::LptaD3DMatrix;

#define MATRIX_ROWS 4
#define MATRIX_COLS 4

TEST(LptaD3DMatrix, MakeFrom_D3DXMATRIX)
{
    D3DXMATRIX m = {
        0.0f, 1.0f, 2.0f, 3.0f,
        1.0f, 2.0f, 4.0f, 7.0f,
        2.0f, 4.0f, 8.0f, 15.0f,
        3.0f, 7.0f, 15.0f, 30.0f,
    };
    LptaD3DMatrix conv = LptaD3DMatrix::MakeFrom(m);
    for (unsigned int row = 0; row < MATRIX_ROWS; ++row) {
        for (unsigned int col = 0; col < MATRIX_COLS; ++col) {
            ASSERT_EQ(m.m[col][row], conv.Get(row, col));
        }
    }
}

TEST(LptaD3DMatrix, ConvertToDxMatrix)
{
    D3DXMATRIX m = {
        0.0f, 1.0f, 2.0f, 3.0f,
        1.0f, 2.0f, 4.0f, 7.0f,
        2.0f, 4.0f, 8.0f, 15.0f,
        3.0f, 7.0f, 15.0f, 30.0f,
    };
    LptaD3DMatrix lptaMatrix = LptaD3DMatrix::MakeFrom(m);
    D3DMATRIX convertedBack = lptaMatrix.ConvertToDxMatrix();
    for (unsigned int row = 0; row < MATRIX_ROWS; ++row) {
        for (unsigned int col = 0; col < MATRIX_COLS; ++col) {
            ASSERT_EQ(m.m[col][row], convertedBack.m[row][col]);
        }
    }
}

TEST(LptaD3DMatrix, CastTo_LptaMatrix)
{
    D3DXMATRIX m;
    D3DXMatrixIdentity(&m);
    LptaD3DMatrix d3dM = LptaD3DMatrix::MakeFrom(m);

    lpta_3d::LptaMatrix baseM = static_cast<lpta_3d::LptaMatrix>(d3dM);
    for (unsigned int row = 0; row < MATRIX_ROWS; ++row) {
        for (unsigned int col = 0; col < MATRIX_COLS; ++col) {
            if (row == col) {
                ASSERT_EQ(1.0f, baseM.Get(row, col));
            }
            else {
                ASSERT_EQ(0.0f, baseM.Get(row, col));
            }
        }
    }
}