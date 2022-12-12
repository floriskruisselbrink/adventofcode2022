#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include "utils.h"

class PlayingSpace
{
private:
    std::vector<Point> m_knots;
    std::set<Point> m_visited_by_tail;

public:
    PlayingSpace(std::size_t rope_length) : m_knots{rope_length, {0, 0}}, m_visited_by_tail{{0, 0}} {}

    int visited_by_tail() { return m_visited_by_tail.size(); }

    void move(const std::string &instruction);

private:
    void followTail(Point &head, Point &next);
};

const std::map<char, Point> directions{
    {'R', {1, 0}},
    {'L', {-1, 0}},
    {'D', {0, 1}},
    {'U', {0, -1}}};

void PlayingSpace::move(const std::string &instruction)
{
    Point direction = directions.at(instruction[0]);
    int count{std::stoi(instruction.substr(2))};

    for (int i = 0; i < count; i++)
    {
        Point& head{m_knots.front()};
        head += direction;

        for (int j = 1; j < m_knots.size(); j++)
        {
            followTail(m_knots[j-1], m_knots[j]);
        }

        m_visited_by_tail.insert(m_knots.back());
    }
}

void PlayingSpace::followTail(Point &head, Point &next)
{
    int dx{head.x - next.x};
    int dy{head.y - next.y};

    if (std::max(std::abs(dx), std::abs(dy)) == 2)
    {
        next.x += sign(dx);
        next.y += sign(dy);
    }
}

int solve(const std::vector<std::string> &input, std::size_t rope_length)
{
    PlayingSpace playingSpace{rope_length};
    for (auto &instruction : input)
    {
        playingSpace.move(instruction);
    }

    return playingSpace.visited_by_tail();
}

int main()
{
    std::cout << "AOC 2022, Day 9: Rope Bridge\n";

    auto input = read_lines("day09.txt");

    int score_part1{solve(input, 2)};
    std::cout << "Part 1: " << score_part1 << '\n';

    int score_part2{solve(input, 10)};
    std::cout << "Part 2: " << score_part2 << '\n';
    return 0;
}
