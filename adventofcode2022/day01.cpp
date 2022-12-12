#include <algorithm>
#include <vector>
#include "aoc.h"

template <>
auto advent2022::day01() -> result
{
    std::vector<int> elf_calories{};
    int current_calories{0};

    auto input{aoc::read_lines("adventofcode2022/input/day01.txt")};

    for (const auto &line : input)
    {
        if (line.empty())
        {
            elf_calories.push_back(current_calories);
            current_calories = 0;
        }
        else
        {
            int calories = std::stoi(line);
            current_calories += calories;
        }
    }
    elf_calories.push_back(current_calories);

    std::sort(elf_calories.begin(), elf_calories.end(), std::greater());

    return aoc::result(elf_calories[0], elf_calories[0] + elf_calories[1] + elf_calories[2]);
}