#ifndef _LPTARESOURCEMANAGER_H_
#define _LPTARESOURCEMANAGER_H_

#include <memory>
#include <vector>
#include "LptaResource.h"

namespace lpta
{

template <class T, class D>
class LptaResourceManager
{
public:
    LptaResourceManager(void);
    virtual ~LptaResourceManager(void);

    virtual const T &GetNullResource(void) const;

    virtual bool AddResource(const T &resource);
    virtual const T &GetResource(LptaResource::ID id) const;

protected:
    T nullResource;
    std::vector<T> resources;

    LptaResource::ID GetNextId(void);

private:
    LptaResource::ID nextId = LptaResource::STARTING_ID;
};

// AddResource(RESOURCE_PTR)
template <class T>
inline bool KeyAlreadyExists(const std::vector<T> &resources, LptaResource::ID id);

template <class T, class D>
LptaResourceManager<T, D>::LptaResourceManager(void) :
    nullResource(D::CreateNullResource(GetNextId(), dynamic_cast<D*>(this)))
{
}

template <class T, class D>
LptaResourceManager<T, D>::~LptaResourceManager(void)
{
}

template <class T, class D>
const T &LptaResourceManager<T, D>::GetNullResource(void) const
{
    return nullResource;
}

template <class T, class D>
bool LptaResourceManager<T, D>::AddResource(const T &resource)
{
    if (KeyAlreadyExists<T>(resources, resource.GetId())) {
        return false;
    }
    resources.push_back(resource);
    return true;
}
template <class T>
bool KeyAlreadyExists(const std::vector<T> &resources, LptaResource::ID id)
{
    for (std::vector<T>::const_iterator r = resources.begin(); r != resources.end(); ++r) {
        if (r->GetId() == id) {
            return true;
        }
    }
    return false;
}

template <class T, class D>
const T &LptaResourceManager<T, D>::GetResource(LptaResource::ID id) const
{
    for (std::vector<T>::const_iterator r = resources.begin(); r != resources.end(); ++r) {
        if (r->GetId() == id) {
            return *r;
        }
    }
    return GetNullResource();
}

template <class T, class D>
LptaResource::ID LptaResourceManager<T, D>::GetNextId(void)
{
    return nextId++;
}

}

#endif