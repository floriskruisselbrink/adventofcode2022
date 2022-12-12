#include <algorithm>
#include <deque>
#include <iostream>
#include <memory>
#include "aoc.h"

class Operation
{
public:
    virtual ~Operation() {}
    virtual long long execute(long long item) = 0;
};

class OperationAdd : public Operation
{
private:
    int m_parameter;

public:
    OperationAdd(int parameter) : m_parameter{parameter} {}
    long long execute(long long item) override { return item + m_parameter; }
};

class OperationMultiply : public Operation
{
private:
    int m_parameter;

public:
    OperationMultiply(int parameter) : m_parameter{parameter} {}
    long long execute(long long item) override { return item * m_parameter; }
};

class OperationSquared : public Operation
{
public:
    long long execute(long long item) override { return item * item; }
};

class MonkeyBusiness;
class Monkey
{
private:
    Operation *m_operation;
    int m_division_test;
    int m_throw_when_true;
    int m_throw_when_false;
    std::deque<long long> m_items{};

    long long m_inspection_count{0};

public:
    Monkey(Operation *operation, int division_test, int when_true, int when_false, std::deque<long long> items)
        : m_operation{operation}, m_division_test{division_test}, m_throw_when_true{when_true}, m_throw_when_false{when_false}, m_items{items} {}

    void catch_item(long long item)
    {
        m_items.push_back(item);
    }

    auto has_items() const -> bool { return !m_items.empty(); }
    auto inspection_count() const -> long long { return m_inspection_count; }

    auto inspect_next_item(int worry_relief) -> std::tuple<long long, int>
    {
        m_inspection_count++;

        auto item{m_items.front()};
        m_items.pop_front();
        item = m_operation->execute(item) / worry_relief;
        int target = (item % m_division_test) ? m_throw_when_false : m_throw_when_true;

        return std::make_tuple(item, target);
    }
};

class MonkeyBusiness
{
private:
    std::vector<Monkey> m_monkeys;
    int m_worry_relief;
    int m_modulo;

public:
    MonkeyBusiness(std::vector<Monkey> monkeys, int worry_relief, int modulo)
        : m_monkeys{monkeys}, m_worry_relief{worry_relief}, m_modulo{modulo} {}

    void play_round()
    {
        for (std::size_t i{0}; i < m_monkeys.size(); i++)
        {
            play_turn(m_monkeys[i]);
        }
    }

    auto business_level() -> long long
    {
        std::vector<long long> inspection_counts{};

        std::transform(m_monkeys.begin(), m_monkeys.end(), std::back_inserter(inspection_counts),
                       [](const Monkey &m)
                       { return m.inspection_count(); });
        std::sort(inspection_counts.begin(), inspection_counts.end(), std::greater<int>());

        return inspection_counts[0] * inspection_counts[1];
    }

private:
    void play_turn(Monkey &monkey)
    {
        while (monkey.has_items())
        {
            auto [item, target] = monkey.inspect_next_item(m_worry_relief);
            m_monkeys[target].catch_item(item % m_modulo);
        }
    }
};

Operation *create_operation(char op_type, std::string parameter)
{
    if (op_type == '+')
    {
        return new OperationAdd(std::stoi(parameter));
    }
    else if (parameter == "old")
    {
        return new OperationSquared();
    }
    else
    {
        return new OperationMultiply(std::stoi(parameter));
    }
}

std::deque<long long> convert_itemlist(std::vector<std::string> items)
{
    std::deque<long long> result{};
    std::transform(items.begin(), items.end(), std::back_inserter(result),
                   [](const std::string &item)
                   { return std::stoll(item); });
    return result;
}

auto parse_monkeys(const std::vector<std::string> &input, int worry_relief) -> MonkeyBusiness
{
    std::vector<Monkey> monkey_list{};
    int modulo{1};

    std::size_t line{0};
    while (line < input.size())
    {
        // "Monkey x:"
        line++; // skip

        // "  Starting items: a, b, .."
        auto item_list = aoc::split(input[line++].substr(18), ", ");

        // "  Operation: new = old # .."
        auto op_type = input[line][23];
        auto parameter = input[line].substr(25);
        line++;

        // "  Test: divisible by .."
        auto division_test = std::stoi(input[line++].substr(21));

        // "    If true: throw to monkey .."
        auto monkey_true = std::stoi(input[line++].substr(29));

        // "    If false: throw to monkey .."
        auto monkey_false = std::stoi(input[line++].substr(29));

        // (empty line)
        line++;

        monkey_list.push_back({create_operation(op_type, parameter), division_test, monkey_true, monkey_false, convert_itemlist(item_list)});
        modulo *= division_test;
    }
    return MonkeyBusiness{monkey_list, worry_relief, modulo};
}

template <>
auto advent2022::day11() -> result
{
    auto input{aoc::read_lines("adventofcode2022/input/day11.txt")};

    auto monkeyBusiness1{parse_monkeys(input, 3)};
    for (int round{1}; round <= 20; round++)
    {
        monkeyBusiness1.play_round();
    }

    auto monkeyBusiness2{parse_monkeys(input, 1)};
    for (int round(1); round <= 10000; round++)
    {
        monkeyBusiness2.play_round();
    }

    return aoc::result(monkeyBusiness1.business_level(), monkeyBusiness2.business_level());
}