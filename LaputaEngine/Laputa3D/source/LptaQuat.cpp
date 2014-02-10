// todo: a lot of the underlying operations seem like they would be better handled by the
// vector object.

#include "LptaMatrix.h"
#include "LptaQuat.h"

LptaQuat::LptaQuat(void) : LptaQuat(1.0f, 0.0f, 0.0f, 0.0f)
{
}

LptaQuat::LptaQuat(float w, float x, float y, float z) : w(w), x(x), y(y), z(z)
{
}

LptaQuat LptaQuat::MakeFromEuler(float pitch, float yaw, float roll)
{
    pitch *= 0.5f;
    yaw *= 0.5f;
    roll *= 0.5f;

    float cX = cosf(pitch);
    float cY = cosf(yaw);
    float cZ = cosf(roll);

    float sX = sinf(pitch);
    float sY = sinf(yaw);
    float sZ = sinf(roll);

    float cYcZ = cY * cZ;
    float sYsZ = sY * sZ;
    float cYsZ = cY * sZ;
    float sYcZ = sY * cZ;

    return LptaQuat(
        cX * cYcZ + sX * sYsZ,
        sX * cYcZ - cX * sYsZ,
        cX * sYcZ + sX * cYsZ,
        cX * cYsZ - sX * sYcZ
    );
}

LptaQuat LptaQuat::operator *(const LptaQuat &other) const
{
    LptaQuat result = *this;
    result *= other;
    return result;
}

void LptaQuat::operator *=(const LptaQuat &other)
{
    float _w = (w * other.w) - (x * other.x) - (y * other.y) - (z * other.z);
    float _x = (w * other.x) + (x * other.w) + (y * other.z) - (z * other.y);
    float _y = (w * other.y) + (y * other.w) + (z * other.x) - (x * other.z);
    float _z = (w * other.z) + (z * other.w) + (x * other.y) - (y * other.x);

    this->w = _w;
    this->x = _x;
    this->y = _y;
    this->z = _z;
}