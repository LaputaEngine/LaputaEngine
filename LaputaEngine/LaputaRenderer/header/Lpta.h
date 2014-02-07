#ifndef _LPTA_H_
#define _LPTA_H_

#include <string>
#include <memory>
#include <array>
#include <vector>
using std::string;
using std::shared_ptr;
using std::array;
using std::vector;

namespace Lpta {

const unsigned int MAX_SKIN_TEXTURES = 8;

typedef struct LptaColorType
{
    union
    {
        struct
        {
            float red;
            float green;
            float blue;
            float alpha;
        };
        float colors[4];
    };
} LPTA_COLOR;

typedef struct LptaMaterialType
{
    LPTA_COLOR diffuse;
    LPTA_COLOR ambient;
    LPTA_COLOR specular;
    LPTA_COLOR emissive;
    float specularPower;
} LPTA_MATERIAL;

typedef shared_ptr<void> DATA;
typedef vector<LPTA_COLOR> COLOR_KEYS;
typedef struct LptaTextureType
{
    float alpha;
    string fileName;
    DATA data;
    COLOR_KEYS colorAlphaKeys;

} LPTA_TEXTURE;

typedef array<unsigned int, MAX_SKIN_TEXTURES> SKIN_TEXTURE_IDS;
typedef struct LptaSkinType
{
    bool enableTransparency;
    unsigned int materialId;
    SKIN_TEXTURE_IDS textureIds;
} LPTA_SKIN;

}

#endif