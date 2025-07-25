// Data transfer objetc for the pokemon class constructor data management, with an abstraction layer added as well.

#ifndef POKEMON_DTO_H
#define POKEMON_DTO_H

#include <string>
#include <vector>

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

struct PokemonDTO {
    std::string name;
    std::vector<std::string> eggGroup;
    std::vector<std::string> typing;
    std::vector<std::string> evolutionChain;
    std::vector<Abilities> abilities;
    Statistics stats;
    int id;
    int baseExperience;
    int hatchCounter;
};

#endif