#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "utils.h"

using IntRange = std::pair<int, int>;

bool fully_overlaps(IntRange left, IntRange right)
{
    return 
        ((left.first <= right.first) && (left.second >= right.second))
        || ((right.first <= left.first) && (right.second >= left.second));
}

bool partly_overlaps(IntRange left, IntRange right)
{
    return 
        ((right.first <= left.second) && (right.second >= left.second))
        || ((left.first <= right.second) && (left.second >= right.second));
}

int main()
{
    std::cout << "AOC 2022, Day 4: Camp Cleanup\n";

    auto input{read_lines("day04.txt")};

    int full_overlaps{0};
    int part_overlaps{0};
    for (auto &line: input)
    {
        std::vector<std::string> numbers = split(line, "-,");
        IntRange left{std::stoi(numbers[0]), std::stoi(numbers[1])};
        IntRange right{std::stoi(numbers[2]), std::stoi(numbers[3])};

        if (fully_overlaps(left, right)) {
            full_overlaps++;
        }
        else if (partly_overlaps(left, right)) {
            part_overlaps++;
        }
    } 

    std::cout << "Part 1: " << full_overlaps << '\n';
    std::cout << "Part 2: " << full_overlaps + part_overlaps << '\n';
    return 0;
}