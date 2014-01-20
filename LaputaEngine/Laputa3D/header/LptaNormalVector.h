#ifndef _LPTANORMALVECTOR_H_
#define _LPTANORMALVECTOR_H_

#include "LptaVector.h"

class LptaNormalVector : public LptaVector
{
public:
	LptaNormalVector(void);
	LptaNormalVector(float x, float y, float z);
};

#endif