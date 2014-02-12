#ifndef _SHAPES_H_
#define _SHAPES_H_
#include "LptaVector.h"

namespace lpta_3d
{

namespace geometry
{
    const int TRIANGLE_SIDES = 3;
}

typedef struct 
{
    POINT vertices[3];
} LPTA_TRIANGLE;

}

#endif