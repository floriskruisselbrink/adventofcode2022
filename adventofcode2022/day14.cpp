#include "aoc.h"

namespace day14
{
    constexpr auto filename{"adventofcode2022/input/day14.txt"};
    constexpr auto width{1000};

    constexpr char ROCK = '#';
    constexpr char SAND = 'o';
    constexpr char SAND_SOURCE = '+';

    using aoc::Point;
    using aoc::sign;

    class Grid
    {
    private:
        std::vector<std::array<char, width>> m_grid{};
        int m_min_x{500};
        int m_max_x{500};

    public:
        Grid()
        {
            ensure_height(1);
            m_grid[0][500] = SAND_SOURCE;
        }

        int height() const { return m_grid.size(); }
        void ensure_height(int height_needed)
        {
            if ((height_needed + 1) > height())
            {
                m_grid.resize(height_needed + 1);
            }
        }

        void draw_rocks(Point a, Point b, bool update_minmax = true)
        {
            ensure_height(std::max(a.y, b.y));

            Point current{a};
            Point diff{sign(b.x - a.x), sign(b.y - a.y)};
            while (current != b)
            {
                m_grid[current.y][current.x] = ROCK;
                current += diff;
            }
            m_grid[current.y][current.x] = ROCK;

            if (update_minmax)
            {
                m_min_x = std::min({m_min_x, a.x, b.x});
                m_max_x = std::min({m_max_x, a.x, b.x});
            }
        }

        void draw_floor()
        {
            draw_rocks({0, height()+1}, {999, height()+1}, false);
        }

        char operator[](Point index) const
        {
            return m_grid[index.y][index.x];
        }

        char &operator[](Point index)
        {
            m_min_x = std::min(m_min_x, index.x);
            m_max_x = std::max(m_max_x, index.x);
            return m_grid[index.y][index.x];
        }

        void print_grid()
        {
            for (int y = 0; y < height(); y++)
            {
                for (int x{m_min_x}; x <= m_max_x; x++)
                {
                    std::cout << (m_grid[y][x] ? m_grid[y][x] : '.');
                }
                std::cout << std::endl;
            }
        }
    };

    auto parse_input_line(const std::string &line, Grid &grid)
    {
        std::istringstream ss{line};
        Point start{};
        ss >> start.x;
        ss.ignore(1, ',');
        ss >> start.y;
        ss.ignore(4, '>');

        while (ss)
        {
            Point next{};
            ss >> next.x;
            ss.ignore(1, ',');
            ss >> next.y;
            ss.ignore(4, '>');

            grid.draw_rocks(start, next);
            start = next;
        }
    }

    auto simulate(Grid &grid) -> int
    {
        const Point down{0, 1};
        const Point down_left{-1, 1};
        const Point down_right{1, 1};

        int sand{0};

        Point sand_source{500, 0};
        Point position{sand_source};
        while (position.y < grid.height())
        {
            if (!grid[position + down])
            {
                position += down;
            }
            else if (!grid[position + down_left])
            {
                position += down_left;
            }
            else if (!grid[position + down_right])
            {
                position += down_right;
            }
            else if (position == sand_source)
            {
                sand++;
                break;
            }
            else
            {
                sand++;
                grid[position] = SAND;
                position = sand_source;
            }
        }

        return sand;
    }
}

template <>
auto advent2022::day14() -> result
{
    auto input{aoc::read_lines(day14::filename)};
    day14::Grid grid1{};
    for (const auto &line : input)
    {
        day14::parse_input_line(line, grid1);
    }
    auto grid2{grid1};
    grid2.draw_floor();


    auto part1{day14::simulate(grid1)};
    // grid1.print_grid();
    auto part2{day14::simulate(grid2)};
    // grid2.print_grid();
    return aoc::result(part1, part2);
}