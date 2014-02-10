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
using std::shared_ptr;
using std::vector;

class LptaTexture : public LptaResource
{
public:
    typedef ID TEXTURE_ID;
    typedef shared_ptr<void> DATA;
    typedef vector<LptaColor> COLOR_KEYS;

public:
    LptaTexture(ID id, const string &filename, const DATA data, 
        float alpha, const COLOR_KEYS &colorKeys);
    ~LptaTexture(void);

    inline DATA GetData(void) const;

private:
    string filename;
    DATA data;
    float alpha;
    COLOR_KEYS colorKeys;
};

LptaTexture::DATA LptaTexture::GetData(void) const
{
    return data;
}

}

#endif