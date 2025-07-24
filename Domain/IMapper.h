#ifndef _I_MAPPER_H_
#define _I_MAPPER_H_

#include <iostream>

#include "PokemonDTO.h"

class IJsonMapper {
public:
    virtual PokemonDTO transformJson(const std::string& jsonString) = 0;
    virtual ~IJsonMapper() = default;
};

#endif