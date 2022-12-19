#include <optional>
#include <regex>
#include "aoc.h"

namespace day15
{
#if 0
    const std::string filename{"adventofcode2022/input/day15_test.txt"};
    const int row_to_check{10};
    const std::pair<int, int> search_range{0, 20};
#else
    const std::string filename{"adventofcode2022/input/day15.txt"};
    const int row_to_check{2'000'000};
    const std::pair<int, int> search_range{0, 4'000'000};
#endif

    using aoc::Point;
    using IntRange = std::pair<int, int>;

    struct Sensor
    {
        Point location;
        Point beacon;
        int radius;

        Sensor(Point location, Point closest_beacon) : location{location}, beacon{closest_beacon}, radius{aoc::manhattan_distance(location, closest_beacon)} {}
        Sensor(const std::string &input)
        {
            const std::regex line_format{"^Sensor at x=(-?\\d+), y=(-?\\d+): closest beacon is at x=(-?\\d+), y=(-?\\d+)"};

            std::smatch match_result;
            if (std::regex_match(input, match_result, line_format))
            {
                location = {std::stoi(match_result[1]), std::stoi(match_result[2])};
                beacon = {std::stoi(match_result[3]), std::stoi(match_result[4])};
                radius = aoc::manhattan_distance(location, beacon);
            }
        }

        auto line_at(int y) const -> std::optional<IntRange>
        {
            auto distance{std::abs(location.y - y)};

            if (distance > radius)
                return std::nullopt;

            auto offset = radius - distance;
            return std::make_pair(location.x - offset, location.x + offset);
        }
    };

    using SensorList = std::vector<Sensor>;
    using Beacon = Point;
    using BeaconList = std::set<Beacon>;

    auto parse_input(const std::vector<std::string> &lines) -> SensorList
    {
        std::vector<Sensor> sensor_list{};

        for (const auto &line : lines)
        {
            sensor_list.push_back({line});
        }

        return sensor_list;
    }

    auto find_unique_beacons(const SensorList &sensor_list) -> BeaconList
    {
        BeaconList beacon_list{};

        std::transform(sensor_list.begin(), sensor_list.end(), std::inserter(beacon_list, beacon_list.begin()),
                       [](const Sensor &sensor)
                       { return sensor.beacon; });

        return beacon_list;
    }
    auto find_horizontal_range(const SensorList &sensor_list) -> std::tuple<int, int>
    {
        int min_x{0};
        int max_x{0};
        for (const auto &sensor : sensor_list)
        {
            min_x = std::min(min_x, sensor.location.x - sensor.radius);
            max_x = std::max(max_x, sensor.location.x + sensor.radius);
        }
        return std::make_tuple(min_x, max_x);
    }

    auto find_coverage(const SensorList &sensor_list, int row) -> std::set<IntRange>
    {
        std::set<IntRange> covered_ranges{};
        for (const auto &sensor : sensor_list)
        {
            auto range{sensor.line_at(row)};
            if (range)
                covered_ranges.insert(*range);
        }

        return covered_ranges;
    }

    auto merge_ranges(const std::set<IntRange> &ranges) -> std::set<IntRange>
    {
        std::set<IntRange> merged_ranges{};

        int start{ranges.begin()->first};
        int end{ranges.begin()->second};

        for (const auto &range : ranges)
        {
            // extends current range
            if (range.first <= end + 1 && range.second > end)
            {
                end = range.second;
            }
            // new range
            else if (range.first > end)
            {
                merged_ranges.insert(std::make_pair(start, end));
                start = range.first;
                end = range.second;
            }
        }
        merged_ranges.insert(std::make_pair(start, end));

        return merged_ranges;
    }

    auto count_covered_positions(const SensorList &sensor_list, const BeaconList &beacon_list) -> int
    {
        auto covered_ranges{merge_ranges(find_coverage(sensor_list, row_to_check))};

        int covered_count{0};
        for (const auto &range : covered_ranges)
        {
            covered_count += range.second - range.first;
        }

        auto beacons{
            std::count_if(beacon_list.begin(), beacon_list.end(),
                          [](const Beacon &beacon)
                          { return beacon.y == row_to_check; })};

        return covered_count - beacons;
    }

    auto find_distress_beacon(const SensorList &sensor_list) -> long long
    {
        for (int y = search_range.first; y <= search_range.second; y++)
        {
            auto covered_ranges{merge_ranges(find_coverage(sensor_list, y))};
            if (covered_ranges.size() > 1)
            {
                return 4'000'000L * (covered_ranges.begin()->second + 1) + y;
            }
        }
        return 0;
    }
}

template <>
auto advent2022::day15() -> result
{
    using namespace day15;

    auto input{aoc::read_lines(filename)};
    auto sensors{parse_input(input)};
    auto beacons{find_unique_beacons(sensors)};

    aoc::Timer timer{};

    timer.start("Calculating part 1");
    auto part1{count_covered_positions(sensors, beacons)};
    timer.stop();

    timer.start("Calculating part 2");
    auto part2{find_distress_beacon(sensors)};
    timer.stop();

    return aoc::result(part1, part2);
}