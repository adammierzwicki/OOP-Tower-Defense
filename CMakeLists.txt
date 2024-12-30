cmake_minimum_required(VERSION 3.22)

project(towerDefense)

include(cmake/UpdateSubmodules.cmake)

add_subdirectory(game)
add_subdirectory(ut)
add_subdirectory(external)