//  Definition of the clases to store the data obtained with the pokeApi

#ifndef POKEMON_H
#define POKEMON_H

#include <iostream>
#include <vector>
#include "PokemonDTO.h"

class Pokemon {
    private:
        std::string name;
        std::vector<std::string> eggGroup;
        std::vector<std::string> typing;
        std::vector<std::string> evolutionChain;
        std::vector<Abilities> abilities;
        Statistics stats;
        int id;
        int baseExperience;
        int hatchCounter;

    public:
        Pokemon(const PokemonDTO &dataTransferObjetc);
        std::string getName() const;
        std::vector<std::string> getEggGroup() const;
        std::vector<std::string> getTyping() const;
        std::vector<std::string> getEvolutionChain() const;
        std::vector<Abilities> getAbilities() const;
        Statistics getStatistics() const;
        int getId() const;
        int getbaseExperience() const;
        int gethatchCounter() const;

    friend std::ostream &operator<<(std::ostream &os, const Pokemon &Pokemon);
};

#endif