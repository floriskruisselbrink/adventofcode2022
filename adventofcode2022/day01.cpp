#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "utils.h"

int main()
{
	std::cout << "AOC 2022, Day 1: Calorie Counting\n";
	Timer timer{};

	std::vector<int> elf_calories{};
	int current_calories{0};

	std::cout << "Reading input... ";
	auto input{read_lines("day01.txt")};
	std::cout << timer << '\n';

	std::cout << "Parsing input... ";
	for (auto &line : input)
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
	std::cout << timer << '\n';

	std::cout << "Sorting results... ";
	std::sort(elf_calories.begin(), elf_calories.end(), std::greater());
	std::cout << timer << '\n';

	std::cout << "Part 1: " << elf_calories[0] << '\n';
	std::cout << "Part 2: " << elf_calories[0] + elf_calories[1] + elf_calories[2] << '\n';
	return 0;
}