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

std::string Pokemon::getName() const {
    return this->name;
}
std::vector<std::string> Pokemon::getEggGroup() const {
    return this->eggGroup;
}
std::vector<std::string> Pokemon::getTyping() const {
    return this->typing;
}
std::vector<std::string> Pokemon::getEvolutionChain() const {
    return this->evolutionChain;
}
std::vector<Abilities> Pokemon::getAbilities() const {
    return this->abilities;
}
Statistics Pokemon::getStatistics() const {
    return this->stats;
}
int Pokemon::getId() const {
    return this->id;
}
int Pokemon::getbaseExperience() const {
    return this->baseExperience;
}
int Pokemon::gethatchCounter() const {
    return this->hatchCounter;
}

std::ostream &operator<<(std::ostream &os, const Pokemon &pokemon) {
    os  << "Information about " << pokemon.name << ":" << std::endl
        << "Pokedex Id: " << pokemon.id << std::endl;

    os  << "Typing: " << std::endl;
    for(const std::string &type : pokemon.typing) {
        os << "\t" << type << std::endl;
    }

    os << "Abilities:" << std::endl;
    for(const Abilities &ability : pokemon.abilities) {
        os << "\t" << ability.slot << ": " <<ability.name << std::endl;
        if(ability.isHidden) {
            os << "\t\tIs Hidden" << std::endl;
        }
    }

    os  << "Stats: " << std::endl
        << "\t" << "Hp: " << pokemon.stats.health << std::endl
        << "\t" << "Attack: " << pokemon.stats.attack << std::endl
        << "\t" << "Defense: " << pokemon.stats.defense << std::endl
        << "\t" << "Special Attack: " << pokemon.stats.specialAttack << std::endl
        << "\t" << "Special Defense: " << pokemon.stats.specialDefense << std::endl
        << "\t" << "Speed: " << pokemon.stats.speed << std::endl;

    os << "Evolution Chain:" << std::endl << "\t";
    for (size_t i = 0; i < pokemon.evolutionChain.size(); ++i) {
        os << pokemon.evolutionChain[i];
        if (i < pokemon.evolutionChain.size() - 1) {
            os << " - ";
        }
    }
    os << std::endl;

    os << "Egg Group: " << std::endl << "\t";
    for(size_t i = 0; i < pokemon.eggGroup.size(); ++i) {
        os << pokemon.eggGroup[i];
        if(i < pokemon.eggGroup.size() - 1) {
            os << " - ";
        } 
    }
    os << std::endl;

    os  << "Base experience: " << pokemon.baseExperience << std::endl
        << "Steps to eclose: " << pokemon.hatchCounter << std::endl;

    return os;
}
