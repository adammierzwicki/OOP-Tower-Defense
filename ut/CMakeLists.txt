project(td_ut)

include(CTest)

if(BUILD_TESTING)
    set(HEADERS
        inc/queueFixture.h
        inc/towerFixture.h
    )
    set(SOURCES
        src/queueTests.cpp
        src/towerTests.cpp
    )
    add_executable(tower_defense_tests ${HEADERS} ${SOURCES})

    target_link_libraries(tower_defense_tests PRIVATE GTest::gmock_main GTest::gtest_main game_lib)

    if(NOT WIN32)
        include(GoogleTest)
        gtest_discover_tests(tower_defense_tests)
    endif()
endif()