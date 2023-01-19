#ifndef RESERVOIR_H
#define RESERVOIR_H

#include <sstream>
#include <string>
#include <utility>
#include <vector>

using Position = std::pair<int, int>;

struct Line {
    Position start;
    Position end;

    Line(Position a, Position b) : start(a), end(b)
    {
        if (start > end) {
            std::swap(start, end);
        }
    }

    std::vector<Position> convert_to_positions()
    {
        if (start.first != end.first) {
            return horizontal_to_positions();
        }
        return vertical_to_positions();
    }

    std::vector<Position> horizontal_to_positions()
    {
        std::vector<Position> positions;
        for (int i = start.first; i <= end.first; i++) {
            positions.push_back(Position(i, end.second));
        }
        return positions;
    }

    std::vector<Position> vertical_to_positions()
    {
        std::vector<Position> positions;
        for (int i = start.second; i <= end.second; i++) {
            positions.push_back(Position(end.first, i));
        }
        return positions;
    }
};

class Reservoir {
  private:
    std::vector<std::vector<char>> map;
    int max_x;
    int min_x;
    int max_y;
    int sand_source;

  public:
    Reservoir(std::vector<std::string> lines);
    std::vector<Position> extract_positions(const std::string &str);
    void draw_rock_structures(const std::vector<std::vector<Position>> &p);
    bool drop_sand();
    bool overflow(const Position &p);
};

#endif