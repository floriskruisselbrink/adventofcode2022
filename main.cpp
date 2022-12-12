#include <ctime>
#include <iostream>
#include "aoc.h"

template <int YEAR>
void print_results(advent<YEAR> adv, int last_day=25)
{
    std::cout << "=== Advent of Code " << YEAR << " ===" << std::endl;

    for (auto day = 1; day <= last_day; day++)
    {
        auto [part1, part2] = adv(day);
        std::cout << " Day " << std::setw(2) << day
                  << ": " << std::setw(20) << part1
                  << " / " << std::setw(20) << part2 << std::endl;
    }
}

int today()
{
    time_t now = time(NULL);
    std::tm *tm = localtime(&now);

    return tm->tm_mday;
}

int main()
{
    constexpr int year{2022};
    int day = today();

#if 1
    print_results(advent<year>{}, day);
#else

    std::cout << "Advent of Code " << year << ", Day " << day << std::endl;

    auto [part1, part2] = advent<year>{}(day);
    std::cout << "Part 1: " << part1 << std::endl;
    std::cout << "Part 2: " << part2 << std::endl;
#endif
    return EXIT_SUCCESS;
}