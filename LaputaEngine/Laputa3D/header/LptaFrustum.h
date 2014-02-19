#ifndef _LPTAFRUSTUM_H_
#define _LPTAFURSTUM_H_

namespace lpta_3d
{

class LptaPlane;

class LptaFrustum
{
public:
    static const unsigned int NUM_FACES = 6;
    typedef unsigned int FACE;
    static const FACE LEFT = 0;
    static const FACE RIGHT = 1;
    static const FACE TOP = 2;
    static const FACE BOTTOM = 3;
    static const FACE NEAR = 4;
    static const FACE FAR = 5;

public:
    LptaFrustum(const LptaPlane &left, const LptaPlane &right, 
        const LptaPlane &top, const LptaPlane &bottom,
        const LptaPlane &near, const LptaPlane &far);
    ~LptaFrustum(void);
    
    const LptaPlane &GetPlaneFor(FACE face) const;
private:
    array<LptaPlane, NUM_FACES> planes;
};

}

#endif