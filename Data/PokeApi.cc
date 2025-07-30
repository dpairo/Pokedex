//  Implementation of the PokeApi functions.

#include <iostream>
#include <curl/curl.h>

#include "PokeApi.h"
#include "JsonMappers/SinglePokemonMapper.h"
#include "JsonMappers/AllPokemonMapper.h"

//  size -> Size of each data unit received.
//  numberEntities -> Number of units of that size received.
size_t  PokeApi::callBack(void* contents, size_t size, size_t numberEntities, std::string* output) {
    const size_t totalSize = size * numberEntities;
    output->append((char*)contents, totalSize);
    return totalSize;
}

void PokeApi::sendRequest(CURL* curl) {
    CURLcode apiResponse = curl_easy_perform(curl);                 //  starts with the request and calls callBack everytime that gets data.

    if(apiResponse != CURLE_OK) {
        //  call exceptions
    }
}

void PokeApi::setCurlOptions(CURL* curl, const std::string& fullUrl, std::string& responseData) {
    curl_easy_setopt(curl, CURLOPT_URL, fullUrl.c_str());           //  configures the url (only works with char).
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callBack);        //  everytime you recieve data use that function (callBack).
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);       //  set the string where the data will be stored.
}

bool startsWith(const std::string& fullString, const std::string& prefix) {
    return fullString.size() >= prefix.size() &&
           fullString.compare(0, prefix.size(), prefix) == 0;
}

std::string PokeApi::makeRequest(const std::string &endpoint) {
    const std::string prefix = "http";
    std::string fullUrl;

    if (startsWith(endpoint, prefix)) {
        fullUrl = endpoint;
    } else {
        const std::string baseUrl = "https://pokeapi.co/api/v2/";
        fullUrl = baseUrl + endpoint;
    }

    std::string responseData;
    CURL* curl = curl_easy_init();

    if(curl) {                                                          //  checks that everything is ok to start configuration.
        setCurlOptions(curl, fullUrl, responseData);
        sendRequest(curl);
        curl_easy_cleanup(curl);
    }
    return responseData;
}

std::string PokeApi::getPokemonName() {
    std::string pokemonName;

    do {
        std::cout << "Write the pokemon name: ";
        getline(std::cin, pokemonName);

        if(pokemonName.empty()) {
            system("clear");
            std::cout << "Please, write a pokemon name." << std::endl;
        }
    
    } while(pokemonName.empty());

    return pokemonName;
}

//  All the Pokemon information is splited into three url.
PokemonDTO PokeApi::getPokemonByName(const std::string &pokemonName) {
    std::string pokemonDetailsRequest = "pokemon/";
    std::string pokemonSpeciesRequest = "pokemon-species/";

    std::string pokemonDetailsEndpoint = pokemonDetailsRequest + pokemonName;
    std::string pokemonSpeciesEndpoint = pokemonSpeciesRequest + pokemonName;

    std::string pokemonDetailsRawJson = makeRequest(pokemonDetailsEndpoint);
    std::string pokemonSpeciesRawJson = makeRequest(pokemonSpeciesEndpoint);

    SinglePokemonMapper pokemonMapper;
    std::string pokemonEvolutionChainRequest;
    PokemonDTO dto = pokemonMapper.transformDataPokemonJson(pokemonDetailsRawJson, pokemonSpeciesRawJson, pokemonEvolutionChainRequest);

    std::string pokemonEvolutionChainRawJson = makeRequest(pokemonEvolutionChainRequest);
    dto.evolutionChain = pokemonMapper.transformEvolutionChainJson(pokemonEvolutionChainRawJson);

    return(dto);
}

std::vector<std::string> PokeApi::getAllPokemon() {
    const std::string allPokemonEndPoint = "pokemon?limit=100000";

    const std::string allPokemonRawJson = makeRequest(allPokemonEndPoint);

    AllPokemonMapper pokemonMapper;

    std::vector<std::string> allPokemon = pokemonMapper.transformAll(allPokemonRawJson);

    return allPokemon;
}

std::vector<std::string> PokeApi::getAllMoves() {
    const std::string allMovesEndPoint = "move?limit=100000";

    const std::string allMovesRawJson = makeRequest(allMovesEndPoint);

    AllPokemonMapper pokemonMapper;

    std::vector<std::string> allMoves = pokemonMapper.transformAll(allMovesRawJson);

    return allMoves;
}

std::vector<std::string> PokeApi::getAllAbilities() {
    const std::string allAbilitiesEndPoint = "ability?limit=100000";

    const std::string allAbilitiesRawJson = makeRequest(allAbilitiesEndPoint);

    AllPokemonMapper pokemonMapper;

    std::vector<std::string> allAbilities = pokemonMapper.transformAll(allAbilitiesRawJson);

    return allAbilities;
}

void PokeApi::getMovePoolFromPokemon(const std::string &pokemonName, std::vector<std::string> &allMoves, std::vector<std::string> &allMethods, std::string &lastVersion) {
    const std::string pokemonDetailsRequest = "pokemon/";
    const std::string pokemonVersionsEndPoint = "version-group?limit=100000&offset=0";
    const std::string pokemonDetailsEndpoint = pokemonDetailsRequest + pokemonName;

    const std::string pokemonAndMovePoolRawString = makeRequest(pokemonDetailsEndpoint);
    const std::string pokemonVersionsRawString = makeRequest(pokemonVersionsEndPoint);

    SinglePokemonMapper pokemonMapper;
    pokemonMapper.transformMovePool(pokemonAndMovePoolRawString,pokemonVersionsRawString,allMoves,allMethods, lastVersion);
}


