//  Interface that will be used to define what the pokeApi will be able to do with an abstraction layer

#ifndef I_POKEMON_REPOSITORY_H
#define I_POKEMON_REPOSITORY_H

#include <string>
#include <vector>
#include <memory>

#include "Pokemon.h"

class IPokemonRepository {
public:
    virtual Pokemon getPokemonByName() = 0;
    virtual std::vector<std::unique_ptr<Pokemon>> getAllPokemon() = 0;
    virtual std::vector<std::unique_ptr<Moves>> getMovepoolFromPokemon() = 0;
    virtual std::vector<std::unique_ptr<Moves>> getAllPokemonMoves() = 0;
    virtual ~IPokemonRepository() = default;
};

#endif