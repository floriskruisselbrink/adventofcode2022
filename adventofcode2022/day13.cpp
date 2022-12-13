#include <memory>
#include <numeric>
#include <optional>
#include "aoc.h"

// #define VERBOSE

class Packet;
using PacketRef = std::shared_ptr<Packet>;
using PacketRefList = std::vector<PacketRef>;

class Packet
{
private:
    std::optional<int> m_value{std::nullopt};

public:
    PacketRefList packet_list{};

    Packet() {}

    Packet(const std::string &source)
    {
        std::size_t pos{0};
        // skip outer list [ ]
        parse(source.substr(1, source.size() - 2), pos);
    }

    bool has_value() const { return m_value.has_value(); }
    int value() const { return *m_value; }

    void change_to_list()
    {
        auto val = *m_value;
        m_value = std::nullopt;
        auto next = std::make_shared<Packet>();
        next->m_value = val;
        packet_list.push_back(next);
    }

    void parse(const std::string &source, std::size_t &pos)
    {
        while (pos < source.size())
        {
            if (source[pos] == '[')
            {
                pos++;
                auto next = std::make_shared<Packet>();
                packet_list.push_back(next);
                next->parse(source, pos);
            }
            else if (source[pos] == ']')
            {
                pos++;
                break;
            }
            else if (source[pos] == ',')
            {
                pos++;
            }
            else
            {
                auto next = std::make_shared<Packet>();
                auto start = pos;
                while (std::isdigit(source[pos]))
                {
                    pos++;
                }
                next->m_value = std::stoi(source.substr(start, pos - start));
                packet_list.push_back(next);
            }
        }
    }

    friend std::ostream &operator<<(std::ostream &out, const Packet &packet)
    {
        if (packet.has_value())
        {
            out << packet.value();
        }
        else
        {
            out << '[';
            for (std::size_t i{0}; i < packet.packet_list.size(); i++)
            {
                if (i > 0)
                    out << ',';
                out << *(packet.packet_list[i]);
            }
            out << ']';
        }
        return out;
    }
};

auto read_packets(const std::string &filename) -> std::vector<Packet>
{
    auto lines = aoc::read_lines(filename);

    std::vector<Packet> packets{};
    for (auto &line : lines)
    {
        if (line.empty())
            continue;
        packets.push_back({line});
    }

    return packets;
}

void inline log(int depth, const std::string &message)
{
#ifdef VERBOSE
    std::cout << std::string(depth * 2, ' ') << message << std::endl;
#endif
}

auto compare(Packet &left, Packet &right, std::size_t depth = 0) -> std::optional<bool>
{
#ifdef VERBOSE
    std::cout << std::string(depth * 2, ' ') << "- Compare " << left << " vs " << right << std::endl;
#endif

    if (left.has_value() && right.has_value())
    {
        if (left.value() < right.value())
        {
            log(depth + 1, "- Left side is smaller, so inputs are in the right order");
            return true;
        }
        else if (left.value() > right.value())
        {
            log(depth + 1, "- Right side is smaller, so inputs are NOT in the right order");
            return false;
        }
    }
    else if (!left.has_value() && !right.has_value())
    {
        for (std::size_t i{0}; i < left.packet_list.size(); i++)
        {
            if (i < right.packet_list.size())
            {
                if (auto cmp = compare(*left.packet_list[i], *right.packet_list[i], depth + 1); cmp.has_value())
                {
                    return *cmp;
                }
            }
            else
            {
                log(depth + 1, "- Right side ran out of items, so inputs are NOT in the right order");
                return false;
            }
        }

        if (left.packet_list.size() < right.packet_list.size())
        {
            log(depth + 1, "- Left side ran out of items, so inputs are in the right order");
            return true;
        }
    }
    else if (!left.has_value() && right.has_value())
    {
        log(depth + 1, "- Mixed types");
        right.change_to_list();
        if (auto cmp = compare(left, right, depth + 1); cmp.has_value())
        {
            return *cmp;
        }
    }
    else if (left.has_value() && !right.has_value())
    {
        log(depth + 1, "- Mixed types");
        left.change_to_list();
        if (auto cmp = compare(left, right, depth + 1); cmp.has_value())
        {
            return *cmp;
        }
    }

    // Undecided yet...
    return {};
}

auto part1(std::vector<Packet> &packets) -> int
{
    int count{0};

    for (std::size_t i{0}; i < packets.size(); i += 2)
    {
        std::size_t pair{(i / 2) + 1};
#ifdef VERBOSE
        std::cout << "== Pair " << pair << " ==" << std::endl;
#endif
        auto cmp = compare(packets[i], packets[i + 1]);
        assert(cmp.has_value());
        if (*cmp)
            count += pair;
    }
    return count;
}

auto part2(std::vector<Packet> &packets) -> int
{
    // insert marker packets
    auto marker1{packets.emplace_back(Packet{"[[2]]"})};
    auto marker2{packets.emplace_back(Packet{"[[6]]"})};

    // sort the packets
    std::vector<std::size_t> indexes(packets.size());
    std::iota(indexes.begin(), indexes.end(), 0);
    std::sort(indexes.begin(), indexes.end(),
              [&packets](auto left, auto right)
              { return *compare(packets[left], packets[right]); });

    // find the markers
    auto index1 = std::find(indexes.cbegin(), indexes.cend(), packets.size() - 2) - indexes.cbegin() + 1;
    auto index2 = std::find(indexes.cbegin(), indexes.cend(), packets.size() - 1) - indexes.cbegin() + 1;

    return index1 * index2;
}

template <>
auto advent2022::day13() -> result
{
    auto packets = read_packets("adventofcode2022/input/day13.txt");

    return aoc::result(part1(packets), part2(packets));
}
