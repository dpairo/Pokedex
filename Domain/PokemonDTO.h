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

struct Habilities {
    std::string name;
    bool isHidden;
    int slot;
};

struct Statisticks {
    int health;
    int attack;
    int defense;
    int specialAttack;
    int specialDefense;
    int speed;
};

struct PokemonDTO {
    std::string name;
    std::string primaryType;
    std::string secondaryType;
    std::string eggGroup;
    std::vector<Habilities> abilities;
    std::vector<Moves> movements;
    Statisticks stats;
    int id;
    int baseExperience;
    int hatchCounter;
};

#endif