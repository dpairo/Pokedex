//  Implementation of the AllPokemonMapperClass.

#include "AllPokemonMapper.h"

std::vector<std::string> AllPokemonMapper::parseAll(const nlohmann::json& allJson) const {
        std::vector<std::string> allPokemons;

        for (const auto& pokemon : allJson[resultsSeeker]) {
                allPokemons.push_back(pokemon[nameSeeker]);
        }

        return allPokemons;
}

std::vector<std::string> AllPokemonMapper::transformAll(const std::string &allPokemonRawJson) const {
        const nlohmann::json allPokemonJson = nlohmann::json::parse(allPokemonRawJson);

        std::vector<std::string> allPokemons = parseAll(allPokemonJson);

        return allPokemons;
}
