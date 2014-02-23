#ifndef _LPTAD3DMATRIX_H_
#define _LPTAD3DMATRIX_H_

#include <d3dx9.h>
#include "LptaMatrix.h"

namespace lpta_d3d
{

class LptaD3DMatrix : public lpta_3d::LptaMatrix
{
public:
    LptaD3DMatrix(const lpta_3d::LptaMatrix &m);
    ~LptaD3DMatrix(void);
    static LptaD3DMatrix MakeFrom(const D3DXMATRIX &m);

    D3DXMATRIX ConvertToDxMatrix(void) const;
private:
    LptaD3DMatrix(void);
};

}

#endif