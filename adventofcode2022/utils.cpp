#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "utils.h"

std::vector<std::string> split(const std::string &source, const std::string &delimiters)
{
    std::vector<std::string> result;

    int current;
    int next{-1};

    do
    {
        current = next + 1;
        next = source.find_first_of(delimiters, current);
        result.push_back(source.substr(current, next - current));
    } while (next != std::string::npos);

    return result;
}

std::string join(const std::vector<std::string> &strings, const std::string &delimiter)
{
    std::ostringstream result{};
    auto current{strings.begin()};
    auto last{strings.end()};

    if (current != last)
    {
        result << *current;
        while (++current != last)
        {
            result << delimiter << *current;
        }
    }

    return result.str();
}

std::vector<std::string> read_lines(std::istream &input_stream)
{
    std::vector<std::string> lines;

    std::string line;
    while (std::getline(input_stream, line))
    {
        lines.push_back(line);
    }

    return lines;
}

std::vector<std::string> read_lines(std::string_view filename)
{
    std::ifstream input_stream{filename};
    return read_lines(input_stream);
}

std::ostream &operator<<(std::ostream &out, Timer &timer)
{
    out << timer.elapsed() << " seconds elapsed";
    return out;
}
