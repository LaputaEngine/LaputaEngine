#ifndef _LPTABOUNDINGBOX_H_
#define _LPTABOUNDINGBOX_H_

#include "LptaPlane.h"

struct LptaBBPlanes
{
	LptaPlane planes[6];
	// index enum, do not alter values
	enum BBFace
	{
		FRONT = 0,
		BACK,
		LEFT,
		RIGHT,
		TOP,
		BOTTOM
	};
	LptaPlane &operator[](BBFace face)
	{
		return planes[face];
	}
};

#endif