#include "grid.h"

struct Position {
    int first;
    int second;

    Position(int first = 0, int second = 0) : first(first), second(second) {}

    std::vector<Position> neighbors(const Position &p,
                                    bool include_diagonals = false)
    {
        std::vector<Position> neighbors = {
            Position(p.first - 1, p.second), Position(p.first + 1, p.second),
            Position(p.first, p.second - 1), Position(p.first, p.second + 1)};

        if (include_diagonals) {
            neighbors.push_back(Position(p.first - 1, p.second - 1));
            neighbors.push_back(Position(p.first + 1, p.second - 1));
            neighbors.push_back(Position(p.first + 1, p.second - 1));
            neighbors.push_back(Position(p.first + 1, p.second + 1));
        }

        return neighbors;
    }
};

class Grid_B : public Grid<char> {
  public:
    Grid_B(std::string filename,
           std::vector<char> (*extractor)(const std::string &))
        : Grid(filename, extractor)
    {
    }
};

std::vector<char> extractor(const std::string &line)
{
    return std::vector<char>(line.begin(), line.end());
}

int main()
{
    Grid_B test("sample.txt", extractor);
    std::cout << test;
    return 0;
}