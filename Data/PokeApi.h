//  Definition of the class that we will use to obtain the data

#ifndef POKEAPI_H
#define POKEAPI_H

#include <memory>
#include <vector>
#include <nlohmann/json.hpp>
#include <curl/curl.h>

#include "Domain/IPokemonRepository.h"
#include "Domain/Pokemon.h"
#include "Domain/PokemonDTO.h"

class PokeApi : public IPokemonRepository {
    private:
        PokemonDTO parseJsonToDTO(const nlohmann::json& json);
        std::string makeRequest(const std::string& endpoint);
        std::string getPokemonName();
        void setCurlOptions(CURL* curl, const std::string& url, std::string& responseData);
        void sendRequest(CURL* curl);

    public:
        PokemonDTO getPokemonByName(const std::string &pokemonName) override;
        //std::vector<std::unique_ptr<Moves>> getMovepoolFromPokemon() override;
        //std::vector<std::unique_ptr<Pokemon>> getAllPokemon() override;
        //std::vector<std::unique_ptr<Abilities>> getAllAbilities() override;
        //std::vector<std::unique_ptr<Moves>> getAllMoves() override;

    static size_t callBack(void* contents, size_t size, size_t nmemb, std::string* output);
};

#endif