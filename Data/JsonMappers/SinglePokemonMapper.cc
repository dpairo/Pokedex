//  Implementation to the Json mapper to parse Json when just 1 pokemon has been requested

#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>

#include "SinglePokemonMapper.h"

std::vector<Ability> SinglePokemonMapper::parsePokemonAbilities(const nlohmann::json &data) {
    std::vector<Ability> abilitiesSet;

    for(const auto &abilityData : data[abilitiesSeeker]) {
        Ability auxiliarAbility;
        auxiliarAbility.name = abilityData[abilitySeeker][nameSeeker];
        auxiliarAbility.isHidden = abilityData[isAbilityHiddenSeeker];
        auxiliarAbility.slot = abilityData[slotAbilitySeeker];

        abilitiesSet.push_back(auxiliarAbility);
    }

    return abilitiesSet;
}

std::string SinglePokemonMapper::parsePokemonName(const nlohmann::json &data) {
    return data[nameSeeker];
}

PokemonDTO SinglePokemonMapper::transformJson(const std::string &rawJsonString) {
    nlohmann::json data = nlohmann::json::parse(rawJsonString);

    PokemonDTO dto;
    dto.name = parsePokemonName(data);
}


