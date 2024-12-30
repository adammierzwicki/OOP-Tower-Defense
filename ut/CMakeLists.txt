cmake_minimum_required(VERSION 3.22)

project(ut)

include(CTest)

if(BUILD_TESTING)
   set(HEADERS
      inc/queueFixture.h
      ../game/inc/customQueue.h
      ../game/inc/tower.h
      ../game/inc/enemy.h
      )
   set(SOURCES
      src/queueTests.cpp
      src/towerTests.cpp
      )
   
   add_executable(ut ${HEADERS} ${SOURCES})
   target_link_libraries(ut PRIVATE GTest::gtest_main game_lib)
   target_link_libraries(ut PUBLIC game_lib sfml-graphics sfml-window sfml-system)

   include(GoogleTest)
   gtest_discover_tests(ut)
endif()