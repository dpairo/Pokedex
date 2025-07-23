//  Definition of the class that we will use to obtain the data

#ifndef POKEAPI_H
#define POKEAPI_H

#include <memory>
#include <vector>
#include <nlohmann/json.hpp>

#include "Domain/IPokemonRepository.h"
#include "Domain/Pokemon.h"
#include "Domain/PokemonDTO.h"

class PokeApi : public IPokemonRepository {
    private:
        PokemonDTO parseJsonToDTO(const nlohmann::json& json);
        std::string makeRequest(const std::string& endpoint);

    public:
        Pokemon getPokemonByName() override;
        std::vector<std::unique_ptr<Moves>> getMovepoolFromPokemon() override;
        std::vector<std::unique_ptr<Pokemon>> getAllPokemon() override;
        std::vector<std::unique_ptr<Moves>> getAllPokemonMoves() override;
};

#endif