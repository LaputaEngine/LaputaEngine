#ifndef _LPTAUUVERTICES_H_
#define _LPTAUUVERTICES_H_

#include <vector>
#include "LptaVector.h"
#include "LptaVertices.h"

namespace lpta
{

typedef struct UU_VERTEX_TYPE
{
    lpta_3d::POINT coordinate;
    lpta_3d::LptaVector normal;
    
    float tu;
    float tv;
} UU_VERTEX;

class LptaUUVertices : public LptaVertices
{
public:
    LptaUUVertices(void);
    virtual ~LptaUUVertices(void);

    virtual unsigned int GetNumVertices(void) const;
    virtual void Accept(LptaVerticesVisitor *visitor);

    void AddVertex(const UU_VERTEX &vertex);
    const std::vector<UU_VERTEX> &GetVertices(void) const;
    
private:
    std::vector<UU_VERTEX> vertices;
};

}

#endif