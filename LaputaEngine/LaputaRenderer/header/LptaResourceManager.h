#ifndef _LPTARESOURCEMANAGER_H_
#define _LPTARESOURCEMANAGER_H_

#include <memory>
#include <map>
#include "LptaResource.h"

namespace lpta
{

template <class T, class D>
class LptaResourceManager
{
public:
    LptaResourceManager(void);
    virtual ~LptaResourceManager(void);

    virtual std::shared_ptr<T> GetNullResource(void) const;

    virtual bool AddResource(std::shared_ptr<T> resource);
    virtual std::shared_ptr<T> GetResource(LptaResource::ID id) const;

protected:
    std::shared_ptr<T> nullResource;
    std::map<LptaResource::ID, std::shared_ptr<T>> resources;

    LptaResource::ID GetNextId(void);

private:
    LptaResource::ID nextId = LptaResource::STARTING_ID;
};

// AddResource(RESOURCE_PTR)
template <class T>
inline bool KeyAlreadyExists(const std::map<LptaResource::ID, std::shared_ptr<T>> &resources, 
    LptaResource::ID id);

template <class T, class D>
LptaResourceManager<T, D>::LptaResourceManager(void)
{
    nullResource = D::CreateNullResource(GetNextId(), dynamic_cast<D*>(this));
}

template <class T, class D>
LptaResourceManager<T, D>::~LptaResourceManager(void)
{
}

template <class T, class D>
std::shared_ptr<T> LptaResourceManager<T, D>::GetNullResource(void) const
{
    return nullResource;
}

template <class T, class D>
bool LptaResourceManager<T, D>::AddResource(std::shared_ptr<T> resource)
{
    if (KeyAlreadyExists<T>(resources, resource->GetId())) {
        return false;
    }
    resources.insert(std::pair<LptaResource::ID, std::shared_ptr<T>>(resource->GetId(), resource));
    return true;
}
template <class T>
bool KeyAlreadyExists(const std::map<LptaResource::ID, std::shared_ptr<T>> &resources, 
    LptaResource::ID id)
{
    return resources.find(id) != resources.end();
}

template <class T, class D>
std::shared_ptr<T> LptaResourceManager<T, D>::GetResource(LptaResource::ID id) const
{
    try {
        return resources.at(id);
    }
    catch (std::out_of_range) {
        return GetNullResource();
    }
}

template <class T, class D>
LptaResource::ID LptaResourceManager<T, D>::GetNextId(void)
{
    return nextId++;
}

}

#endif