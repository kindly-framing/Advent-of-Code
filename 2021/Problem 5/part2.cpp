#include "helpers.h"
#include <algorithm>
#include <cassert>
#include <regex>
#include <unordered_map>
#include <utility>

using Position = std::pair<int, int>;

struct Line
{
    Position m_start;
    Position m_end;

    // constructs a Line from a string formatted "x1,x2 -> y1,y2".
    Line(std::string str)
    {
        m_start = {-1, -1};
        m_end = {-1, -1};

        std::string format = "%d,%d -> %d,%d";
        std::sscanf(str.c_str(), format.c_str(), &m_start.first,
                    &m_start.second, &m_end.first, &m_end.second);

        if (m_start.first == -1 || m_start.second == -1 || m_end.first == -1 ||
            m_end.second == -1)
        {
            throw std::invalid_argument("Can't construct from string: " + str);
        }

        // helps internally for getting a vector of positions from line
        if (m_start > m_end)
        {
            std::swap(m_start, m_end);
        }
    }

    std::vector<Position> convert_to_positions()
    {
        if (m_start.first != m_end.first && m_start.second != m_end.second)
        {
            return diagonal_to_positions();
        }
        if (m_start.first < m_end.first)
        {
            return horizontal_to_positions();
        }
        return vertical_to_positions();
    }

    std::vector<Position> horizontal_to_positions()
    {
        std::vector<Position> positions;
        for (int i = m_start.first; i <= m_end.first; i++)
        {
            positions.push_back(Position(i, m_end.second));
        }
        return positions;
    }

    std::vector<Position> vertical_to_positions()
    {
        std::vector<Position> positions;
        for (int i = m_start.second; i <= m_end.second; i++)
        {
            positions.push_back(Position(m_end.first, i));
        }
        return positions;
    }

    std::vector<Position> diagonal_to_positions()
    {
        std::vector<Position> positions;

        int x_step = (m_end.first - m_start.first > 0) ? 1 : -1;
        int y_step = (m_end.second - m_start.second > 0) ? 1 : -1;
        Position p(m_start);
        while (p <= m_end)
        {
            positions.push_back(p);
            p.first += x_step;
            p.second += y_step;
        }

        return positions;
    }
};

struct Vent
{
    std::unordered_map<Position, int, Pair_Hash> m_intersecting;

    Vent(std::vector<std::string> data)
    {
        if (data.empty())
        {
            throw std::invalid_argument(
                "There is no data to construct Vent!\n");
        }

        for (Position &p : extract_positions(data))
        {
            m_intersecting[p]++;
        }
    }

    std::vector<Position>
    extract_positions(const std::vector<std::string> &data)
    {
        std::vector<Position> positions;
        for (std::string str : data)
        {
            std::vector<Position> current = Line(str).convert_to_positions();
            positions.insert(positions.end(), current.begin(), current.end());
        }
        return positions;
    }

    int count(const int &n)
    {
        return std::count_if(m_intersecting.begin(), m_intersecting.end(),
                             [&](auto elem) { return elem.second >= n; });
    }
};

int main()
{
    std::vector<std::string> lines = get_lines("actual.txt");
    Vent vent(lines);
    std::cout << std::boolalpha << (vent.count(2) == 18442) << '\n';
    return 0;
}