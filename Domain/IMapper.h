#ifndef _I_MAPPER_H_
#define _I_MAPPER_H_

#include <iostream>

#include "PokemonDTO.h"

class IJsonMapper {
public:
    virtual PokemonDTO transformDataPokemonJson(const std::string &pokemonDetailsRawJson, const std::string &pokemonSpeciesRawJson, std::string &evolutionChainUrl) = 0;
    virtual ~IJsonMapper() = default;
};

#endif