# CMakeList.txt : CMake project for adventofcode2022, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (day01 day01.cpp utils.h utils.cpp)
add_executable (day02 day02.cpp utils.h utils.cpp)
add_executable (day03 day03.cpp utils.h utils.cpp)
add_executable (day04 day04.cpp utils.h utils.cpp)
add_executable (day05 day05.cpp utils.h utils.cpp)
add_executable (day06 day06.cpp utils.h utils.cpp)
add_executable (day07 day07.cpp utils.h utils.cpp)
add_executable (day08 day08.cpp utils.h utils.cpp)
add_executable (day09 day09.cpp utils.h utils.cpp)
add_executable (day10 day10.cpp utils.h utils.cpp)

add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/input
    ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Copying resources into binary directory")
