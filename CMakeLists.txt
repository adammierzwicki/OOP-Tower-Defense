cmake_minimum_required(VERSION 3.22)

project(towerDefense)

include(cmake/UpdateSubmodules.cmake)
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_subdirectory(game)
add_subdirectory(ut)
add_subdirectory(external)