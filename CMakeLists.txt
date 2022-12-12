cmake_minimum_required(VERSION 3.21)

project(
    aoc
    VERSION 1.0
    DESCRIPTION "Advent of Code Solutions in C++"
    LANGUAGES CXX
)

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE
    cxx_std_20
)
target_compile_options(compiler_flags INTERFACE
    "$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>"
)

add_executable(aoc 
    main.cpp 
    adventofcode2022/day01.cpp
    adventofcode2022/day02.cpp
    adventofcode2022/day03.cpp
    adventofcode2022/day04.cpp
    adventofcode2022/day05.cpp
    adventofcode2022/day06.cpp
    adventofcode2022/day07.cpp
    adventofcode2022/day08.cpp
    adventofcode2022/day09.cpp
    adventofcode2022/day10.cpp
    adventofcode2022/day11.cpp
    adventofcode2022/day12.cpp
    adventofcode2022/day13.cpp
    adventofcode2022/day14.cpp
    adventofcode2022/day15.cpp
    adventofcode2022/day16.cpp
    adventofcode2022/day17.cpp
    adventofcode2022/day18.cpp
    adventofcode2022/day19.cpp
    adventofcode2022/day20.cpp
    adventofcode2022/day21.cpp
    adventofcode2022/day22.cpp
    adventofcode2022/day23.cpp
    adventofcode2022/day24.cpp
    adventofcode2022/day25.cpp
    )
target_link_libraries(aoc PUBLIC compiler_flags)
target_include_directories(aoc PUBLIC "${PROJECT_SOURCE_DIR}")

add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/adventofcode2022/input
    ${CMAKE_CURRENT_BINARY_DIR}/adventofcode2022/input
    COMMENT "Copying resources into binary directory"
)