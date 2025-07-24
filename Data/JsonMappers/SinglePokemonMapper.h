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
        const std::string slotAbilitySeeker = "slot";
        std::string parsePokemonName(const nlohmann::json &data);
        std::vector<Ability> parsePokemonAbilities(const nlohmann::json &data);
    public:
        PokemonDTO transformJson(const std::string& rawJsonString) override;

};

#endif