#include "LptaResource.h"

namespace lpta
{
const LptaResource::ID LptaResource::STARTING_ID = 0;

LptaResource::LptaResource(ID id) : id(id)
{
}

LptaResource::~LptaResource(void)
{
}

}