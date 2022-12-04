# CMakeList.txt : CMake project for adventofcode2022, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (day01 day01.cpp utils.h utils.cpp)
configure_file(day01.txt . COPYONLY)

add_executable (day02 day02.cpp utils.h utils.cpp)
configure_file(day02.txt . COPYONLY)

add_executable (day03 day03.cpp utils.h utils.cpp)
configure_file(day03.txt . COPYONLY)

add_executable (day04 day04.cpp utils.h utils.cpp)
#configure_file(day04.txt . COPYONLY)
