#ifndef _LPTAULVERTICES_H_
#define _LPTAULVERTICES_H_

#include <vector>
#include "LptaVector.h"
#include "LptaColor.h"
#include "LptaVertices.h"

namespace lpta
{

typedef struct UL_VERTEX_TYPE
{
    lpta_3d::POINT coordinate;
    LptaColor color;

    float tu;
    float tv;
} UL_VERTEX;

class LptaULVertices : public LptaVertices
{
public:
    LptaULVertices(void);
    virtual ~LptaULVertices(void);

    virtual unsigned int GetNumVertices(void) const;
    virtual void Accept(LptaVerticesVisitor *visitor);

    void AddVertex(const UL_VERTEX &vertex);
    const std::vector<UL_VERTEX> &GetVertices(void) const;

private:
    std::vector<UL_VERTEX> vertices;
};

}

#endif