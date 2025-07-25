#include <iostream>

#include "Data/PokeApi.h"
#include "Domain/Pokemon.h"

int main() {

    PokeApi api;
    Pokemon charizard(api.getPokemonByName("charizard"));

    std::cout << charizard.name;

    return 0;
}