#include <array>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <string>
#include <tuple>
#include "utils.h"

constexpr auto filename{"day12.txt"};
constexpr auto width{67};
constexpr auto height{41};

using Grid = std::array<std::array<int, height>, width>;

bool in_bounds(Point point)
{
    return (point.x >= 0) && (point.y >= 0) && (point.x < width) && (point.y < height);
}

bool possible_move(const Grid &map, Point from, Point to)
{
    return map[from.x][from.y] <= (map[to.x][to.y] + 1);
}

const Point directions[]{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

auto parse_input(const std::vector<std::string> &input) -> std::tuple<Grid, Point, Point>
{
    Grid heightmap{};
    Point start{};
    Point finish{};

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            switch (input[y][x])
            {
            case 'S':
                start = {x, y};
                heightmap[x][y] = 0;
                break;
            case 'E':
                finish = {x, y};
                heightmap[x][y] = 25;
                break;
            default:
                heightmap[x][y] = input[y][x] - 'a';
                break;
            }
        }
    }
    return std::make_tuple(heightmap, start, finish);
}

Grid find_shortest_path(const Grid &heightmap, Point start)
{
    Grid distance;
    std::set<Point> visited{};

    auto priority = [&distance](Point a, Point b)
    { return distance[a.x][a.y] > distance[b.x][b.y]; };

    std::priority_queue<Point, std::vector<Point>, decltype(priority)> queue{priority};

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            distance[x][y] = std::numeric_limits<int>::max();
        }
    }

    distance[start.x][start.y] = 0;
    visited.insert(start);
    queue.push(start);

    while (!queue.empty())
    {
        Point current{queue.top()};
        queue.pop();

        visited.insert(current);

        for (auto &direction : directions)
        {
            Point neighbour = current + direction;
            if (!visited.contains(neighbour) && in_bounds(neighbour) && possible_move(heightmap, current, neighbour))
            {
                int newDistance = distance[current.x][current.y] + 1;
                if (newDistance < distance[neighbour.x][neighbour.y])
                {
                    distance[neighbour.x][neighbour.y] = newDistance;
                    queue.push(neighbour);
                }
            }
        }
    }

    return distance;
}

int find_best_starting_position(const Grid &heightmap, const Grid &distances)
{
    int best_distance{std::numeric_limits<int>::max()};

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            if (heightmap[x][y] == 0 && distances[x][y] < best_distance)
            {
                best_distance = distances[x][y];
            }
        }
    }

    return best_distance;
}

int main()
{
    std::cout << "AOC 2022, Day 12: Hill Climbing Algorithm\n";

    auto input{read_lines(filename)};
    auto [heightmap, start, top]{parse_input(input)};
    auto distances{find_shortest_path(heightmap, top)};

    std::cout << "Part 1: " << distances[start.x][start.y] << '\n';
    std::cout << "Part 2: " << find_best_starting_position(heightmap, distances) << '\n';
    return 0;
}