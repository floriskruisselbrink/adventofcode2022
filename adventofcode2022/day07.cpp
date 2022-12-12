#include <filesystem>
#include <map>
#include "aoc.h"

namespace fs = std::filesystem;

std::map<fs::path, int> calculate_directory_sizes(const std::vector<std::string> &input)
{
    std::map<fs::path, int> directory_map{};

    fs::path root_path{"/"};
    fs::path current_path = root_path;

    for (auto &line : input)
    {
        auto tokens = aoc::split(line, " ");

        if (tokens[1] == "cd")
        {
            if (tokens[2] == "/")
            {
                current_path = root_path;
            }
            else if (tokens[2] == "..")
            {
                current_path = current_path.parent_path();
            }
            else
            {
                current_path = current_path / tokens[2];
            }
        }
        else if (isdigit(tokens[0][0]))
        {
            int size = std::stoi(tokens[0]);

            fs::path parent_path{current_path};
            while (parent_path != root_path)
            {
                directory_map[parent_path] += size;
                parent_path = parent_path.parent_path();
            }
            directory_map[root_path] += size;
        }
    }

    return directory_map;
}

int sum_directories_smaller_than(int max_size, const std::map<fs::path, int> &directory_sizes)
{
    int total_size{0};

    for (auto &[directory, size] : directory_sizes)
    {
        if (size < max_size)
            total_size += size;
    }

    return total_size;
}

int find_smallest_over(int min_size, const std::map<fs::path, int> &directory_sizes)
{
    int smallest{std::numeric_limits<int>::max()};

    for (auto &[directory, size] : directory_sizes)
    {
        if (size > min_size && size < smallest)
            smallest = size;
    }

    return smallest;
}

template<>
auto advent2022::day07() -> result
{
    auto input = aoc::read_lines("adventofcode2022/input/day07.txt");
    auto directory_sizes = calculate_directory_sizes(input);

    int score_part1{sum_directories_smaller_than(100000, directory_sizes)};

    const int total_space{70000000};
    const int update_space{30000000};
    int unused_space{total_space - directory_sizes["/"]};
    int needed_space{update_space - unused_space};
    int score_part2{find_smallest_over(needed_space, directory_sizes)};

    return aoc::result(score_part1, score_part2);
}