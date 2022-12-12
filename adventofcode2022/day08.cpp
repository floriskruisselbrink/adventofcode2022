#include "aoc.h"

class Grid
{
private:
    std::vector<std::string> grid;
    std::size_t grid_size;

public:
    Grid(const std::vector<std::string> &input) : grid{input}, grid_size{input[0].size()} {}
    std::size_t size() const { return grid_size; }
    bool is_visible(int x, int y) const;
    int scenic_score(int x, int y) const;
};

const std::vector<std::tuple<int, int>> directions{
    {1, 0},  // right
    {-1, 0}, // left
    {0, 1},  // down
    {0, -1}, // up
};

bool Grid::is_visible(int x, int y) const
{
    char current_tree{grid[x][y]};
    for (auto [dx, dy] : directions)
    {
        int current_x{x};
        int current_y{y};
        while (true)
        {
            current_x += dx;
            current_y += dy;

            // reached edge of grid: tree is visible
            if (current_x == -1 || current_x == grid_size || current_y == -1 || current_y == grid_size)
                return true;

            // stop looking if we found a tree of equal height or higher
            if (grid[current_x][current_y] >= current_tree)
                break;
        }
    }

    // A tree is invisible if in ALL directions there is at least ONE tree higher or of equal height
    // A tree is visible if in ANY direction ALL trees are smaller

    return false;
}

int Grid::scenic_score(int x, int y) const
{
    char current_tree{grid[x][y]};
    int score{1};

    for (auto [dx, dy] : directions)
    {
        int current_x{x};
        int current_y{y};
        int viewing_distance{0};
        while (true)
        {
            current_x += dx;
            current_y += dy;

            // reached edge of grid: no more trees to see
            if (current_x == -1 || current_x == grid_size || current_y == -1 || current_y == grid_size)
                break;

            viewing_distance++;

            // we can't see past a tree of equal height or higher
            if (grid[current_x][current_y] >= current_tree)
                break;
        }

        score *= viewing_distance;
    }
    return score;
}

int count_visible_trees(const Grid &grid)
{
    int visible_count{0};

    for (int x = 0; x < grid.size(); x++)
    {
        for (int y = 0; y < grid.size(); y++)
        {
            if (grid.is_visible(x, y))
            {
                visible_count++;
            }
        }
    }

    return visible_count;
}

int find_most_scenic_tree(const Grid &grid)
{
    int highest_scenic_score{0};

    for (int x = 1; x < grid.size() - 1; x++)
    {
        for (int y = 1; y < grid.size() - 1; y++)
        {
            highest_scenic_score = std::max(highest_scenic_score, grid.scenic_score(x, y));
        }
    }
    return highest_scenic_score;
}

template<>
auto advent2022::day08() -> result
{
    Grid grid = aoc::read_lines("adventofcode2022/input/day08.txt");

    int score_part1{count_visible_trees(grid)};
    int score_part2{find_most_scenic_tree(grid)};

    return aoc::result(score_part1, score_part2);
}