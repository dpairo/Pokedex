//  Implementation of pokeApi functions

#include <iostream>
#include <curl/curl.h>
#include "PokeApi.h"

const std::string baseUrl = "https://pokeapi.co/api/v2/";

size_t callBack(void* contents, size_t size, size_t numberEntities, std::string* output) {
    //  size -> Size of each data unit recieved
    //  numberEntities -> Number of units of that size received

    size_t totalSize = size * numberEntities;
    output->append((char*)contents, totalSize);
    return totalSize;
}

std::string PokeApi::makeRequest(const std::string &endpoint) {
    std::string fullUrl = baseUrl + endpoint;
    std::string responseData;

    CURL* curl = curl_easy_init();

    if(curl) {                                                          //  checks that everything is ok to start configuration
        curl_easy_setopt(curl, CURLOPT_URL, fullUrl.c_str());           //  configures the url (only works with char)
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callBack);        //  everytime you recieve data use that function (callBack)
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);       //  set the string where the data will be stored
        CURLcode apiResponse = curl_easy_perform(curl);                 //  starts with the request and calls callBack everytime that gets data

        if(apiResponse != CURLE_OK) {
            //  call excepcions
        }
        curl_easy_cleanup(curl);
    }
    return responseData;
}

std::string getPokemonName() {
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

Pokemon PokeApi::getPokemonByName() {
    std::string typeRequest = "pokemon/";
    std::string pokemonName = getPokemonName();
    std::string endpoint;
    endpoint = typeRequest + pokemonName;
    
    makeRequest(endpoint);
}