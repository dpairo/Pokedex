//  Implementation to the Json mapper to parse Json when just 1 pokemon has been requested

#include <nlohmann/json.hpp>
#include <vector>
#include <unordered_map>

#include "SinglePokemonMapper.h"

void SinglePokemonMapper::parseMovePool(const nlohmann::json &movePoolJson , std::vector<std::string>& allMoves,  std::vector<std::string>& allMethods, const std::string &lastVersion) const {
    for (const auto &moves : movePoolJson[movesSeeker]) {
        for (const auto &methods : moves[versionDetailsSeeker]) {
            const std::string method = methods[versionGroupSeeker][nameSeeker].get<std::string>();
            if (lastVersion == method) {
                allMoves.push_back(moves[singularMoveSeeker][nameSeeker].get<std::string>());
                allMethods.push_back(methods[learnMethodSeeker][nameSeeker].get<std::string>());
            }
        }
    }
}

std::string SinglePokemonMapper::getPokemonLastVersion(const nlohmann::json &pokemonAndMovePoolJson,const std::unordered_map<std::string, int> &versionsMap) const {
    std::string pokemonLastVersion = redBluesSeeker;
    int highestId = 0;
    auto it0 = versionsMap.find(pokemonLastVersion);
    if (it0 != versionsMap.end()) {
        highestId = it0->second;
    }

    for (const auto &pokemonMove : pokemonAndMovePoolJson[movesSeeker]) {
        for (const auto &version : pokemonMove[versionDetailsSeeker]) {
            std::string candidate = version[versionGroupSeeker][nameSeeker].get<std::string>();
            auto it = versionsMap.find(candidate);
            if (it != versionsMap.end() && it->second > highestId) {
                highestId = it->second;
                pokemonLastVersion = candidate;
            }
        }
    }
    return pokemonLastVersion;
}

std::unordered_map<std::string,int> SinglePokemonMapper::getVersionsWithId(const nlohmann::json &versionJson) const {
    const std::string indigoDisk = "the-indigo-disk";
    const std::string tealMask = "the-teal-mask";
    const std::string isleOfArmor = "the-isle-of-armor";
    const std::string crownTundra = "the-crown-tundra";
    const std::string swordShield = "sword-shield";
    const std::string scarletViolet = "scarlet-violet";

    std::unordered_map<std::string,int> versionsMap;
    int currentVersion = 0;

    if (!versionJson.contains("results")) {
        return versionsMap;
    }

    for (const auto &entry : versionJson[resultsSeeker]) {
        if (!entry.contains(nameSeeker)) continue;
        std::string versionName = entry[nameSeeker].get<std::string>();
        ++currentVersion;
        if (versionName == indigoDisk || versionName == tealMask) {
            versionName = scarletViolet;
        }
        else if (versionName == isleOfArmor || versionName == crownTundra) {
            versionName = swordShield;
        }

        versionsMap.emplace(versionName, currentVersion);
    }

    static const std::vector<std::string> versionsToErase = {
        "red-green-japan","blue-japan","brilliant-diamond-and-shining-pearl",
        "lets-go-pikachu-lets-go-eevee","xd","colosseum","legends-arceus"
    };
    for (const auto &bad : versionsToErase) {
        versionsMap.erase(bad);
    }

    return versionsMap;
}

void SinglePokemonMapper::extractEvolutionChain(const nlohmann::json &evolutionNode, std::vector<std::string> &evolutionChain) const {
    evolutionChain.push_back(evolutionNode[speciesSeeker][nameSeeker]);

    for(const auto &nextEvolution : evolutionNode[evolvesToSeeker]) {
        extractEvolutionChain(nextEvolution, evolutionChain);
    }
}

std::vector<std::string> SinglePokemonMapper::transformEvolutionChainJson(const std::string &pokemonEvolutionChainRawJson) const {
    nlohmann::json pokemonEvolutionChainData = nlohmann::json::parse(pokemonEvolutionChainRawJson);
    const nlohmann::json jsonBlock = pokemonEvolutionChainData[chainSeeker];
    std::vector<std::string> evolutionChain;

    extractEvolutionChain(jsonBlock, evolutionChain);

    return evolutionChain;
}

void SinglePokemonMapper::parseEvolutionChainUrl(const nlohmann::json &pokemonDataSpecies, std::string &evolutionChainUrl) const {
    evolutionChainUrl = pokemonDataSpecies[evolutionChainSeeker][urlSeeker];
}

int SinglePokemonMapper::parsePokemonHatchCounter(const nlohmann::json &pokemonDataSpecies) const {
    const int stepsToEclose = 255;
    return pokemonDataSpecies[hatchCounterSeeker].get<int>() * stepsToEclose;
}

int SinglePokemonMapper::parsePokemonBaseExp(const nlohmann::json &pokemonDataDetails) const {
    return pokemonDataDetails[baseExperienceSeeker];
}

int SinglePokemonMapper::parsePokedexId(const nlohmann::json &pokemonDataDetails) const {
    return pokemonDataDetails[idSeeker];
}

std::vector<std::string> SinglePokemonMapper::parsePokemonEggGroups(const nlohmann::json &pokemonDataSpecies) const {
    std::vector<std::string> eggGroups;

    for(const auto &eggGroupData : pokemonDataSpecies[eggGroupsSeeker]) {
        eggGroups.push_back(eggGroupData[nameSeeker]);
    }
    return eggGroups;
}

std::vector<std::string> SinglePokemonMapper::parsePokemonTyping(const nlohmann::json &pokemonDataDetails) const {
    std::vector<std::string> typing;

    for (const auto& typeInfo : pokemonDataDetails[typesSeeker]) {
        std::string typeName = typeInfo[singleTypeSeeker][nameSeeker];
        typing.push_back(typeName);
    }
    return typing;
}

Statistics SinglePokemonMapper::parsePokemonStats(const nlohmann::json &pokemonDataDetails) {
    Statistics pokemonStats{};

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
        const int baseStatValue = statsData[baseStatValueSeeker];

        auto pair = statsMap.find(statName);

        if(pair != statsMap.end()) {
            pokemonStats.*(pair->second) = baseStatValue;
        }
    }
    return pokemonStats;
}

std::vector<Abilities> SinglePokemonMapper::parsePokemonAbilities(const nlohmann::json &pokemonDataDetails) const {
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

std::string SinglePokemonMapper::parsePokemonName(const nlohmann::json &pokemonDataDetails) const {
    return pokemonDataDetails[nameSeeker];
}

void SinglePokemonMapper::transformMovePool(const std::string& pokemonAndMovePoolRawString, const std::string &versionsRawJson, std::vector<std::string> &allMoves, std::vector<std::string> &allMethods, std::string &lastVersion) const {
    const nlohmann::json pokemonAndMovePoolJson = nlohmann::json::parse(pokemonAndMovePoolRawString);
    const nlohmann::json versionsJson = nlohmann::json::parse(versionsRawJson);

    const std::unordered_map<std::string, int> versionsMap = getVersionsWithId(versionsJson);
    lastVersion = getPokemonLastVersion(pokemonAndMovePoolJson, versionsMap);

    parseMovePool(pokemonAndMovePoolJson, allMoves, allMethods, lastVersion);
}

PokemonDTO SinglePokemonMapper::transformDataPokemonJson(const std::string &pokemonDetailsRawJson, const std::string &pokemonSpeciesRawJson, std::string &evolutionChainUrl) {
    const nlohmann::json pokemonDataDetails = nlohmann::json::parse(pokemonDetailsRawJson);
    const nlohmann::json pokemonDataSpecies = nlohmann::json::parse(pokemonSpeciesRawJson);

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
