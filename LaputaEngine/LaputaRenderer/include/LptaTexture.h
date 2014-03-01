#ifndef _LPTATEXTURE_H_
#define _LPTATEXTURE_H_

#include <string>
#include <vector>
#include "LptaResource.h"
#include "LptaColor.h"

namespace lpta
{
using std::string;
using std::vector;

class LptaTexture : public LptaResource
{
public:
    typedef ID TEXTURE_ID;
    typedef vector<LptaColor> COLOR_KEYS;
    typedef void* DATA;

public:
    LptaTexture(ID id, const string &filename, DATA data, 
        float alpha, const COLOR_KEYS &colorKeys);
    ~LptaTexture(void);

    inline const DATA &GetData(void) const;

    const string &GetFilename(void) const;
    float GetAlpha(void) const;
    const COLOR_KEYS &GetColorKeys(void) const;

private:
    string filename;
    DATA data;
    float alpha;
    COLOR_KEYS colorKeys;
};

const LptaTexture::DATA &LptaTexture::GetData(void) const
{
    return data;
}

}

#endif