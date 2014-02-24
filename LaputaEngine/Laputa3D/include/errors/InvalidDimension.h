#ifndef _INVALIDDIMENSION_H_
#define _INVALIDDIMENSION_H_

#include <stdexcept>

namespace lpta_3d
{

class InvalidDimension : public std::runtime_error
{
public:
    InvalidDimension(void);
};

}

#endif