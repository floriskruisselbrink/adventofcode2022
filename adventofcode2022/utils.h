#ifndef _AOC_UTILS_H
#define _AOC_UTILS_H

#include <fstream>
#include <string_view>
#include <vector>

std::vector<std::string> read_lines(std::istream &input_stream);
std::vector<std::string> read_lines(std::string_view filename);

#endif