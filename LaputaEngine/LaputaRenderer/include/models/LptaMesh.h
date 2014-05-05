#ifndef _LPTAMESH_H_
#define _LPTAMESH_H_

#include <string>

namespace lpta
{

class LptaMeshLoadFailure
{
public:
    LptaMeshLoadFailure(const std::string &reason) : reason(reason) {}
    ~LptaMeshLoadFailure(void) {}

    const std::string reason;
};

class LptaMesh
{
public:
    LptaMesh(void) {}
    virtual ~LptaMesh(void) {}

    virtual unsigned int NumVertices(void) const = 0;
    virtual unsigned int NumFaces(void) const = 0;

public:
    static LptaMesh *LoadFromFile(const std::string &filename);
};

}

#endif