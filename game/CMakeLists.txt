cmake_minimum_required(VERSION 3.22..3.28)

project(game)

set(HEADERS
    inc/animation.h
    inc/customQueue.h
    inc/drawableObject.h
    inc/endGame.h
    inc/enemy.h
    inc/game.h
    inc/gun.h
    inc/levelInfo.h
    inc/menu.h
    inc/prices.h
    inc/selectBox.h
    inc/tower.h
    inc/ui.h
    inc/windowHandler.h
    )

set(SOURCES
    src/animation.cpp
    src/drawableObject.cpp
    src/endGame.cpp
    src/enemy.cpp
    src/game.cpp
    src/gun.cpp
    src/levelInfo.cpp
    src/menu.cpp
    src/prices.cpp
    src/selectBox.cpp
    src/tower.cpp
    src/ui.cpp
    src/windowHandler.cpp
   )

add_executable(towerDefense src/main.cpp ${HEADERS} ${SOURCES})
target_include_directories(towerDefense PRIVATE inc)
add_library(game_lib STATIC ${HEADERS} ${SOURCES})
target_link_libraries(towerDefense PUBLIC game_lib sfml-graphics sfml-window sfml-system)
