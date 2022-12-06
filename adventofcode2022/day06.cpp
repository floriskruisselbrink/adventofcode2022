#include <iostream>
#include <set>
#include "utils.h"

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

int main()
{
    std::cout << "AOC 2022, Day 6: Tuning Trouble\n";

    std::string input = read_lines("day06.txt")[0];

    int score_part1{find_marker(input, 4)};
    std::cout << "Part 1: " << score_part1 << '\n';

    int score_part2{find_marker(input, 14)};
    std::cout << "Part 2: " << score_part2 << '\n';
    return 0;
}