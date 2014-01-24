#include <vector>
#include "LptaOBB.h"
using std::vector;

// ConvertToAABB(void)
typedef const vector<LptaVector> EXTENTS;
inline void SetExtremesFor(LptaVector::DIMENSION dim, EXTENTS &extents, 
    COORDINATE &min, COORDINATE &max);

LptaOBB::LptaOBB(const COORDINATE &coordinate, const OBB_AXES &axes) :
    coordinate(coordinate), axes(axes)
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
    for (OBB_AXES::const_iterator it = axes.begin(); it != axes.end(); ++it) {
        extentVectors.push_back(it->ExtentVector());
    }

    SetExtremesFor(LptaVector::X, extentVectors, min, max);
    SetExtremesFor(LptaVector::Y, extentVectors, min, max);
    SetExtremesFor(LptaVector::Z, extentVectors, min, max);

    min += coordinate;
    max += coordinate;
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