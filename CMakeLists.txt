cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 17)

if (CMAKE_COMPILER_IS_GNUCC)
  option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" FALSE)

  if (ENABLE_COVERAGE)
    add_compile_options(--coverage -O0)
  endif()
endif()

add_library(dubins 
    src/dubins.c)

target_include_directories(dubins 
    PUBLIC 
    include)

target_link_libraries(dubins 
    PUBLIC 
    m)
target_link_libraries(dubins PRIVATE --coverage)

add_executable(main 
    src/main
)

target_link_libraries(main
    PRIVATE
    dubins
)

if (MSVC)
    target_compile_options(dubins PRIVATE /W3)
else()
    target_compile_options(dubins PRIVATE -Wall -Wextra -Wpedantic -std=gnu89)
endif()

if(BUILD_TESTING)
    enable_testing()

    add_executable(unittest_dubins
        tests/montecarlo_tests.cpp
        tests/stableapi_tests.cpp)

    target_link_libraries(unittest_dubins
        dubins
        GTest::Main
        GTest::GTest)
    target_link_libraries(unittest_dubins --coverage)

    add_test(unittest_dubins unittest_dubins)
endif(BUILD_TESTING)
