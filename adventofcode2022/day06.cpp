#include <set>
#include "aoc.h"

int find_marker(const std::string& input, int marker_length)
{
    int position{marker_length};

    std::set<char> marker{};
    for (auto i{input.begin()}, j{i+marker_length}; j <= input.end(); i++, j++)
    {
        marker = {i, j};
        if (marker.size() == marker_length) break;

        position++;
    }

    return position;
}

template<>
auto advent2022::day06() -> result
{
    std::string input = aoc::read_lines("adventofcode2022/input/day06.txt")[0];

    int score_part1{find_marker(input, 4)};
    int score_part2{find_marker(input, 14)};

    return aoc::result(score_part1, score_part2);
}