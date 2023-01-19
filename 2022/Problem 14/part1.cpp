// construct a graph that is a translated version of input
// drop sand from sand source until out of bounds
//      handle logic for dropping sand
// return the count of how many sand units dropped
#include "helpers.h"
#include "reservoir.h"

Reservoir::Reservoir(std::vector<std::string> lines)
{
    // initialized first in order to calculate graph dimensions
    max_x = 0;
    max_y = 0;
    min_x = INT_MAX;

    // extracting the positions for rocks and finding the dimensions for the
    // graph
    std::vector<std::vector<Position>> rocks;
    for (auto &&line : lines) {
        std::vector<Position> line_rocks = extract_positions(line);
        rocks.push_back(line_rocks);

        for (auto &&pos : line_rocks) {
            max_x = std::max(max_x, pos.first);
            max_y = std::max(max_y, pos.second);
            min_x = std::min(min_x, pos.first);
        }
    }

    // creating graph with rock structures
    map = std::vector<std::vector<char>>(
        max_y, std::vector<char>(max_x - min_x + 1, '.'));
    sand_source = 500 - min_x;
    map[0][sand_source] = '+';
    draw_rock_structures(rocks);
}

std::vector<Position> Reservoir::extract_positions(const std::string &str)
{
    std::vector<Position> positions;
    std::istringstream ss(str);
    std::string position;
    int x;
    int y;
    while (std::getline(ss, position, ' ')) {
        sscanf(position.c_str(), "%d,%d", &x, &y);
        positions.push_back(Position(x, y));
        ss.ignore(3); // ignores seperator " -> "
    }
    return positions;
}

void Reservoir::draw_rock_structures(
    const std::vector<std::vector<Position>> &p)
{
    for (size_t r = 0; r < p.size(); r++) {
        for (size_t c = 0; c + 1 < p[r].size(); c++) {
            Position a = p[r][c];
            Position b = p[r][c + 1];
            Line current(a, b);
            for (auto &&pos : current.convert_to_positions()) {
                map[pos.second - 1][pos.first - min_x] = '#';
            }
        }
        std::cout << '\n';
    }
}

bool Reservoir::drop_sand()
{
    Position rest(0, sand_source);

    bool found_rest_position = false;
    while (!found_rest_position) {
        // fall down until obstacle is reached
        while (map[rest.first + 1][rest.second] == '.') {
            rest.first++;
        }

        // check bottom left if in bounds and then if filled
        Position bottom_left(rest.first + 1, rest.second - 1);
        if (!overflow(bottom_left) && !filled(bottom_left)) {
            found_rest_position = bottom_left;
        }
    }

    if (overflow(rest)) {
        return false;
    }
    map[rest.first][rest.second] = 'o';
    return true;
}

bool Reservoir::overflow(const Position &p)
{
    return p.first < 0 || p.first >= map.size() || p.second < 0 ||
           p.second >= map[0].size();
}

int main()
{
    std::vector<std::string> lines = get_lines("sample.txt");

    int sand_units{};
    Reservoir cave(lines);
    while (cave.drop_sand()) {
        sand_units++;
    }
    std::cout << sand_units << '\n';

    return 0;
}