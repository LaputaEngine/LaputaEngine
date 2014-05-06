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
    virtual void Visit(const LptaVertices *collection) const = 0;
    virtual void Visit(const LptaUUVertices *collection) const = 0;
    virtual void Visit(const LptaULVertices *collection) const = 0;
};

}

#endif