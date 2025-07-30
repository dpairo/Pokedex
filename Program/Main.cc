#include <iostream>

#include "Data/PokeApi.h"
#include "Domain/Pokemon.h"
#include "View/TerminalViewer.h"

int main() {
    PokeApi api;
    //TerminalViewer viewer;

    Pokemon charizard(api.getPokemonByName("tapu-koko"));
    std::vector<std::string> allPokemonMoves;
    std::vector<std::string> allMethodsMoves;
    std::string lastVersion;

    std::vector<std::string> pokemonMoves = api.getAllAbilities();

    api.getMovePoolFromPokemon("tapu-koko", allPokemonMoves, allMethodsMoves, lastVersion);


    std::cout << charizard << std::endl << std::endl << "showing movepool from: " << lastVersion << std::endl;

    for (int i = 0; i < allPokemonMoves.size(); i++) {
        std::cout << allPokemonMoves[i] << " - " << allMethodsMoves[i] << std::endl;
    }

    std::cout << std::endl;
    for (const std::string &pokemonMove : pokemonMoves) {
        std::cout << pokemonMove << std::endl;
    }

    return 0;
}