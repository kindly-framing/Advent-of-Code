#include "helpers.h"
#include <algorithm>
#include <unordered_map>
#include <utility>

using Position = std::pair<int, int>;

struct Line
{
    Position m_start;
    Position m_end;

    Line(std::string str)
    {
        std::string format = "%d,%d -> %d,%d";
        std::sscanf(str.c_str(), format.c_str(), &m_start.first,
                    &m_start.second, &m_end.first, &m_end.second);

        // helpful for converting to positions to have start < end
        if (m_start > m_end)
        {
            std::swap(m_start, m_end);
        }
    }

    std::vector<Position> convert_to_positions()
    {
        // only consider horizontal/vertical positions
        if (m_start.first != m_end.first && m_start.second != m_end.second)
        {
            return {};
        }

        std::vector<Position> positions;

        // increment x1 value to x2 value
        for (int i = m_start.first; i < m_end.first; i++)
        {
            positions.push_back(Position(i, m_end.second));
        }

        // increment y1 value to y2 value
        for (int i = m_start.second; i <= m_end.second; i++)
        {
            positions.push_back(Position(m_end.first, i));
        }

        return positions;
    }
};

struct Vent
{
    std::unordered_map<Position, int, Pair_Hash> m_intersecting;

    Vent(std::vector<std::string> data)
    {
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
            Line current(str);
            std::vector<Position> converted = current.convert_to_positions();

            // this is here specfically since part 1 only considers vertical and
            // horizontal lines, therefore it could lead to runtime errors
            if (converted.empty())
            {
                continue;
            }
            else
            {
                for (Position &p : converted)
                {
                    positions.push_back(p);
                }
            }
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
    std::vector<std::string> lines = get_lines("sample.txt");
    Vent vent(lines);
    std::cout << vent.count(2) << '\n';
    return 0;
}