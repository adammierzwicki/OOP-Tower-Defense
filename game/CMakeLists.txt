cmake_minimum_required(VERSION 3.22..3.28)

project(game)

set(HEADERS
    inc/animation.h
    inc/customQueue.h
    inc/drawableObject.h
    inc/enemy.h
    inc/game.h
    inc/gun.h
    inc/levelInfo.h
    inc/menu.h
    inc/selectBox.h
    inc/tower.h
    inc/ui.h
    inc/windowHandler.h
    )

set(SOURCES
    src/animation.cpp
    src/customQueue.cpp
    src/drawableObject.cpp
    src/enemy.cpp
    src/game.cpp
    src/gun.cpp
    src/levelInfo.cpp
    src/menu.cpp
    src/selectBox.cpp
    src/tower.cpp
    src/ui.cpp
    src/windowHandler.cpp
   )

add_executable(game ${HEADERS} ${SOURCES})
add_library(game_lib STATIC ${HEADERS} ${SOURCES})
set_target_properties(game PROPERTIES ENABLE_EXPORTS ON)

target_link_libraries(game PRIVATE SFML::Graphics)