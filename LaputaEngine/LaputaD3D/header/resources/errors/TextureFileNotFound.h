#ifndef _TEXTUREFILENOTFOUND_H_
#define _TEXTUREFILENOTFOUND_H_

#include <string>
#include "TextureError.h"

namespace lpta_d3d
{

class TextureFileNotFound : public TextureError
{
public:
    TextureFileNotFound(const std::string &filename);
};

}

#endif