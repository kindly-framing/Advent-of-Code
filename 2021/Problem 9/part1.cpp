#include "height_map.h"
#include "helpers.h"
#include <numeric>

std::vector<Position> Position::neighbors() const
{
    return {Position(x - 1, y), Position(x + 1, y), Position(x, y + 1),
            Position(x, y - 1)};
}

Height_Map::Height_Map(std::vector<std::string> lines)
{
    for (size_t r = 0; r < lines.size(); r++) {
        map.push_back(std::vector<int>());
        for (size_t c = 0; c < lines[r].size(); c++) {
            map[r].push_back(lines[r][c] - '0');
        }
    }
    assert(!map.empty());
}

std::vector<int> Height_Map::low_point_values()
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

bool Height_Map::is_low_point(const Position &p) const
{
    for (auto &&neighbor : valid_neighbors(p)) {
        if (map_value(p) >= map_value(neighbor)) {
            return false;
        }
    }
    return true;
}

std::vector<Position> Height_Map::valid_neighbors(const Position &p) const
{
    std::vector<Position> neighbors;
    for (auto &&pos : p.neighbors()) {
        if (in_bounds(pos)) {
            neighbors.push_back(pos);
        }
    }
    return neighbors;
}

int Height_Map::map_value(const Position &p) const { return map[p.x][p.y]; }

bool Height_Map::in_bounds(const Position &p) const
{
    return p.x >= 0 && p.x < map.size() && p.y >= 0 && p.y < map[0].size();
}

int main()
{
    std::vector<std::string> lines = get_lines("sample.txt");

    Height_Map map(lines);
    std::vector<int> low_points = map.low_point_values();
    std::cout << std::accumulate(low_points.begin(), low_points.end(), 0,
                                 [](int sum, int n) { return sum + n + 1; })
              << '\n';

    return 0;
}