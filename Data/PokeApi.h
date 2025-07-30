//  Definition of the class that we will use to obtain the data

#ifndef POKEAPI_H
#define POKEAPI_H

#include <memory>
#include <vector>
#include <nlohmann/json.hpp>
#include <curl/curl.h>

#include "Domain/IPokemonRepository.h"
#include "Domain/PokemonDTO.h"

class PokeApi final : public IPokemonRepository  {
    public:
        PokemonDTO getPokemonByName(const std::string &pokemonName) override;
        void getMovePoolFromPokemon(const std::string &pokemonName, std::vector<std::string> &allMoves, std::vector<std::string> &allMethods, std::string &lastVersion) override;
        std::vector<std::string> getAllPokemon() override;
        std::vector<std::string> getAllAbilities() override;
        std::vector<std::string> getAllMoves() override;

    private:
        static std::string makeRequest(const std::string& endpoint);
        static std::string getPokemonName();
        static void setCurlOptions(CURL* curl, const std::string& url, std::string& responseData);
        static void sendRequest(CURL* curl);
        static size_t callBack(void* contents, size_t size, size_t numberEntities, std::string* output);
};

#endif