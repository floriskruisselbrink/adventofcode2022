#ifndef __AOC_H_
#define __AOC_H_

#include <array>
#include <fstream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

template <int YEAR>
struct advent
{
    static constexpr int year = YEAR;
    using result = std::tuple<std::string, std::string>;

    auto operator()(int day) const -> result
    {
        assert(day >= 1 && day <= 25);
        return days[day - 1]();
    }

    static auto day01() -> result;
    static auto day02() -> result;
    static auto day03() -> result;
    static auto day04() -> result;
    static auto day05() -> result;
    static auto day06() -> result;
    static auto day07() -> result;
    static auto day08() -> result;
    static auto day09() -> result;
    static auto day10() -> result;
    static auto day11() -> result;
    static auto day12() -> result;
    static auto day13() -> result;
    static auto day14() -> result;
    static auto day15() -> result;
    static auto day16() -> result;
    static auto day17() -> result;
    static auto day18() -> result;
    static auto day19() -> result;
    static auto day20() -> result;
    static auto day21() -> result;
    static auto day22() -> result;
    static auto day23() -> result;
    static auto day24() -> result;
    static auto day25() -> result;

private:
    static constexpr std::array<result (*)(), 25> days = {
        // NOLINT
        &advent<year>::day01,
        &advent<year>::day02,
        &advent<year>::day03,
        &advent<year>::day04,
        &advent<year>::day05,
        &advent<year>::day06,
        &advent<year>::day07,
        &advent<year>::day08,
        &advent<year>::day09,
        &advent<year>::day10,
        &advent<year>::day11,
        &advent<year>::day12,
        &advent<year>::day13,
        &advent<year>::day14,
        &advent<year>::day15,
        &advent<year>::day16,
        &advent<year>::day17,
        &advent<year>::day18,
        &advent<year>::day19,
        &advent<year>::day20,
        &advent<year>::day21,
        &advent<year>::day22,
        &advent<year>::day23,
        &advent<year>::day24,
        &advent<year>::day25,
    };
};

using advent2022 = advent<2022>;

namespace aoc
{
    template <typename T>
    auto inline to_string(T value) -> std::string
    {
        std::stringstream ss{};
        ss << value;
        return ss.str();
    }

    template <typename T1, typename T2>
    auto result(T1 t1, T2 t2) -> std::tuple<std::string, std::string>
    {
        return std::tuple{to_string(t1), to_string(t2)};
    }

    auto inline read_lines(std::istream &input_stream) -> std::vector<std::string>
    {
        std::vector<std::string> lines{};

        std::string line;
        while (std::getline(input_stream, line))
        {
            lines.push_back(line);
        }

        return lines;
    }

    auto inline read_lines(std::string_view filename) -> std::vector<std::string>
    {
        std::ifstream input_stream{filename};
        if (input_stream.is_open())
        {
            return read_lines(input_stream);
        }
        throw std::runtime_error("Could not open file");
    }

    auto inline split(const std::string &source, const std::string &delimiters) -> std::vector<std::string>
    {
        std::vector<std::string> result;

        std::string::size_type current{0};
        std::string::size_type next{0};
        do
        {
            next = source.find_first_of(delimiters, current);
            result.push_back(source.substr(current, next - current));
            current = next + delimiters.size();
        } while (next != std::string::npos);

        return result;
    }

    template <class InputIt>
    auto inline join(InputIt first, InputIt last, const std::string &delimiter)
    {
        std::ostringstream result{};
        auto current{first};

        if (current != last)
        {
            result << *current;
            while (++current != last) { result << delimiter << *current; }
        }

        return result.str();
    }

    template <typename T>
    int sign(T value)
    {
        return (T{0} < value) - (value < T{0});
    }

    struct Point
    {
        int x{};
        int y{};

        friend bool operator<(const Point &a, const Point &b)
        {
            return std::tie(a.x, a.y) < std::tie(b.x, b.y);
        }

        friend bool operator==(const Point &a, const Point &b)
        {
            return (a.x == b.x) && (a.y == b.y);
        }

        Point &operator+=(const Point &b)
        {
            x += b.x;
            y += b.y;
            return *this;
        }

        friend Point operator+(Point a, const Point &b)
        {
            a += b;
            return a;
        }
    };

} // namespace aoc

#endif