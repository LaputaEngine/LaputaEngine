#ifndef _TEXTURED3DFAILURE_H_
#define _TEXTURED3DFAILURE_H_

#include <string>
#include "TextureError.h"

namespace lpta_d3d
{

class TextureD3DFailure : public TextureError
{
public:
    TextureD3DFailure(const std::string &reason);
};

}

#endif