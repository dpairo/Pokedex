cmake_minimum_required(VERSION 3.26)
project(Pokedex LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS
        *.cc
)

add_executable(Pokedex ${SRC}
        Data/JsonMappers/AllPokemonMapper.cpp
        View/TerminalViewer.h)

list(FILTER SRC EXCLUDE REGEX "${CMAKE_BINARY_DIR}")

target_include_directories(Pokedex PRIVATE
        ${CMAKE_SOURCE_DIR}
        Dataç
        Domain
        Exceptions
        Program
        View
)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(Pokedex PRIVATE nlohmann_json::nlohmann_json)

find_package(CURL REQUIRED)
target_link_libraries(Pokedex PRIVATE CURL::libcurl)

target_compile_options(Pokedex PRIVATE -Wall -Wextra -Wpedantic)