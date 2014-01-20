#include "Lpta3D.h"
#include "LptaRay.h"

#define INTERSECTS true
#define BARYCENTRIC_LOWER_LIMIT 0.0f
#define BARYCENTRIC_UPPER_LIMIT 1.0f

inline bool IsOnSamePlane(float determinant);
inline bool IsWithinTriangle(float barycentricCoordinate);

LptaRay::LptaRay(const COORDINATE &origin, const LptaVector &direction) : 
	origin(origin), direction(direction)
{
}

LptaRay::~LptaRay(void)
{
}

// uses the Moller and Tumbore algorithm
bool LptaRay::Intersects(const LPTA_TRIANGLE &triangle) const
{
	COORDINATE edge1 = triangle.vertices[1] - triangle.vertices[0];
	COORDINATE edge2 = triangle.vertices[2] - triangle.vertices[0];
	LptaVector p = direction.Cross(edge2);
	float determinant = edge1 * p;

	// this tests both sides, the algorithm presented by Moller and Tumbore
	// optionally culls the backface of a triangle.
	if (IsOnSamePlane(determinant)) {
		return !INTERSECTS;
	}

	LptaVector distance = origin - triangle.vertices[0];
	float u = distance * p;
	if (!IsWithinTriangle(u)) {
		return !INTERSECTS;
	}

	LptaVector q = distance.Cross(edge1);
	float v = direction * q;
	if (!IsWithinTriangle(v)) {
		return !INTERSECTS;
	}

	return INTERSECTS;
}

inline bool IsOnSamePlane(float determinant)
{
	return -LPTA_EPSILON < determinant && determinant < LPTA_EPSILON;
}

inline bool IsWithinTriangle(float barycentricCoordinate)
{
	return BARYCENTRIC_LOWER_LIMIT <= barycentricCoordinate &&
		barycentricCoordinate <= BARYCENTRIC_UPPER_LIMIT;
}