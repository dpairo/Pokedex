#include <iostream>

#include "Data/PokeApi.h"
#include "Domain/Pokemon.h"

int main() {

    PokeApi api;
    Pokemon charizard(api.getPokemonByName("tapu-koko"));

    std::cout << charizard;

    return 0;
}