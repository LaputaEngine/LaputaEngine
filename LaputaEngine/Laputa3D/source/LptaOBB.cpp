#include <vector>
#include "LptaOBB.h"
using std::vector;

typedef OBB_AXES::iterator OBB_AXIS;
typedef OBB_AXES::const_iterator OBB_CONST_AXIS;

// ConvertToAABB(void)
typedef const vector<LptaVector> EXTENTS;
inline void SetExtremesFor(LptaVector::DIMENSION dim, EXTENTS &extents, 
    COORDINATE &min, COORDINATE &max);

LptaOBB::LptaOBB(const COORDINATE &centre, const OBB_AXES &axes) :
    centre(centre), axes(axes)
{
}

LptaOBB::~LptaOBB(void)
{
}

LptaAABB LptaOBB::ConvertToAABB(void) const
{
    COORDINATE min;
    COORDINATE max;
    
    vector<LptaVector> extentVectors;
    for (OBB_CONST_AXIS axis = axes.begin(); axis != axes.end(); ++axis) {
        extentVectors.push_back(axis->ExtentVector());
    }

    SetExtremesFor(LptaVector::X, extentVectors, min, max);
    SetExtremesFor(LptaVector::Y, extentVectors, min, max);
    SetExtremesFor(LptaVector::Z, extentVectors, min, max);

    min += centre;
    max += centre;
    return LptaAABB(min, max);
}
void SetExtremesFor(LptaVector::DIMENSION dim, EXTENTS &extents,
    COORDINATE &min, COORDINATE &max)
{
    if (extents.size() == 0) {
        return;
    }
    float dimensionMax = extents.at(0).GetDimension(dim);
    for (EXTENTS::const_iterator it = extents.begin(); it != extents.end(); ++it) {
        if (it->GetDimension(dim) > dimensionMax) {
            dimensionMax = it->GetDimension(dim);
        }
    }
    min.SetDimension(dim, -dimensionMax);
    max.SetDimension(dim, dimensionMax);
}

LptaOBB LptaOBB::Transform(LptaMatrix transform) const
{
    COORDINATE centre = this->centre;
    COORDINATE translation = transform.GetTranslation();
    transform.ClearTranslation();

    OBB_AXES axes = this->axes;
    for (OBB_AXIS axis = axes.begin(); axis != axes.end(); ++axis) {
        axis->direction = LptaNormalVector::MakeFrom(axis->direction * transform);
    }
    centre = centre * transform;
    centre += translation;

    return LptaOBB(centre, axes);
}