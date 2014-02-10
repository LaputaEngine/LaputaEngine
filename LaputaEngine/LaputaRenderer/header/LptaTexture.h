#ifndef _LPTATEXTURE_H_
#define _LPTATEXTURE_H_

#include <string>
#include <memory>
#include <vector>
#include "LptaResource.h"
#include "LptaColor.h"

namespace lpta
{
using std::string;
using std::unique_ptr;
using std::vector;

template <class T>
class LptaTexture : public LptaResource
{
public:
    typedef ID TEXTURE_ID;
    typedef vector<LptaColor> COLOR_KEYS;

public:
    LptaTexture(ID id, const string &filename, const T &data, 
        float alpha, const COLOR_KEYS &colorKeys);
    ~LptaTexture(void);

    inline const T &GetData(void) const;

private:
    string filename;
    T data;
    float alpha;
    COLOR_KEYS colorKeys;
};

template <class T>
LptaTexture<T>::LptaTexture(ID id, const string &filename, const T &data, 
        float alpha, const COLOR_KEYS &colorKeys) :
        LptaResource(id), data(data), filename(filename), alpha(alpha), colorKeys(colorKeys)
{
}

template <class T>
LptaTexture<T>::~LptaTexture(void)
{
}

template <class T>
const T &LptaTexture<T>::GetData(void) const
{
    return data;
}

}

#endif