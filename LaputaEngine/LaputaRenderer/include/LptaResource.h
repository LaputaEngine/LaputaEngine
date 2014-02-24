#ifndef _LPTARESOURCE_H_
#define _LPTARESOURCE_H_

#include <memory>

namespace lpta
{

class LptaResource
{
public:
    typedef unsigned long long ID;
    static const ID STARTING_ID;
    static const ID INVALID_ID;
public:
    LptaResource(ID id);
    virtual ~LptaResource(void);

    inline ID GetId(void) const;
    inline bool operator<(const LptaResource& other) const;
protected:
    ID id;
};

LptaResource::ID LptaResource::GetId(void) const
{
    return id;
}

bool LptaResource::operator<(const LptaResource &other) const
{
    return id < other.id;
}

}
#endif