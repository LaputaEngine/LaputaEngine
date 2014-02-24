#ifndef _LPTARESOURCEMANAGER_H_
#define _LPTARESOURCEMANAGER_H_

#include <map>
#include "LptaResource.h"
#include "errors/ImproperResourceManager.h"

namespace lpta
{

template <class T>
class LptaResourceManager
{
protected:
    typedef std::map<LptaResource::ID, T> RESOURCES;

public:
    /*!!! must call SetNullResource !!!!*/
    LptaResourceManager(void);
    virtual ~LptaResourceManager(void);

    virtual const T &RetrieveNullResource(void) const;
    virtual const T &RetrieveResource(LptaResource::ID id) const;

protected:
    virtual void SetNullResource(T resource);

    virtual bool AddResource(const T &resource);
    virtual bool UpdateResource(const T& updated);
    LptaResource::ID GetNextId(void);

    LptaResource::ID nullResourceId = LptaResource::INVALID_ID;
    RESOURCES resources;
    
private:
    LptaResource::ID nextId = LptaResource::STARTING_ID;

    typedef std::pair<LptaResource::ID, T> KEY_VALUE_PAIR;
    typedef std::pair<typename RESOURCES::iterator, bool> INSERT_RESULT;
};

template <class T>
LptaResourceManager<T>::LptaResourceManager(void)
{
}

template <class T>
LptaResourceManager<T>::~LptaResourceManager(void)
{
}

template <class T>
const T &LptaResourceManager<T>::RetrieveNullResource(void) const
{
    try {
        return resources.at(nullResourceId);
    }
    catch (std::out_of_range) {
        throw ImproperResourceManager();
    }
}

template <class T>
void LptaResourceManager<T>::SetNullResource(T resource)
{
    AddResource(resource);
    nullResourceId = resource.GetId();
}

template <class T>
bool LptaResourceManager<T>::AddResource(const T &resource)
{

    INSERT_RESULT result = resources.insert(KEY_VALUE_PAIR(resource.GetId(), resource));
    return result.second;
}

template <class T>
const T &LptaResourceManager<T>::RetrieveResource(LptaResource::ID id) const
{
    try {
        return resources.at(id);
    }
    catch (std::out_of_range) {
        return RetrieveNullResource();
    }
}

template <class T>
bool LptaResourceManager<T>::UpdateResource(const T& updated)
{
    if (updated.GetId() != nullResourceId && resources.count(updated.GetId()) > 0) {
        resources.at(updated.GetId()) = updated;
        return true;
    }
    return false;
}

template <class T>
LptaResource::ID LptaResourceManager<T>::GetNextId(void)
{
    return nextId++;
}

}

#endif