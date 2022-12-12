#include "aoc.h"

int calculate_score(char opponent_move, char next_move)
{
    const int score_map[3][3] = {
        {4, 8, 3},
        {1, 5, 9},
        {7, 2, 6}
    };

    return score_map[opponent_move - 'A'][next_move - 'A'];
}

char calculate_move(char opponent_move, char round_should_end)
{
    char next_move{};
    switch (round_should_end)
    {
    case 'X':
        next_move = opponent_move - 1;
        break;
    case 'Y':
        next_move = opponent_move;
        break;
    case 'Z':
        next_move = opponent_move + 1;
        break;
    }

    if (next_move < 'A') next_move = 'C';
    else if (next_move > 'C') next_move = 'A';

    return next_move;
}

template<>
auto advent2022::day02() -> result
{
    auto input{aoc::read_lines("adventofcode2022/input/day02.txt")};

    int score_part1{0};
    int score_part2{0};

    for (auto &line : input)
    {
        char opponent_move{ line[0]};
        char second_column{ line[2]};

        char my_move1 = second_column + 'A' - 'X';
        score_part1 += calculate_score(opponent_move, my_move1);

        char my_move2 = calculate_move(opponent_move, second_column);
        score_part2 += calculate_score(opponent_move, my_move2);
    }

    return aoc::result(score_part1, score_part2);
}

