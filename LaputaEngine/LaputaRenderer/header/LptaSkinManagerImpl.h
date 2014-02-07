#ifndef _LPTASKINMANAGERIMPL_H_
#define _LPTASKINMANAGERIMPL_H_

#include <string>
#include <vector>
#include "Lpta.h"
#include "LptaSkinManager.h"
using std::vector;

class LptaSkinManagerImpl : public LptaSkinManager
{
protected:
    const std::string INVALID_TEXTURE_FILENAME = "";

    vector<Lpta::LPTA_SKIN> skins;
    vector<Lpta::LPTA_MATERIAL> materials;
    vector<Lpta::LPTA_TEXTURE> textures;

    bool ValidSkinId(unsigned int skinId) const;
    bool ValidMaterialId(unsigned int materialId) const;
    bool ValidTextureId(unsigned int textureId) const;
};

#endif