#include <climits>
#include "LptaResource.h"

namespace lpta
{
const LptaResource::ID LptaResource::STARTING_ID = 0;
const LptaResource::ID LptaResource::INVALID_ID = UINT_MAX;

LptaResource::LptaResource(ID id) : id(id)
{
}

LptaResource::~LptaResource(void)
{
}

}