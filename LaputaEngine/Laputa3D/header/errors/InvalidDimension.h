#ifndef _INVALIDDIMENSION_H_
#define _INVALIDDIMENSION_H_

#include <stdexcept>

class InvalidDimension : public std::runtime_error
{
public:
    InvalidDimension(void);
};

#endif