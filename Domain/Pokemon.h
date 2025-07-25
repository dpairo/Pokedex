//  Definition of the clases to store the data obtained with the pokeApi

#ifndef POKEMON_H
#define POKEMON_H

#include <iostream>
#include <vector>
#include "PokemonDTO.h"

struct Moves {
    std::string method;
    std::string moveName;
    std::string category;
    int attackPoints;
    int precision;
};

struct Abilities {
    std::string name;
    bool isHidden;
    int slot;
};

struct Statistics {
    int health;
    int attack;
    int defense;
    int specialAttack;
    int specialDefense;
    int speed;
};

class Pokemon {
    private:
        
        std::vector<std::string> eggGroup;
        std::vector<std::string> typing;
        std::vector<std::string> evolutionChain;
        std::vector<Abilities> abilities;
        Statistics stats;
        int id;
        int baseExperience;
        int hatchCounter;

    public:
        std::string name;
        Pokemon(const PokemonDTO &dataTransferObjetc);

    friend std::ostream &operator<<(std::ostream &os, const Pokemon &Pokemon);
};

#endif