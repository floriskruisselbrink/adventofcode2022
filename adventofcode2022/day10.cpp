#include <iostream>
#include "aoc.h"

class CpuState
{
public:
    int x{1};
    int cycle{1};
    int column{0};

    int signal_strength{0};

    void noop()
    {
        next_cycle();
    }

    void addx(int value)
    {
        next_cycle();
        next_cycle();
        x += value;
    }

private:
    void next_cycle()
    {
        std::cout << current_pixel();

        if (((cycle - 20) % 40) == 0)
        {
            signal_strength += cycle * x;
        }
        column++;
        cycle++;

        if (column >= 40)
        {
            column = 0;
            std::cout << std::endl;
        }
    }

    char current_pixel()
    {
        if (column == x || column == (x - 1) || column == (x + 1))
            return '#';
        else
            return '.';
    }
};

CpuState run(const std::vector<std::string> &input)
{
    CpuState state{};

    for (auto &line : input)
    {
        if (line == "noop")
        {
            state.noop();
        }
        else
        {
            auto value = std::stoi(line.substr(5));
            state.addx(value);
        }
    }

    return state;
}

template<>
auto advent2022::day10() -> result
{
    auto input = aoc::read_lines("adventofcode2022/input/day10.txt");
    auto result = run(input);

    return aoc::result(result.signal_strength, "(see above)");
}