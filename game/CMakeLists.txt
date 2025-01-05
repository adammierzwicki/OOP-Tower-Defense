cmake_minimum_required(VERSION 3.6..3.28)

project(td_game)

set(HEADERS
    inc/animation.h
    inc/customQueue.h
    inc/drawableObject.h
    inc/endGame.h
    inc/enemy.h
    inc/game.h
    inc/gun.h
    inc/levelInfo.h
    inc/logger.h
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
    src/logger.cpp
    src/main.cpp
    src/menu.cpp
    src/selectBox.cpp
    src/tower.cpp
    src/ui.cpp
    src/windowHandler.cpp
)
add_library(game_lib STATIC ${HEADERS} ${SOURCES})
target_link_libraries(game_lib PUBLIC sfml-graphics sfml-window sfml-audio sfml-system)

if(WIN32)
    target_link_libraries(game_lib PUBLIC sfml-main)
endif()

add_executable(td_game ${HEADERS} ${SOURCES})
target_link_libraries(td_game PUBLIC sfml-graphics sfml-window sfml-audio sfml-system)

if(WIN32)
    target_link_libraries(td_game PUBLIC sfml-main)
endif()

# target_link_libraries(td_game PUBLIC game_lib)
set_target_properties(td_game PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    OUTPUT_NAME "tower-defense"
)

add_custom_command(TARGET td_game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_BINARY_DIR}/external/SFML-2.6.2/lib"
    "${CMAKE_BINARY_DIR}/bin"
)