#include <limits>
#include <vector>
#include "LptaOBB.h"
using std::vector;

typedef OBB_AXES::iterator OBB_AXIS;
typedef OBB_AXES::const_iterator OBB_CONST_AXIS;

// ConvertToAABB(void)
typedef const vector<LptaVector> EXTENTS;
inline void SetExtremesFor(LptaVector::DIMENSION dim, EXTENTS &extents, 
    COORDINATE &min, COORDINATE &max);

// Intersects(Triangle)
#define TRIANGLE_EDGES 3
inline void ProjectOBBToVector(const LptaOBB &obb, const LptaVector &vector, 
    float *obbMin, float *obbMax)
{
    const OBB_AXES &axes = obb.GetAxes();
    float projectionCentre = vector * obb.GetCentre();
    float projectionRadius = 0;
    for (OBB_CONST_AXIS axis = axes.begin(); axis != axes.end(); ++axis) {
        projectionRadius += fabs(vector * axis->direction) * axis->extent;
    }
    *obbMin = projectionCentre - projectionRadius;
    *obbMax = projectionCentre + projectionRadius;
}
inline void ProjectTriangleToVector(const LPTA_TRIANGLE &triangle, const LptaVector &vector,
    float *triangleMin, float *triangleMax) 
{
    *triangleMin = std::numeric_limits<float>::max();
    *triangleMax = std::numeric_limits<float>::min();
    for (unsigned int i = 0; i < lpta_geometry::TRIANGLE_SIDES; ++i) {
        float projection = vector * triangle.vertices[i];
        *triangleMin = fmin(*triangleMin, projection);
        *triangleMax = fmax(*triangleMax, projection);
    }
}
#define TEST_TRIANGLE_INTERSECT(triangleMin, triangleMax, obbMin, obbMax) \
do{ \
    if (triangleMin > obbMax || triangleMax < obbMin) { \
        return false; \
    } \
} while (0)

// Intersects(OBB)
#define TEST_OBB_INTERSECT(R0, R1, R) \
do { \
    if (fabs(R) > R0 + R1) { \
        return false; \
    } \
} while (0)

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

bool LptaOBB::Intersects(const LPTA_TRIANGLE &triangle) const
{
    LptaVector triangleEdges[3] = {
        triangle.vertices[1] - triangle.vertices[0],
        triangle.vertices[2] - triangle.vertices[0],
        triangle.vertices[2] - triangle.vertices[1],
    };
    LptaVector triangleNormal = triangleEdges[0].Cross(triangleEdges[1]);
    LptaVector d = triangle.vertices[0] - centre;
    float triangleMin;
    float triangleMax;
    float obbMin;
    float obbMax;

    // normal as separation
    // all vertices project to same location on the normal
    triangleMin = triangleNormal * triangle.vertices[0];
    triangleMax = triangleMin;
    ProjectOBBToVector(*this, triangleNormal, &obbMin, &obbMax);
    TEST_TRIANGLE_INTERSECT(triangleMin, triangleMax, obbMin, obbMax);

    // obb axes
    for (OBB_CONST_AXIS axis = axes.begin(); axis != axes.end(); ++axis) {
        ProjectTriangleToVector(triangle, axis->direction, &triangleMin, &triangleMax);
        // projection of obb to one of its axis is clearly defined by extents
        float projection = axis->direction * centre;
        obbMin = projection - axis->extent;
        obbMax = projection + axis->extent;
        TEST_TRIANGLE_INTERSECT(triangleMin, triangleMax, obbMin, obbMax);
    }

    // cross vectors
    for (OBB_CONST_AXIS axis = axes.begin(); axis != axes.end(); ++axis) {
        for (unsigned int edgeIndex = 0; edgeIndex != TRIANGLE_EDGES; ++edgeIndex) {
            LptaVector projectionVector = triangleEdges[edgeIndex].Cross(axis->direction);
            ProjectOBBToVector(*this, projectionVector, &obbMin, &obbMax);
            ProjectTriangleToVector(triangle, projectionVector, &obbMin, &obbMax);
            TEST_TRIANGLE_INTERSECT(triangleMin, triangleMax, obbMin, obbMax);
        }
    }
    return true;
}

bool LptaOBB::Intersects(const LptaOBB &obb) const
{
    float c[3][3] = { 0 };
    LptaVector d = obb.centre - this->centre;
    for (unsigned int i = 0; i < 3; ++i) {
        for (unsigned int j = 0; j < 3; ++j) {
            c[i][j] = this->axes.at(i).direction * obb.axes.at(j).direction;
        }
    }
    // first obb axes as separation
    for (unsigned int i = 0; i < 3; ++i) {
        TEST_OBB_INTERSECT(
            axes.at(i).extent,
            obb.axes.at(0).extent * fabs(c[i][0]) +
                obb.axes.at(1).extent * fabs(c[i][1]) +
                obb.axes.at(2).extent * fabs(c[i][2]),
            axes.at(i).direction * d
        );
    }
    // second obb axes as separation
    for (unsigned int i = 0; i < 3; ++i) {
        TEST_OBB_INTERSECT( 
            axes.at(0).extent * fabs(c[0][i]) +
                axes.at(1).extent * fabs(c[1][i]) +
                axes.at(2).extent * fabs(c[2][i]),
            obb.axes.at(i).extent,
            obb.axes.at(i).direction * d
        );
    }
    // cross product separation axes
    // A0 x B0
    TEST_OBB_INTERSECT(
        axes.at(1).extent * fabs(c[2][0]) + axes.at(2).extent * fabs(c[1][0]),
        obb.axes.at(1).extent * fabs(c[0][2]) + obb.axes.at(2).extent * fabs(c[0][1]),
        axes.at(2).direction * c[1][0] * d - axes.at(1).direction * c[2][0] * d
    );
    // A0 x B1
    TEST_OBB_INTERSECT(
        axes.at(1).extent * fabs(c[2][1]) + axes.at(2).extent * fabs(c[1][1]),
        obb.axes.at(0).extent * fabs(c[0][2]) + obb.axes.at(2).extent * fabs(c[0][0]),
        axes.at(2).direction * c[1][1] * d - axes.at(1).direction * c[2][1] * d
    );
    // A0 x B2
    TEST_OBB_INTERSECT(
        axes.at(1).extent * fabs(c[2][2]) + axes.at(2).extent * fabs(c[1][2]),
        obb.axes.at(0).extent * fabs(c[0][1]) + obb.axes.at(1).extent * fabs(c[0][0]),
        axes.at(2).direction * c[1][2] * d - axes.at(1).direction * c[2][2] * d
    );
    // A1 x B0
    TEST_OBB_INTERSECT(
        axes.at(0).extent * fabs(c[2][0]) + axes.at(2).extent * fabs(c[0][0]),
        obb.axes.at(1).extent * fabs(c[1][2]) + obb.axes.at(2).extent * fabs(c[1][1]),
        axes.at(0).direction * c[2][0] * d - axes.at(2).direction * c[0][0] * d
    );
    // A1 x B1
    TEST_OBB_INTERSECT(
        axes.at(0).extent * fabs(c[2][1]) + axes.at(2).extent * fabs(c[0][1]),
        obb.axes.at(0).extent * fabs(c[1][2]) + obb.axes.at(2).extent * fabs(c[1][0]),
        axes.at(2).direction * c[1][0] * d - axes.at(0).direction * c[1][2] * d
    );
    // A1 x B2
    TEST_OBB_INTERSECT(
        axes.at(0).extent * fabs(c[2][2]) + axes.at(2).extent * fabs(c[0][2]),
        obb.axes.at(0).extent * fabs(c[1][1]) + obb.axes.at(1).extent * fabs(c[1][0]),
        axes.at(0).direction * c[2][2] * d - axes.at(2).direction * c[0][2] * d
    );
    // A2 x B0
    TEST_OBB_INTERSECT(
        axes.at(0).extent * fabs(c[1][0]) + axes.at(1).extent * fabs(c[0][0]),
        obb.axes.at(1).extent * fabs(c[2][2]) + obb.axes.at(2).extent * fabs(c[2][1]),
        axes.at(1).direction * c[0][0] * d - axes.at(0).direction * c[1][0] * d
    );
    // A2 x B1
    TEST_OBB_INTERSECT(
        axes.at(0).extent * fabs(c[1][1]) + axes.at(1).extent * fabs(c[0][1]),
        obb.axes.at(0).extent * fabs(c[2][2]) + obb.axes.at(2).extent * fabs(c[2][0]),
        axes.at(1).direction * c[0][1] * d - axes.at(0).direction * c[1][1] * d
    );
    // A2 x B2
    TEST_OBB_INTERSECT(
        axes.at(0).extent * fabs(c[1][2]) + axes.at(1).extent * fabs(c[0][2]),
        obb.axes.at(0).extent * fabs(c[2][1]) + obb.axes.at(1).extent * fabs(c[2][0]),
        axes.at(1).direction * c[0][2] * d - axes.at(0).direction * c[1][2] * d
    );
    return true;
}