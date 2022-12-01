#include <string>

#include "utils.h"

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
