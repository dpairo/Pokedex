//  Definition of the interface for all the data mappers

#ifndef _SINGLE_POKEMON_MAPPER_H_
#define _SINGLE_POKEMON_MAPPER_H_

#include "Domain/PokemonDTO.h"

class SinglePokemonMapper {
    public:
        PokemonDTO transformDataPokemonJson(const std::string &pokemonDetailsRawJson, const std::string &pokemonSpeciesRawJson, std::string &evolutionChainUrl);
        void transformMovePool(const std::string& pokemonAndMovePoolRawString, const std::string& versionsRawJson, std::vector<std::string>& allMoves, std::vector<std::string>& allMethods, std::string &lastVersion) const;
        std::vector<std::string> transformEvolutionChainJson(const std::string &pokemonEvolutionChainRawJson) const;

    private:
        const std::string nameSeeker = "name";
        const std::string abilitiesSeeker = "abilities";
        const std::string abilitySeeker = "ability";
        const std::string isAbilityHiddenSeeker = "is_hidden";
        const std::string slotSeeker = "slot";
        const std::string healthSeeker = "hp";
        const std::string statsSeeker = "stats";
        const std::string singleStatSeeker = "stat";
        const std::string baseStatValueSeeker = "base_stat";
        const std::string attackSeeker = "attack";
        const std::string defenseSeeker = "defense";
        const std::string specialAttackSeeker = "special-attack";
        const std::string specialDefenseSeeker = "special-defense";
        const std::string speedSeeker = "speed";
        const std::string typesSeeker = "types";
        const std::string singleTypeSeeker = "type";
        const std::string eggGroupsSeeker = "egg_groups";
        const std::string idSeeker = "id";
        const std::string baseExperienceSeeker = "base_experience";
        const std::string hatchCounterSeeker = "hatch_counter";
        const std::string evolutionChainSeeker = "evolution_chain";
        const std::string urlSeeker = "url";
        const std::string chainSeeker = "chain";
        const std::string speciesSeeker = "species";
        const std::string evolvesToSeeker = "evolves_to";
        const std::string movesSeeker = "moves";
        const std::string singularMoveSeeker = "move";
        const std::string versionDetailsSeeker = "version_group_details";
        const std::string versionGroupSeeker = "version_group";
        const std::string redBluesSeeker = "red-blue";
        const std::string resultsSeeker = "results";
        const std::string levelUpSeeker = "level-up";
        const std::string tutorSeeker = "tutor";
        const std::string machineSeeker = "machine";
        const std::string learnMethodSeeker = "move_learn_method";
        std::string getPokemonLastVersion(const nlohmann::json &pokemonAndMovePoolJson, const std::unordered_map<std::string, int> &versionsMap) const;
        std::unordered_map<std::string, int> getVersionsWithId(const nlohmann::json &versionJson) const ;
        void parseMovePool(const nlohmann::json& movePoolJson, std::vector<std::string>& allMoves, std::vector<std::string> &allMethods, const std::string& lastVersion) const;
        void extractEvolutionChain(const nlohmann::json &jsonNode, std::vector<std::string> &evolutionChain) const;
        void parseEvolutionChainUrl(const nlohmann::json &pokemonDataSpecies, std::string &evolutionChainUrl) const;
        int parsePokemonHatchCounter(const nlohmann::json &pokemonDataSpecies) const;
        int parsePokemonBaseExp(const nlohmann::json &pokemonDataDetails) const;
        int parsePokedexId(const nlohmann::json &pokemonDataDetails) const;
        std::vector<std::string> parsePokemonEggGroups(const nlohmann::json &pokemonDataSpecies) const;
        std::vector<std::string> parsePokemonTyping(const nlohmann::json &pokemonDataDetails) const;
        std::string parsePokemonName(const nlohmann::json &pokemonDataDetails) const;
        std::vector<Abilities> parsePokemonAbilities(const nlohmann::json &pokemonDataDetails) const;
        Statistics parsePokemonStats(const nlohmann::json &pokemonDataDetails);
};

#endif