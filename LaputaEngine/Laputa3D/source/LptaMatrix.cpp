#include <math.h>
#include "LptaVector.h"
#include "errors/InvalidRotationAxis.h"
#include "LptaMatrix.h"

#define SKIP_ZEROING true

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


LPTA_MATRIX LptaMatrix::MakeRotateXAxisMatrix(float rad)
{
	float radCos = cos(rad);
	float radSin = sin(rad);
	LPTA_MATRIX matrix = LPTA_MATRIX(new LptaMatrix);

	matrix->AssignAt(0, 0, 1.0f);
	matrix->AssignAt(3, 3, 1.0f);

	matrix->AssignAt(1, 1, radCos);
	matrix->AssignAt(1, 2, radSin);
	matrix->AssignAt(2, 1, -radSin);
	matrix->AssignAt(2, 2, radCos);
	return matrix;
}

LPTA_MATRIX LptaMatrix::MakeRotateYAxisMatrix(float rad)
{
	float radCos = cos(rad);
	float radSin = sin(rad);
	LPTA_MATRIX matrix = LPTA_MATRIX(new LptaMatrix());

	matrix->AssignAt(1, 1, 1.0f);
	matrix->AssignAt(3, 3, 1.0f);

	matrix->AssignAt(0, 0, radCos);
	matrix->AssignAt(0, 2, -radSin);
	matrix->AssignAt(2, 0, radSin);
	matrix->AssignAt(2, 2, radCos);
	return matrix;
}

LPTA_MATRIX LptaMatrix::MakeRotateZAxisMatrix(float rad)
{
	float radCos = cos(rad);
	float radSin = sin(rad);
	LPTA_MATRIX matrix = LPTA_MATRIX(new LptaMatrix());

	matrix->AssignAt(2, 2, 1.0f);
	matrix->AssignAt(3, 3, 1.0f);

	matrix->AssignAt(0, 0, radCos);
	matrix->AssignAt(0, 1, radSin);
	matrix->AssignAt(1, 0, -radSin);
	matrix->AssignAt(1, 1, radCos);
	return matrix;
}

LPTA_MATRIX LptaMatrix::MakeRotationMatrixFor(const LptaVector &v, float rad)
{
	if (!v.IsNormal()) {
		throw InvalidRotationAxis(v);
	}

	float radCos = cos(rad);
	float radSin = sin(rad);
	float cosDiff = (1 - radCos);
	LPTA_MATRIX matrix = LPTA_MATRIX(new LptaMatrix());

	matrix->AssignAt(3, 3, 1.0f);

	matrix->AssignAt(0, 0, radCos + pow(v.GetX(), 2) * cosDiff);
	matrix->AssignAt(0, 1, v.GetX() * v.GetY() * cosDiff + v.GetZ() * radSin);
	matrix->AssignAt(0, 2, v.GetX() * v.GetZ() * cosDiff - v.GetY() * radSin);

	matrix->AssignAt(1, 0, v.GetY() * v.GetX() * cosDiff - v.GetZ() * radSin);
	matrix->AssignAt(1, 1, radCos + pow(v.GetY(), 2) * cosDiff);
	matrix->AssignAt(1, 2, v.GetY() * v.GetZ() * cosDiff + v.GetX() * radSin);

	matrix->AssignAt(2, 0, v.GetZ() * v.GetX() * cosDiff + v.GetY() * radSin);
	matrix->AssignAt(2, 1, v.GetZ() * v.GetY() * cosDiff - v.GetX() * radSin);
	matrix->AssignAt(2, 2, radCos + pow(v.GetZ(), 2) * cosDiff);
	
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