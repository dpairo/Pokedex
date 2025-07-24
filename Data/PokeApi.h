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
        std::string getPokemonName();
        size_t callBack(void* contents, size_t size, size_t numberEntities, std::string* output);
        void setCurlOptions(CURL* curl, const std::string& url, std::string& responseData);
        void sendRequest(CURL* curl);
    public:
        Pokemon getPokemonByName() override;
        std::vector<std::unique_ptr<Moves>> getMovepoolFromPokemon() override;
        std::vector<std::unique_ptr<Pokemon>> getAllPokemon() override;
        std::vector<std::unique_ptr<Abilities>> getAllAbilities() override;
        std::vector<std::unique_ptr<Moves>> getAllMoves() override;
};

#endif