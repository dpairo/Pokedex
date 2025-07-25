//  Implementation of the PokeApi functions.

#include <iostream>
#include <curl/curl.h>

#include "PokeApi.h"
#include "JsonMappers/SinglePokemonMapper.h"

//  size -> Size of each data unit recieved.
//  numberEntities -> Number of units of that size received.
size_t PokeApi::callBack(void* contents, size_t size, size_t numberEntities, std::string* output) {
    size_t totalSize = size * numberEntities;
    output->append((char*)contents, totalSize);
    return totalSize;
}

void PokeApi::sendRequest(CURL* curl) {
    CURLcode apiResponse = curl_easy_perform(curl);                 //  starts with the request and calls callBack everytime that gets data.

    if(apiResponse != CURLE_OK) {
        //  call excepcions
    }
}

void PokeApi::setCurlOptions(CURL* curl, const std::string& fullUrl, std::string& responseData) {
    curl_easy_setopt(curl, CURLOPT_URL, fullUrl.c_str());           //  configures the url (only works with char).
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callBack);        //  everytime you recieve data use that function (callBack).
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);       //  set the string where the data will be stored.
}

std::string PokeApi::makeRequest(const std::string &endpoint) {
    const std::string baseUrl = "https://pokeapi.co/api/v2/";

    std::string fullUrl = baseUrl + endpoint;
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

//  All the pokemon informations is splited into three url.
PokemonDTO PokeApi::getPokemonByName(const std::string &pokemonName) {
    std::string pokemonDetailsRequest = "pokemon/";
    std::string pokemonSpeciesRequest = "pokemon-species/";
    std::string pokemonEvoltuionChainRequest;
    std::string pokemonDetailsEndpoint = pokemonDetailsRequest + pokemonName;
    std::string pokemonSpeciesEndpoint = pokemonSpeciesRequest + pokemonName;

    std::string pokemonDetailsRawJson = makeRequest(pokemonDetailsEndpoint);
    std::string pokemonSpeciesRawJson = makeRequest(pokemonDetailsRequest);

    SinglePokemonMapper pokemonMapper;
    PokemonDTO dto = pokemonMapper.transformDataPokemonJson(pokemonDetailsRawJson, pokemonSpeciesRawJson, pokemonEvoltuionChainRequest);

    std::string pokemonEvoltuionChainRawJson = makeRequest(pokemonEvoltuionChainRequest);
    dto.evolutionChain = pokemonMapper.transformEvolutionChainJson(pokemonEvoltuionChainRawJson);

    return(dto);
}

std::vector<std::unique_ptr<Pokemon>> PokeApi::getAllPokemon() {
    std::string typeRequest = "pokemon?limit=100000";
    std::string endpoint = typeRequest;
}

std::vector<std::unique_ptr<Moves>> PokeApi::getAllMoves() {
    std::string typeRequest = "move?limit=100000";
    std::string endpoint = typeRequest;

    makeRequest(endpoint);
}

std::vector<std::unique_ptr<Abilities>> PokeApi::getAllAbilities() {
    std::string typeRequest = "ability?limit=100000";
    std::string endpoint = typeRequest;

    makeRequest(endpoint);
}