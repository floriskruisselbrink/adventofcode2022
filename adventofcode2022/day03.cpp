#include "aoc.h"

int priority(char item)
{
    return std::islower(item) ? item - 'a' + 1 : item - 'A' + 27;
}

int solve_part1(const std::vector<std::string> &rucksacks)
{
    int score{0};

    for (const std::string &line : rucksacks)
    {
        auto length{line.size() / 2};
        std::string left{line, 0, length};
        std::string right{line, length};

        std::sort(left.begin(), left.end());
        std::sort(right.begin(), right.end());

        std::string overlap{};

        std::set_intersection(
            left.begin(), left.end(),
            right.begin(), right.end(),
            std::back_inserter(overlap));

        score += priority(overlap[0]);
    }

    return score;
}

char find_common_item(std::string &a, std::string &b, std::string &c)
{
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    std::sort(c.begin(), c.end());

    std::string x{};
    std::string y{};

    std::set_intersection(
        a.begin(), a.end(),
        b.begin(), b.end(),
        std::back_inserter(x));
    
    std::set_intersection(
        x.begin(), x.end(),
        c.begin(), c.end(),
        std::back_inserter(y));

    return y[0];
}

int solve_part2(std::vector<std::string> &rucksacks)
{
    int score{0};

    for (int i{0}; i < rucksacks.size(); i += 3)
    {
        score += priority(find_common_item(rucksacks[i], rucksacks[i+1], rucksacks[i+2]));
    }

    return score;
}

template<>
auto advent2022::day03() -> result
{
    auto input{aoc::read_lines("adventofcode2022/input/day03.txt")};

    return aoc::result(solve_part1(input), solve_part2(input));
}