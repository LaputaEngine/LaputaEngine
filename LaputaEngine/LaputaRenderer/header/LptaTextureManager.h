#ifndef _LPTATEXTUREMANAGER_H_
#define _LPTATEXTUREMANAGER_H_

#include <memory>
#include "LptaTexture.h"
#include "LptaResourceManager.h"

namespace lpta
{

template <class T, class D>
class LptaTextureManager : public LptaResourceManager<T, D>
{
protected:
    static const unsigned long DEFAULT_TEXTURE_COLOR = 0xFF7F00FF;
    static const unsigned int DEFAULT_TEXTURE_WIDTH = 64;
    static const unsigned int DEFAULT_TEXTURE_HEIGHT = DEFAULT_TEXTURE_WIDTH;

public:
    LptaTextureManager(void);
    ~LptaTextureManager(void);
};

template <class T, class D>
LptaTextureManager<T, D>::LptaTextureManager(void)
{
}

template <class T, class D>
LptaTextureManager<T, D>::~LptaTextureManager(void)
{
}

}

#endif