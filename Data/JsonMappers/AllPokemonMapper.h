#ifndef ALLPOKEMONMAPPER_H
#define ALLPOKEMONMAPPER_H

#include <vector>
#include <nlohmann/json.hpp>

class AllPokemonMapper {
    public:
        std::vector<std::string> transformAll(const std::string &allJson) const;

    private:
        const std::string resultsSeeker = "results";
        const std::string nameSeeker = "name";
        std::vector<std::string> parseAll(const nlohmann::json &allJson) const;
};
#endif
