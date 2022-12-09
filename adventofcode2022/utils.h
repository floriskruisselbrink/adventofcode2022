#ifndef _AOC_UTILS_H
#define _AOC_UTILS_H

#include <chrono>
#include <fstream>
#include <iostream>
#include <string_view>
#include <vector>

std::vector<std::string> read_lines(std::istream &input_stream);
std::vector<std::string> read_lines(std::string_view filename);

std::vector<std::string> split(const std::string &source, const std::string &delimiters);

std::string join(const std::vector<std::string> &strings, const std::string &delimiter);

template <typename T>
int sign(T value)
{
    return (T{0} < value) - (value < T{0});
}

class Timer
{
private:
    using Clock = std::chrono::steady_clock;
    using Second = std::chrono::duration<double, std::ratio<1>>;

    bool m_reset_on_read{true};
    std::chrono::time_point<Clock> m_begin{Clock::now()};

public:
    void start(std::string_view message)
    {
        reset();
        std::cout << message << "... ";
    }

    void stop()
    {
        std::cout << elapsed() << " seconds elapsed\n";
    }

    void reset()
    {
        m_begin = Clock::now();
    }

    double elapsed()
    {
        auto result = std::chrono::duration_cast<Second>(Clock::now() - m_begin).count();
        if (m_reset_on_read)
            reset();
        return result;
    }

    friend std::ostream &operator<<(std::ostream &out, Timer &timer);
};

#endif