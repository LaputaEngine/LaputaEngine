#ifndef _LPTASKINMANAGER_H_
#define _LPTASKINMANAGER_H_

#include <Windows.h>
#include <string>
#include "Lpta.h"
using std::string;

class LptaSkinManager
{
public:
    LptaSkinManager(void) {};
    virtual ~LptaSkinManager(void) {};

    virtual HRESULT AddSkin(const Lpta::LPTA_MATERIAL &material, unsigned int *skinId) = 0;
    virtual HRESULT AddTexture(unsigned int skinId,
        const Lpta::LPTA_TEXTURE &texture, bool enableTransparency) = 0;
    virtual HRESULT AddTextureHeightmapAsBump(unsigned int skinId, const string &fileName) = 0;
    
    virtual bool MaterialsEqual(const Lpta::LPTA_MATERIAL &mat0, 
        const Lpta::LPTA_MATERIAL &mat1) const = 0;

    virtual Lpta::LPTA_SKIN GetSkin(unsigned int skinId) const = 0;
    virtual Lpta::LPTA_MATERIAL GetMaterial(unsigned int materialId) const = 0;
    virtual Lpta::LPTA_TEXTURE GetTexture(unsigned int textureId) const = 0;
};

#endif