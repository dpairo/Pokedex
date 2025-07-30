//  Interface that will be used to define what the pokeApi will be able to do with an abstraction layer

#ifndef I_POKEMON_REPOSITORY_H
#define I_POKEMON_REPOSITORY_H

#include <vector>
#include <memory>

#include "Pokemon.h"

class IPokemonRepository {
public:
    virtual PokemonDTO getPokemonByName(const std::string &pokemonName) = 0;
    virtual std::vector<std::string> getAllPokemon() = 0;
    virtual std::vector<std::string> getAllAbilities() = 0;
    virtual std::vector<std::string> getAllMoves() = 0;
    virtual void getMovePoolFromPokemon(const std::string &pokemonName, std::vector<std::string> &allMoves, std::vector<std::string> &allMethods, std::string &lastVersion) = 0;
    virtual ~IPokemonRepository() = default;
};

#endif