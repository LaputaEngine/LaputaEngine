#ifndef _TEXTUREERROR_H_
#define _TEXTUREERROR_H_

#include <string>
#include <stdexcept>

namespace lpta_d3d
{

class TextureError : public std::runtime_error
{
public:
    TextureError(const std::string &reason);
};

}

#endif