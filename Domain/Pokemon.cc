#include <iostream>

#include "Pokemon.h"

Pokemon::Pokemon(const PokemonDTO &dto) {
    this->stats = dto.stats;
    this->abilities = dto.abilities;
    this->baseExperience = dto.baseExperience;
    this->eggGroup = dto.eggGroup;
    this->evolutionChain = dto.evolutionChain;
    this->hatchCounter = dto.hatchCounter;
    this->id = dto.id;
    this->name = dto.name;
    this->typing = dto.typing;
}

