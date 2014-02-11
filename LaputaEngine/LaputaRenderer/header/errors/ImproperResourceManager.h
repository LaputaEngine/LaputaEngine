#ifndef _IMPROPERRESOURCEMANAGER_H_
#define _IMPROPERRESOURCEMANAGER_H_

#include <stdexcept>

namespace lpta
{

class ImproperResourceManager : std::runtime_error
{
public:
    ImproperResourceManager(void) : 
        runtime_error("manager was improperly constructed, "
        "please check ResourceManager specification") {}
};

}

#endif