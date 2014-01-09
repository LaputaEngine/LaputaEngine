#ifndef _LPTAMATRIX_H_
#define _LPTAMATRIX_H_

#include <memory>
#include <array>
using std::array;
using std::shared_ptr;

#define LPTA_MATRIX_ROWS 4
#define LPTA_MATRIX_COLUMNS 4

class LptaMatrix;
typedef shared_ptr<LptaMatrix> LPTA_MATRIX;

class LptaMatrix
{
public:
    typedef array<array<float, LPTA_MATRIX_ROWS>, LPTA_MATRIX_COLUMNS> MATRIX;
protected:
    inline void AssignAt(unsigned int row, unsigned int column, float value);

public:
    ~LptaMatrix(void);
    
    static LPTA_MATRIX MakeIdentityMatrix(void);
    static LPTA_MATRIX MakeRotateYAxisMatrix(float rad);

    inline const MATRIX & GetMatrix(void) const;
    inline float Get(unsigned int row, unsigned int column) const;
private:
    LptaMatrix(void);

    MATRIX m;
};

void LptaMatrix::AssignAt(unsigned int row, unsigned int column, float value)
{
    m.at(row).at(column) = value;
}

const LptaMatrix::MATRIX & LptaMatrix::GetMatrix(void) const
{
    return m;
}

float LptaMatrix::Get(unsigned int row, unsigned int column) const
{
    return m.at(row).at(column);
}

#endif