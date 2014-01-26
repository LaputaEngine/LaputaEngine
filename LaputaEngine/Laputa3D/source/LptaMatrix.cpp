/* Resources used:
 * http://www.geometrictools.com/Documentation/LaplaceExpansionTheorem.pdf
 */

#include <math.h>
#include "LptaVector.h"
#include "Lpta3D.h"
#include "errors/InvalidRotationAxis.h"
#include "errors/MatrixInversionError.h"
#include "LptaMatrix.h"

#define SKIP_ZEROING true

LptaMatrix::~LptaMatrix(void)
{
}

LptaMatrix LptaMatrix::MakeIdentityMatrix(void)
{
    LptaMatrix matrix;
    matrix.AssignAt(0, 0, 1.0f);
    matrix.AssignAt(1, 1, 1.0f);
    matrix.AssignAt(2, 2, 1.0f);
    matrix.AssignAt(3, 3, 1.0f);
    return matrix;
}


LptaMatrix LptaMatrix::MakeRotateXAxisMatrix(float rad)
{
    float radCos = cos(rad);
    float radSin = sin(rad);
    LptaMatrix matrix;

    matrix.AssignAt(0, 0, 1.0f);
    matrix.AssignAt(3, 3, 1.0f);

    matrix.AssignAt(1, 1, radCos);
    matrix.AssignAt(1, 2, -radSin);
    matrix.AssignAt(2, 1, radSin);
    matrix.AssignAt(2, 2, radCos);
    return matrix;
}

LptaMatrix LptaMatrix::MakeRotateYAxisMatrix(float rad)
{
    float radCos = cos(rad);
    float radSin = sin(rad);
    LptaMatrix matrix;

    matrix.AssignAt(1, 1, 1.0f);
    matrix.AssignAt(3, 3, 1.0f);

    matrix.AssignAt(0, 0, radCos);
    matrix.AssignAt(0, 2, radSin);
    matrix.AssignAt(2, 0, -radSin);
    matrix.AssignAt(2, 2, radCos);
    return matrix;
}

LptaMatrix LptaMatrix::MakeRotateZAxisMatrix(float rad)
{
    float radCos = cos(rad);
    float radSin = sin(rad);
    LptaMatrix matrix;

    matrix.AssignAt(2, 2, 1.0f);
    matrix.AssignAt(3, 3, 1.0f);

    matrix.AssignAt(0, 0, radCos);
    matrix.AssignAt(0, 1, -radSin);
    matrix.AssignAt(1, 0, radSin);
    matrix.AssignAt(1, 1, radCos);
    return matrix;
}

LptaMatrix LptaMatrix::MakeRotationMatrixFor(const LptaVector &v, float rad)
{
    if (!v.IsNormal()) {
        throw InvalidRotationAxis(v);
    }

    float radCos = cos(rad);
    float radSin = sin(rad);
    float cosDiff = (1 - radCos);
    LptaMatrix matrix;

    matrix.AssignAt(3, 3, 1.0f);

    matrix.AssignAt(0, 0, radCos + pow(v.GetX(), 2) * cosDiff);
    matrix.AssignAt(0, 1, v.GetX() * v.GetY() * cosDiff - v.GetZ() * radSin);
    matrix.AssignAt(0, 2, v.GetX() * v.GetZ() * cosDiff + v.GetY() * radSin);

    matrix.AssignAt(1, 0, v.GetY() * v.GetX() * cosDiff + v.GetZ() * radSin);
    matrix.AssignAt(1, 1, radCos + pow(v.GetY(), 2) * cosDiff);
    matrix.AssignAt(1, 2, v.GetY() * v.GetZ() * cosDiff - v.GetX() * radSin);

    matrix.AssignAt(2, 0, v.GetZ() * v.GetX() * cosDiff - v.GetY() * radSin);
    matrix.AssignAt(2, 1, v.GetZ() * v.GetY() * cosDiff + v.GetX() * radSin);
    matrix.AssignAt(2, 2, radCos + pow(v.GetZ(), 2) * cosDiff);
    
    return matrix;
}

// uses the Laplace Expansion Theorem to compute matrix inverse
LptaMatrix LptaMatrix::MakeInverseFor(const LptaMatrix &m)
{
    LptaMatrix inverse;
    
    float s0 = m.Get(0, 0) * m.Get(1, 1) - m.Get(0, 1) * m.Get(1, 0);
    float s1 = m.Get(0, 0) * m.Get(1, 2) - m.Get(0, 2) * m.Get(1, 0);
    float s2 = m.Get(0, 0) * m.Get(1, 3) - m.Get(0, 3) * m.Get(1, 0);
    float s3 = m.Get(0, 1) * m.Get(1, 2) - m.Get(0, 2) * m.Get(1, 1);
    float s4 = m.Get(0, 1) * m.Get(1, 3) - m.Get(0, 3) * m.Get(1, 1);
    float s5 = m.Get(0, 2) * m.Get(1, 3) - m.Get(0, 3) * m.Get(1, 2);

    float c5 = m.Get(2, 2) * m.Get(3, 3) - m.Get(2, 3) * m.Get(3, 2);
    float c4 = m.Get(2, 1) * m.Get(3, 3) - m.Get(2, 3) * m.Get(3, 1);
    float c3 = m.Get(2, 1) * m.Get(3, 2) - m.Get(2, 2) * m.Get(3, 1);
    float c2 = m.Get(2, 0) * m.Get(3, 3) - m.Get(2, 3) * m.Get(3, 0);
    float c1 = m.Get(2, 0) * m.Get(3, 2) - m.Get(2, 2) * m.Get(3, 0);
    float c0 = m.Get(2, 0) * m.Get(3, 1) - m.Get(2, 1) * m.Get(3, 0);

    float det = s0 * c5 -
        s1 * c4 +
        s2 * c3 +
        s3 * c2 -
        s4 * c1 +
        s5 * c0;

    if (fabs(det) < LPTA_EPSILON) {
        throw MatrixInversionError();
    }
    float first = m.Get(1, 1) * c5 - m.Get(1, 2) * c4 + m.Get(1, 3) * c3;
    inverse.AssignAt(0, 0, m.Get(1, 1) * c5 - m.Get(1, 2) * c4 + m.Get(1, 3) * c3);
    inverse.AssignAt(0, 1, -m.Get(0, 1) * c5 + m.Get(0, 2) * c4 - m.Get(0, 3) * c3);
    inverse.AssignAt(0, 2, m.Get(3, 1) * s5 - m.Get(3, 2) * s4 + m.Get(3, 3) * s3);
    inverse.AssignAt(0, 3, -m.Get(2, 1) * s5 + m.Get(2, 2) * s4 - m.Get(2, 3) * s3);

    inverse.AssignAt(1, 0, -m.Get(1, 0) * c5 + m.Get(1, 2) * c2 - m.Get(1, 3) * c1);
    inverse.AssignAt(1, 1, m.Get(0, 0) * c5 - m.Get(0, 2) * c2 + m.Get(0, 3) * c1);
    inverse.AssignAt(1, 2, -m.Get(3, 0) * s5 + m.Get(3, 2) * s2 - m.Get(3, 3) * s1);
    inverse.AssignAt(1, 3, m.Get(2, 0) * s5 - m.Get(2, 2) * s2 + m.Get(2, 3) * s1);

    inverse.AssignAt(2, 0, m.Get(1, 0) * c4 - m.Get(1, 1) * c2 + m.Get(1, 3) * c0);
    inverse.AssignAt(2, 1, -m.Get(0, 0) * c4 + m.Get(0, 1) * c2 - m.Get(0, 3) * c0);
    inverse.AssignAt(2, 2, m.Get(3, 0) * s4 - m.Get(3, 1) * s2 + m.Get(3, 3) * s0);
    inverse.AssignAt(2, 3, -m.Get(2, 0) * s4 + m.Get(2, 1) * s2 - m.Get(2, 3) * s0);

    inverse.AssignAt(3, 0, -m.Get(1, 0) * c3 + m.Get(1, 1) * c1 - m.Get(1, 2) * c0);
    inverse.AssignAt(3, 1, m.Get(0, 0) * c3 - m.Get(0, 1) * c1 + m.Get(0, 2) * c0);
    inverse.AssignAt(3, 2, -m.Get(3, 0) * s3 + m.Get(3, 1) * s1 - m.Get(3, 2) * s0);
    inverse.AssignAt(3, 3, m.Get(2, 0) * s3 - m.Get(2, 1) * s1 + m.Get(2, 2) * s0);

    for (unsigned int row = 0; row < LPTA_MATRIX_ROWS; ++row) {
        for (unsigned int col = 0; col < LPTA_MATRIX_COLUMNS; ++col) {
            inverse.AssignAt(row, col, inverse.Get(row, col) / det);
        }
    }

    return inverse;
}

LptaMatrix::LptaMatrix(void)
{
    for (unsigned int row = 0; row < LPTA_MATRIX_ROWS; ++row) {
        for (unsigned int col = 0; col < LPTA_MATRIX_COLUMNS; ++col) {
            m.at(row).fill(0.0f);
        }
    }
}


void LptaMatrix::SetTransform(float dx, float dy, float dz)
{
    AssignAt(3, 0, dx);
    AssignAt(3, 1, dy);
    AssignAt(3, 2, dz);
}

void LptaMatrix::ResetTransform(void)
{
    SetTransform(0.0f, 0.0f, 0.0f);
}