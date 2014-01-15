#ifndef _LPTAMATRIX_H_
#define _LPTAMATRIX_H_

#include <memory>
#include <array>
using std::array;
using std::shared_ptr;

#define LPTA_MATRIX_ROWS 4
#define LPTA_MATRIX_COLUMNS 4

class LptaVector;
class LptaMatrix;
typedef shared_ptr<LptaMatrix> LPTA_MATRIX;

class LptaMatrix
{
public:
	// note that this is optimized for SIMD operations, which means grouping
	// up each dimension's scalar value together. The resulting matrix is
	// simply the original matrix transposed.
	// ie: the array internal structur of the matrix is
	//     [x0, x1, x2, x3]
	//     [y0, y1, y2, y3]
	//     [z0, z1, z2, z3]
	//     [w0, w1, w2, w3]
	// this is abstracted away using the inline method "AssignAt"
    typedef array<array<float, LPTA_MATRIX_COLUMNS>, LPTA_MATRIX_ROWS> MATRIX;
protected:
    inline void AssignAt(unsigned int row, unsigned int column, float value);

public:
    ~LptaMatrix(void);
    
    static LPTA_MATRIX MakeIdentityMatrix(void);

	static LPTA_MATRIX MakeRotateXAxisMatrix(float rad);
    static LPTA_MATRIX MakeRotateYAxisMatrix(float rad);
	static LPTA_MATRIX MakeRotateZAxisMatrix(float rad);
	static LPTA_MATRIX MakeRotationMatrixFor(const LptaVector &v, float rad);

    inline const MATRIX & GetMatrix(void) const;
    inline float Get(unsigned int row, unsigned int column) const;
private:
    LptaMatrix(void);

    MATRIX m;
};

/**
	Note that transpsition needs to be accounted for, see note for internal
	MATRIX definition.
*/
void LptaMatrix::AssignAt(unsigned int row, unsigned int column, float value)
{
    m.at(column).at(row) = value;
}

const LptaMatrix::MATRIX & LptaMatrix::GetMatrix(void) const
{
    return m;
}

/**
	Note that transpsition needs to be accounted for, see note for internal
	MATRIX definition.
*/
float LptaMatrix::Get(unsigned int row, unsigned int column) const
{
    return m.at(column).at(row);
}

#endif