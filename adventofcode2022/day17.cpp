#include <bitset>
#include "aoc.h"

namespace day17
{
    const std::string filename{"adventofcode2022/input/day17.txt"};

    using aoc::Point;

    using Row = std::bitset<7>;
    using PlayingField = std::vector<Row>;
    using Shape = std::set<Point>;

    const static auto shapes = std::array<Shape, 5>{{
        // ####
        {Point{3, 3}, Point{4, 3}, Point{5, 3}, Point{6, 3}},

        // .#.
        // ###
        // .#.
        {Point{4, 5}, Point{3, 4}, Point{4, 4}, Point{5, 4}, Point{4, 3}},

        // ..#
        // ..#
        // ###
        {Point{5, 5}, Point{5, 4}, Point{3, 3}, Point{4, 3}, Point{5, 3}},

        // #
        // #
        // #
        // #
        {Point{3, 6}, Point{3, 5}, Point{3, 4}, Point{3, 3}},

        // ##
        // ##
        {Point{3, 4}, Point{4, 4}, Point{3, 3}, Point{4, 3}},
    }};

    auto operator+(const Shape &shape, Point diff) -> Shape
    {
        Shape new_shape{};
        for (const auto &p : shape)
        {
            new_shape.insert(p + diff);
        }
        return new_shape;
    }

    auto blow(const Shape &shape, char movement) -> Shape
    {
        Point diff{movement == '<' ? Point{-1, 0} : Point{1, 0}};
        return shape + diff;
    }

    auto fits(const Shape &shape, const PlayingField &playing_field) -> bool
    {
        for (const auto &p : shape)
        {
            if ((p.x < 1) || (p.x > 7)) // too far left or right
                return false;
            if (p.y < 0) // below floor
                return false;
            if (p.y < playing_field.size())
            {
                if (playing_field[p.y].test(p.x - 1))
                    return false; // collission with already settled rock
            }
        }

        return true; // no collisions found
    }

    auto settle(const Shape &shape, PlayingField &playing_field)
    {
        for (const auto &p : shape)
        {
            while (playing_field.size() <= p.y)
                playing_field.push_back({});

            playing_field[p.y].set(p.x - 1);
        }
    }

    auto play(const std::string &wind_movements) -> std::tuple<int, long long>
    {
        PlayingField playing_field{};
        PlayingField duplicate_playing_field{};

        auto height_part1{0};

        const auto max_detector_windowsize{10'000};
        const auto max_pieces_dropped{1'000'000'000'000};
        auto detected_cycle{0L};
        auto detected_cycle_mod{0L};
        auto delta_steps{0L};
        auto delta_size1{0L};
        auto delta_size2{0L};

        std::size_t wind_index{0};
        std::size_t shape_index{0};
        auto pieces_dropped{0};

        while (pieces_dropped < (3 * max_detector_windowsize))
        {
            if (pieces_dropped == 2022)
            {
                height_part1 = playing_field.size();
            }
            else if (pieces_dropped == (2 * max_detector_windowsize))
            {
                duplicate_playing_field = playing_field;
            }
            else if ((!detected_cycle) && (pieces_dropped > (2 * max_detector_windowsize)))
            {
                if (std::memcmp(
                        &playing_field[playing_field.size() - max_detector_windowsize],
                        &duplicate_playing_field[duplicate_playing_field.size() - max_detector_windowsize],
                        max_detector_windowsize * sizeof(Row)) == 0)
                {
                    detected_cycle = pieces_dropped - (2 * max_detector_windowsize);
                    detected_cycle_mod = max_pieces_dropped % detected_cycle;
                }
            }
            else if (detected_cycle && (!delta_size1) && ((pieces_dropped % detected_cycle) == detected_cycle_mod))
            {
                delta_size1 = playing_field.size();
            }
            else if (detected_cycle && delta_size1 && (!delta_steps) && ((pieces_dropped % detected_cycle) == detected_cycle_mod))
            {
                delta_steps = pieces_dropped;
                delta_size2 = playing_field.size();
                break; // we have everything we need
            }

            auto current_shape = shapes[shape_index] + Point{0, static_cast<int>(playing_field.size())};

            // Move one shape until it is settled
            while (true)
            {
                auto blown_shape = blow(current_shape, wind_movements[wind_index]);
                auto bound_shape = fits(blown_shape, playing_field) ? blown_shape : current_shape;
                auto dropped_shape = bound_shape + Point{0, -1};

                if (++wind_index >= wind_movements.size())
                    wind_index = 0;

                if (fits(dropped_shape, playing_field))
                {
                    current_shape = dropped_shape;
                }
                else
                {
                    settle(bound_shape, playing_field);
                    break;
                }
            }

            if (++shape_index >= shapes.size())
                shape_index = 0;

            pieces_dropped++;
        }

        return std::make_tuple(
            height_part1,
            (((max_pieces_dropped - delta_steps) / detected_cycle) * (delta_size2 - delta_size1)) + delta_size2);
    }
}

template <>
auto advent2022::day17() -> result
{
    using namespace day17;

    auto input = aoc::read_lines(filename);
    auto [part1, part2] = play(input[0]);

    return aoc::result(part1, part2);
}