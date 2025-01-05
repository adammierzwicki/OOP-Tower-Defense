cmake_minimum_required(VERSION 3.6..3.28)

project(towerDefense)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/UpdateSubmodules.cmake)

set(SFML_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/SFML-2.6.2/include)
include_directories(${SFML_INCLUDE_DIR})

set(SFML_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/SFML-2.6.2/lib)
link_directories(${SFML_LIB_DIR})

add_subdirectory(external)
add_subdirectory(game)
add_subdirectory(ut)

set(CONFIGURATION "x86")

if(CMAKE_SYSTEM_PROCESSOR STREQUAL "AMD64")
    set(CONFIGURATION "x64")
endif()

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/external/SFML-2.6.2/extlibs/bin/${CONFIGURATION}/openal32.dll"
    DESTINATION "${CMAKE_BINARY_DIR}/bin"
)
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/external/SFML-2.6.2/extlibs/bin/${CONFIGURATION}/openal32.dll"
    DESTINATION "${CMAKE_BINARY_DIR}/ut"
)