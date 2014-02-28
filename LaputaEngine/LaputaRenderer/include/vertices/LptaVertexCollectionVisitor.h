#ifndef _LPTAVERTEXCOLLECTIONVISITOR_H_
#define _LPTAVERTEXCOLLECTIONVISITOR_H_

namespace lpta
{

class LptaVertexCollection;
class LptaUUVertexCollection;
class LptaULVertexCollection;

class LptaVertexCollectionVisitor
{
public:
    virtual ~LptaVertexCollectionVisitor(void);

    virtual void Visit(LptaVertexCollection *collection) = 0;
    virtual void Visit(LptaUUVertexCollection *collection) = 0;
};

}

#endif