#include <list>
#include <unordered_set>
#include "aoc.h"

namespace day20
{
    const std::string filename{"adventofcode2022/input/day20.txt"};

    using Number = long long;
    using Numbers = std::list<Number>;
    using NumberIterator = Numbers::const_iterator;

    auto read_input() -> Numbers
    {
        std::ifstream input_stream{filename};
        assert(input_stream.is_open());

        Numbers numbers{};
        std::string line;
        while (std::getline(input_stream, line))
        {
            numbers.push_back(std::stoi(line));
        }

        return numbers;
    }

    void print_list(const Numbers &input)
    {
        auto first{true};
        for (const auto &number : input)
        {
            if (!first)
                std::cout << ", ";
            std::cout << number;
            first = false;
        }
        std::cout << std::endl;
    }

    auto shift(const Numbers &list, NumberIterator iterator, Number n) -> NumberIterator
    {
        Number shift_offset{std::abs(n) % static_cast<Number>(list.size())};

        if (n > 0)
        {
            for (auto i = 0; i < shift_offset; i++)
            {
                if (iterator == list.end())
                    iterator = list.begin();
                iterator++;
            }
            if (iterator == list.end())
                iterator = list.begin();
        }
        else if (n < 0)
        {
            for (auto i = 0; i < shift_offset; i++)
            {
                if (iterator == list.begin())
                    iterator = list.end();
                iterator--;
            }
            if (iterator == list.begin())
                iterator = list.end();
        }

        return iterator;
    }

    void mix(Numbers &list, int mixes = 1)
    {
        auto numbers_to_visit{std::vector<NumberIterator>()};
        for (auto it{list.begin()}; it != list.end(); it++)
            numbers_to_visit.push_back(it);

        while (mixes--)
        {
            for (auto &iterator_current : numbers_to_visit)
            {
                auto number = *iterator_current;
                auto destination = shift(list, list.erase(iterator_current), number);
                iterator_current = list.insert(destination, number);
            }
        }
    }

    auto after(const Numbers &list, NumberIterator base, int n) -> Number
    {
        for (Numbers::size_type i = 0; i < (n % list.size()); i++)
        {
            if (++base == list.end())
                base = list.begin();
        }

        return *base;
    }

    auto grove_sum(Numbers list, int mixes, long long decryption_key) -> long long
    {
        for (auto &n : list)
            n *= decryption_key;
        mix(list, mixes);

        auto base{std::find(list.begin(), list.end(), 0)};
        auto x{after(list, base, 1000)};
        auto y{after(list, base, 2000)};
        auto z{after(list, base, 3000)};

        return x + y + z;
    }
}

template <>
auto advent2022::day20() -> result
{
    using namespace day20;

    auto input = read_input();
    auto part1 = grove_sum(input, 1, 1);
    auto part2 = grove_sum(input, 10, 811589153);

    return aoc::result(part1, part2);
}