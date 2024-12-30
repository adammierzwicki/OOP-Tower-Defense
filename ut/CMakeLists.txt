project(ut)

include(CTest)

if(BUILD_TESTING)
   set(HEADERS
      inc/queueFixture.h
      )
   set(SOURCES
      src/queueTests.cpp
      )
   
   add_executable(ut ${HEADERS} ${SOURCES})
   target_link_libraries(ut PRIVATE GTest::gtest_main game_lib)

   include(GoogleTest)
   gtest_discover_tests(ut)
endif()