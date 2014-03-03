#ifndef _LPTAVERTICESVISITOR_H_
#define _LPTAVERTICESVISITOR_H_

namespace lpta
{

class LptaVertices;
class LptaUUVertices;
class LptaULVertices;

class LptaVerticesVisitor
{
public:
    virtual void Visit(LptaVertices *collection) = 0;
    virtual void Visit(LptaUUVertices *collection) = 0;
    virtual void Visit(LptaULVertices *collection) = 0;
};

}

#endif