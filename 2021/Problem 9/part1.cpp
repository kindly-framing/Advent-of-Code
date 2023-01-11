#include "helpers.h"
#include <numeric>

struct Position {
    int r;
    int c;

    Position(int r, int c) : r(r), c(c) {}

    std::vector<Position> neighbors() const
    {
        return {Position(r - 1, c), Position(r + 1, c), Position(r, c + 1),
                Position(r, c - 1)};
    }
};

struct Height_Map {
    std::vector<std::vector<int>> map;

    Height_Map(const std::vector<std::string> lines)
    {
        for (size_t r = 0; r < lines.size(); r++) {
            map.push_back(std::vector<int>());
            for (size_t c = 0; c < lines[r].size(); c++) {
                map[r].push_back(lines[r][c] - '0');
            }
        }
    }

    std::vector<int> get_low_points()
    {
        std::vector<int> low_points;
        for (size_t r = 0; r < map.size(); r++) {
            for (size_t c = 0; c < map[r].size(); c++) {
                if (is_low_point(Position(r, c))) {
                    low_points.push_back(map[r][c]);
                }
            }
        }
        return low_points;
    }

    bool is_low_point(const Position &p)
    {
        for (auto &&neighbor : valid_neighbors(p)) {
            if (value(p) >= value(neighbor)) {
                return false;
            }
        }
        return true;
    }

    int value(const Position &p) { return map[p.r][p.c]; }

    std::vector<Position> valid_neighbors(const Position &p)
    {
        std::vector<Position> neighbors;
        for (auto &&pos : p.neighbors()) {
            if (in_bounds(pos)) {
                neighbors.push_back(pos);
            }
        }
        return neighbors;
    }

    bool in_bounds(const Position &p)
    {
        return p.r >= 0 && p.r < map.size() && p.c >= 0 && p.c < map[0].size();
    }
};

int main()
{
    std::vector<std::string> lines = get_lines("actual.txt");

    Height_Map map(lines);
    std::vector<int> low_points = map.get_low_points();
    std::cout << std::accumulate(low_points.begin(), low_points.end(), 0,
                                 [](int sum, int n) { return sum + n + 1; })
              << '\n';

    return 0;
}