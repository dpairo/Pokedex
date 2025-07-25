//  Definition of the interface for all the data mappers

#ifndef _SINGLE_POKEMON_MAPPER.H_
#define _SINGLE_POKEMON_MAPPER.H_

#include "Domain/PokemonDTO.h"
#include "Domain/IMapper.h"

class SinglePokemonMapper : public IJsonMapper {
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
        const std::string eggGruopsSeeker = "egg_groups";
        const std::string idSeeker = "id";
        const std::string baseExperienceSeeker = "base_experience";
        const std::string hatchCounterSeeker = "hatch_counter";
        const std::string evolutionChainSeeker = "evolution_chain";
        const std::string urlSeeker = "url";
        const std::string chainSeeker = "chain";
        const std::string speciesSeeker = "species";
        const std::string evolvesToSeeker = "evolves_to";
        void extractEvolutionChain(const nlohmann::json &jsonNode, std::vector<std::string> &evolutionChain);
        void parseEvolutionChainUrl(const nlohmann::json &pokemonDataSpecies, std::string &evolutionChainUrl);
        int parsePokemonHatchCounter(const nlohmann::json &pokemonDataSpecies);
        int parsePokemonBaseExp(const nlohmann::json &pokemonDataDetails);
        int parsePokedexId(const nlohmann::json &pokemonDataDetails);
        std::vector<std::string> parsePokemonEggGroups(const nlohmann::json &pokemonDataSpecies);
        std::vector<std::string> parsePokemonTyping(const nlohmann::json &pokemonDataDetails);
        std::string parsePokemonName(const nlohmann::json &pokemonDataDetails);
        std::vector<Ability> parsePokemonAbilities(const nlohmann::json &pokemonDataDetails);
        Statistics parsePokemonStats(const nlohmann::json &pokemonDataDetails);
    public:
        PokemonDTO transformDataPokemonJson(const std::string &pokemonDetailsRawJson, const std::string &pokemonSpeciesRawJson, std::string &evolutionChainUrl) override;
        std::vector<std::string> transformEvolutionChainJson(const std::string &pokemonEvoltuionChainRawJson);
};

#endif