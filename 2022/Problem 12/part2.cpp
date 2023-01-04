#include <climits>
#include <iostream>
#include <list>
#include <queue>
#include <stdexcept>
#include <string>
#include <vector>

struct Position {
    int row;
    int col;
    Position(int r, int c) : row(r), col(c) {}

    Position() {}

    bool operator==(const Position &a) { return row == a.row && col == a.col; }

    std::list<Position> neighbors() const
    {
        Position north = Position(row - 1, col);
        Position south = Position(row + 1, col);
        Position east = Position(row, col + 1);
        Position west = Position(row, col - 1);
        return {north, south, east, west};
    }
};

struct Maze {
    std::vector<std::vector<int>> map;
    int rows;
    int cols;

    Maze() {}

    Maze(std::vector<std::vector<int>> m)
        : map(m), rows(m.size()), cols(m[0].size())
    {
    }

    std::list<Position> find_neighbors(const Position &p)
    {
        std::list<Position> neighbors;
        for (Position neighbor : p.neighbors()) {
            if (check_move(p, neighbor)) {
                neighbors.push_back(neighbor);
            }
        }
        return neighbors;
    }

    bool is_start(const Position &p) { return map[p.row][p.col] == 0; }

    bool contains(const Position &p)
    {
        return p.row >= 0 && p.col >= 0 && p.row < rows && p.col < cols;
    }

    bool check_move(const Position &from, const Position &to)
    {
        if (!contains(from) || !contains(to)) {
            return false;
        }
        return map[to.row][to.col] >= map[from.row][from.col] - 1;
    }
};

struct Explorer {
    Maze map;
    Position start;
    std::queue<Position> exploration_queue;
    std::vector<std::vector<int>> distances;

    Explorer(Maze terrain, Position s) : map(terrain), start(s)
    {
        for (int r = 0; r < map.rows; r++) {
            distances.push_back(std::vector<int>());
            for (int c = 0; c < map.cols; c++) {
                distances[r].push_back(-1);
            }
        }

        distances[start.row][start.col] = 0;
        exploration_queue.push(start);
    }

    int distance_to(const Position &p) { return distances[p.row][p.col]; }

    bool is_exploring() { return exploration_queue.size() > 0; }

    Position explore()
    {
        if (exploration_queue.empty()) {
            throw std::invalid_argument("Nothing left to explore!\n");
        }

        Position exploring = exploration_queue.front();
        exploration_queue.pop();
        for (Position neighbor : map.find_neighbors(exploring)) {
            if (distances[neighbor.row][neighbor.col] == -1) {
                distances[neighbor.row][neighbor.col] =
                    distances[exploring.row][exploring.col] + 1;
                exploration_queue.push(neighbor);
            }
        }

        return exploring;
    }
};

struct Puzzle {
    Maze map;
    Position start;
    Position end;

    Puzzle() {}

    Puzzle(Maze m, Position s, Position e) : map(m), start(s), end(e) {}

    Puzzle parse(const std::string &input, const char &s, const char &e)
    {
        freopen(input.c_str(), "r", stdin);

        start = Position(0, 0);
        end = Position(0, 0);
        std::vector<std::vector<int>> heights;
        std::string row;
        int r = 0;
        while (std::getline(std::cin, row)) {
            heights.push_back(std::vector<int>());
            for (int c = 0; c < row.size(); c++) {
                char ch = row[c];
                if (ch == s) {
                    start = Position(r, c);
                }
                if (ch == e) {
                    end = Position(r, c);
                }
                heights[r].push_back(char_height(ch));
            }
            r++;
        }

        return Puzzle(Maze(heights), start, end);
    }

    int char_height(char ch)
    {
        switch (ch) {
        case 'E':
            return 'z' - 'a';
        case 'S':
            return 0;
        default:
            return ch - 'a';
        }
    }
};

int main()
{
    Puzzle part1 = Puzzle().parse("actual.txt", 'E', 'a');
    Explorer explorer = Explorer(part1.map, part1.start);
    while (explorer.is_exploring()) {
        Position current_location = explorer.explore();
        if (explorer.map.is_start(current_location)) {
            std::cout
                << "The fewest steps required to move from any square with "
                   "elevation a is "
                << explorer.distance_to(current_location) << " steps.";
            break;
        }
    }
    return 0;
}