#include "aoc.h"

namespace day18
{
    const std::string filename{"adventofcode2022/input/day18.txt"};

    using Point3D = std::array<int, 3>;

    const static auto side_positions = std::array<Point3D, 6>{{
        {1, 1, 0}, // front
        {1, 1, 2}, // back
        {0, 1, 1}, // left
        {2, 1, 1}, // right
        {1, 2, 1}, // top
        {1, 0, 1}, // bottom
    }};

    auto parse_input(const std::vector<std::string> &input) -> std::vector<Point3D>
    {
        std::vector<Point3D> cubes{};

        for (const auto &line : input)
        {
            auto parts = aoc::split(line, ",");
            cubes.push_back({std::stoi(parts[0]),
                             std::stoi(parts[1]),
                             std::stoi(parts[2])});
        }

        return cubes;
    }

    auto calculate_surface_area(const std::vector<Point3D> &cubes) -> int
    {
        std::set<Point3D> sides{};
        auto outside_sides{0};

        for (const auto &cube : cubes)
        {
            auto [x, y, z] = cube;

            for (const auto &side : side_positions)
            {
                auto [_, inserted] = sides.insert({x * 2 + side[0], y * 2 + side[1], z * 2 + side[2]});
                if (inserted)
                    outside_sides++;
                else
                    outside_sides--;
            }
        }

        return outside_sides;
    }
}

template <>
auto advent2022::day18() -> result
{
    using namespace day18;

    auto input = aoc::read_lines(filename);
    auto cubes = parse_input(input);

    return aoc::result(calculate_surface_area(cubes), 0);
}