#include "height_map.h"
#include "helpers.h"

std::vector<Position> Position::neighbors() const
{
    return {Position(x - 1, y), Position(x + 1, y), Position(x, y + 1),
            Position(x, y - 1)};
}

bool Position::operator<(const Position &p) const
{
    if (x != p.x) {
        return x < p.x;
    }
    return y < p.y;
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

std::vector<Position> Height_Map::low_point_positions()
{
    // for part 2, it is beneficial to get low point positions rather
    // than their value
    std::vector<Position> low_points;
    for (size_t r = 0; r < map.size(); r++) {
        for (size_t c = 0; c < map[r].size(); c++) {
            Position current = Position(r, c);
            if (is_low_point(current)) {
                low_points.push_back(current);
            }
        }
    }
    return low_points;
}

std::vector<int> Height_Map::get_basin_sizes()
{
    std::vector<int> basin_sizes;

    // BFS for each low point and pushing basin size to vector.
    std::set<Position> visited;
    for (auto &&low_point : low_point_positions()) {
        // using a pair of Positions with their source's value to compare
        std::queue<std::pair<Position, int>> q;
        q.push({low_point, -1});

        // counting all positions that are part of the basin
        int count{};
        while (!q.empty()) {
            std::pair<Position, int> current = q.front();
            q.pop();

            int val = map_value(current.first);
            int prev = current.second;
            if (!visited.count(current.first) && val > prev && val != 9) {
                visited.insert(current.first);
                count++;
                insert_neighbors_in_queue(current.first, q);
            }
        }

        basin_sizes.push_back(count);
    }

    return basin_sizes;
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

void Height_Map::insert_neighbors_in_queue(
    const Position &p, std::queue<std::pair<Position, int>> &q)
{
    int previous = map_value(p);
    for (auto &&neighbor : valid_neighbors(p)) {
        q.push({neighbor, previous});
    }
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
    std::vector<int> basin_counts = map.get_basin_sizes();
    std::sort(basin_counts.begin(), basin_counts.end(), std::greater<int>());
    std::cout << basin_counts[0] * basin_counts[1] * basin_counts[2] << '\n';

    return 0;
}