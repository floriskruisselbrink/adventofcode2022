#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "utils.h"

int main()
{
	std::cout << "Adventofcode 2022, day 01\n";

	std::vector<int> elf_calories{};
	int current_calories{0};

	for (auto &line : read_lines("day01.txt"))
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

	std::sort(elf_calories.begin(), elf_calories.end(), std::greater());

	std::cout << "Part 1: " << elf_calories[0] << '\n';
	std::cout << "Part 2: " << elf_calories[0] + elf_calories[1] + elf_calories[2] << '\n';
	return 0;
}