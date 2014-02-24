#include <string>
#include "errors/NonNormalVector.h"
using std::to_string;

namespace lpta_3d
{

NonNormalVector::NonNormalVector(const LptaVector &vector) :
    domain_error(
        "normal vector expected but [" +
        to_string(vector.GetX()) + ", " +
        to_string(vector.GetY()) + ", " +
        to_string(vector.GetZ()) +
        "]' is not normal."
    )
{

}

}