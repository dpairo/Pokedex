//  Implementation to the Json mapper to parse Json when just 1 pokemon has been requested

#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>
#include <unordered_map>

#include "SinglePokemonMapper.h"

void SinglePokemonMapper::extractEvolutionChain(const nlohmann::json &evolutionNode, std::vector<std::string> &evolutionChain) {
    evolutionChain.push_back(evolutionNode[speciesSeeker][nameSeeker]);

    for(const auto &nextEvolution : evolutionNode[evolvesToSeeker]) {
        extractEvolutionChain(nextEvolution, evolutionChain);
    }
}

std::vector<std::string> SinglePokemonMapper::transformEvolutionChainJson(const std::string &pokemonEvoltuionChainRawJson) {
    nlohmann::json pokemonEvolutionChainData = nlohmann::json::parse(pokemonEvoltuionChainRawJson);
    nlohmann::json jsonBlock = pokemonEvolutionChainData[chainSeeker];
    std::vector<std::string> evolutionChain;

    extractEvolutionChain(jsonBlock, evolutionChain);

    return evolutionChain;
}

void SinglePokemonMapper::parseEvolutionChainUrl(const nlohmann::json &pokemonDataSpecies, std::string &evolutionChainUrl) {
    evolutionChainUrl = pokemonDataSpecies[evolutionChainSeeker][urlSeeker];
}

int SinglePokemonMapper::parsePokemonHatchCounter(const nlohmann::json &pokemonDataSpecies) {
    int stepsToEclose = 255;
    return pokemonDataSpecies[hatchCounterSeeker].get<int>() * stepsToEclose;
}

int SinglePokemonMapper::parsePokemonBaseExp(const nlohmann::json &pokemonDataDetails) {
    return pokemonDataDetails[baseExperienceSeeker];
}

int SinglePokemonMapper::parsePokedexId(const nlohmann::json &pokemonDataDetails){
    return pokemonDataDetails[idSeeker];
}

std::vector<std::string> SinglePokemonMapper::parsePokemonEggGroups(const nlohmann::json &pokemonDataSpecies){
    std::vector<std::string> eggGroups;

    for(const auto &eggGroupData : pokemonDataSpecies[eggGroupsSeeker]) {
        eggGroups.push_back(eggGroupData[nameSeeker]);
    }
    return eggGroups;
}

std::vector<std::string> SinglePokemonMapper::parsePokemonTyping(const nlohmann::json &pokemonDataDetails) {
    std::vector<std::string> typing;

    for (const auto& typeInfo : pokemonDataDetails[typesSeeker]) {
        std::string typeName = typeInfo[singleTypeSeeker][nameSeeker];
        typing.push_back(typeName);
    }
    return typing;
}

Statistics SinglePokemonMapper::parsePokemonStats(const nlohmann::json &pokemonDataDetails) {
    Statistics pokemonStats;

    std::unordered_map<std::string, int Statistics::*> statsMap = {
        {healthSeeker, &Statistics::health},
        {attackSeeker, &Statistics::attack},
        {defenseSeeker, &Statistics::defense},
        {specialAttackSeeker, &Statistics::specialAttack},
        {specialDefenseSeeker, &Statistics::specialDefense},
        {speedSeeker, &Statistics::speed},
    };

    for(const auto &statsData : pokemonDataDetails[statsSeeker]) {
        std::string statName = statsData[singleStatSeeker][nameSeeker];
        int baseStatValue = statsData[baseStatValueSeeker];

        auto pair = statsMap.find(statName);

        if(pair != statsMap.end()) {
            pokemonStats.*(pair->second) = baseStatValue;
        }
    }
    return pokemonStats;
}

std::vector<Abilities> SinglePokemonMapper::parsePokemonAbilities(const nlohmann::json &pokemonDataDetails) {
    std::vector<Abilities> abilitiesSet;

    for(const auto &abilityData : pokemonDataDetails[abilitiesSeeker]) {
        Abilities auxiliarAbility;
        auxiliarAbility.name = abilityData[abilitySeeker][nameSeeker];
        auxiliarAbility.isHidden = abilityData[isAbilityHiddenSeeker];
        auxiliarAbility.slot = abilityData[slotSeeker];

        abilitiesSet.push_back(auxiliarAbility);
    }
    return abilitiesSet;
}

std::string SinglePokemonMapper::parsePokemonName(const nlohmann::json &pokemonDataDetails) {
    return pokemonDataDetails[nameSeeker];
}

PokemonDTO SinglePokemonMapper::transformDataPokemonJson(const std::string &pokemonDetailsRawJson, const std::string &pokemonSpeciesRawJson, std::string &evolutionChainUrl) {
    nlohmann::json pokemonDataDetails = nlohmann::json::parse(pokemonDetailsRawJson);
    nlohmann::json pokemonDataSpecies = nlohmann::json::parse(pokemonSpeciesRawJson);

    PokemonDTO dto;
    dto.name = parsePokemonName(pokemonDataDetails);
    dto.abilities = parsePokemonAbilities(pokemonDataDetails);
    dto.stats = parsePokemonStats(pokemonDataDetails);
    dto.typing = parsePokemonTyping(pokemonDataDetails);
    dto.eggGroup = parsePokemonEggGroups(pokemonDataSpecies);
    dto.id = parsePokedexId(pokemonDataDetails);
    dto.hatchCounter = parsePokemonHatchCounter(pokemonDataSpecies);
    dto.baseExperience = parsePokemonBaseExp(pokemonDataDetails);
    parseEvolutionChainUrl(pokemonDataSpecies, evolutionChainUrl);

    return dto;
}


