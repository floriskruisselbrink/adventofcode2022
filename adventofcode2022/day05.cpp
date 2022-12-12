#include "aoc.h"

using Stack = std::vector<char>;

struct Instruction
{
    int count{};
    int from{};
    int to{};
};

std::vector<Stack> read_stacks(std::istream &input_stream, std::size_t nr_stacks)
{
    std::vector<Stack> stacks{nr_stacks};
    while (true)
    {
        std::string line;
        std::getline(input_stream, line);

        if (std::isdigit(line[1]))
            break;

        for (int index{0}, char_index{1}; index < stacks.size(); index++, char_index = index * 4 + 1)
        {
            if (char_index >= line.length())
                continue;

            if (isupper(line[char_index]))
            {
                stacks[index].push_back(line[char_index]);
            }
        }
    }

    for (auto &stack : stacks)
    {
        std::reverse(stack.begin(), stack.end());
    }

    return stacks;
}

std::vector<Instruction> read_instructions(std::istream &input_stream)
{
    std::vector<Instruction> instructions;

    std::string line;
    while (std::getline(input_stream, line))
    {
        if (!line.starts_with("move "))
            continue;

        auto tokens = aoc::split(line, " ");

        instructions.push_back(Instruction{std::stoi(tokens[1]), std::stoi(tokens[3]) - 1, std::stoi(tokens[5]) - 1});
    }

    return instructions;
}

void move_part1(Stack &from, Stack &to, int count)
{
    to.insert(to.end(), from.rbegin(), from.rbegin() + count);
    from.resize(from.size() - count);
}

void move_part2(Stack &from, Stack &to, int count)
{
    to.insert(to.end(), from.end() - count, from.end());
    from.resize(from.size() - count);
}

std::string solve(const std::vector<Stack> &starting_stacks, const std::vector<Instruction> &instructions, void (*move_function)(Stack &, Stack &, int))
{
    auto stacks{starting_stacks};

    for (auto &instruction : instructions)
    {
        move_function(stacks[instruction.from], stacks[instruction.to], instruction.count);
    }

    std::string result{};
    for (auto &stack : stacks)
    {
        result.push_back(stack.back());
    }

    return result;
}

template <>
auto advent2022::day05() -> result
{
    std::ifstream input_stream{"adventofcode2022/input/day05.txt"};
    auto stacks{read_stacks(input_stream, 9)};
    auto instructions{read_instructions(input_stream)};

    std::string score_part1{solve(stacks, instructions, move_part1)};
    std::string score_part2{solve(stacks, instructions, move_part2)};

    return aoc::result(score_part1, score_part2);
}