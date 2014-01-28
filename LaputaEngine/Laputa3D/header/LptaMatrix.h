#ifndef _LPTAMATRIX_H_
#define _LPTAMATRIX_H_

#include <memory>
#include <array>
using std::array;
using std::shared_ptr;

#define LPTA_MATRIX_ROWS 4
#define LPTA_MATRIX_COLUMNS 4

class LptaVector;

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
    LptaMatrix(void);
    inline void AssignAt(unsigned int row, unsigned int column, float value);
public:
    ~LptaMatrix(void);
    
    static LptaMatrix MakeIdentityMatrix(void);

    static LptaMatrix MakeRotateXAxisMatrix(float rad);
    static LptaMatrix MakeRotateYAxisMatrix(float rad);
    static LptaMatrix MakeRotateZAxisMatrix(float rad);
    static LptaMatrix MakeRotationMatrixFor(const LptaVector &v, float rad);
    static LptaMatrix MakeInverseFor(const LptaMatrix &m);

    inline const MATRIX & GetMatrix(void) const;
    inline float Get(unsigned int row, unsigned int column) const;
    inline float GetDx(void) const;
    inline float GetDy(void) const;
    inline float GetDz(void) const;

    LptaVector GetTranslation(void) const;
    void SetTranslation(float dx, float dy, float dz);
    void ClearTranslation(void);
private:
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
float LptaMatrix::GetDx(void) const
{
    return Get(3, 0);
}
float LptaMatrix::GetDy(void) const
{
    return Get(3, 1);
}
float LptaMatrix::GetDz(void) const
{
    return Get(3, 2);
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