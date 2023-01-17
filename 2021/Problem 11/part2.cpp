#include "helpers.h"
#include "octopus.h"

void Octopus::increase_energy()
{
    ++energy_level;
    if (!flashed && energy_level > 9) {
        flashed = true;
    }
}

void Octopus::reset()
{
    energy_level = 0;
    flashed = false;
}

Grid::Grid(std::vector<std::string> lines)
    : total_flashed_count{}, current_flashed{}
{
    int r{};
    for (auto &&line : lines) {
        octopuses.push_back(std::vector<Octopus>());
        for (auto &&octopus : line) {
            octopuses[r].push_back(Octopus(octopus - '0'));
        }
        r++;
    }
}

void Grid::next_step()
{
    current_flashed.clear();

    increase_levels();

    for (size_t r = 0; r < octopuses.size(); r++) {
        for (size_t c = 0; c < octopuses[r].size(); c++) {
            Position current(r, c);
            if (octopus_at(current)->flashed) {
                increase_adjacent(current);
            }
        }
    }

    total_flashed_count += current_flashed.size();
}

void Grid::increase_levels()
{
    for (auto &&row : octopuses) {
        for (auto &&col : row) {
            col.increase_energy();
        }
    }
}

void Grid::increase_adjacent(const Position &p)
{
    Octopus *current = octopus_at(p);
    if (current->flashed && !current_flashed.count(p)) {
        current_flashed.insert(p);
        current->reset();

        for (auto &&position : valid_neighbors(p)) {
            if (!current_flashed.count(position)) {
                octopus_at(position)->increase_energy();
                increase_adjacent(position);
            }
        }
    }
}

std::vector<Position> Grid::valid_neighbors(const Position &p)
{
    std::vector<Position> positions = {
        {p.first - 1, p.second},     {p.first + 1, p.second},
        {p.first, p.second - 1},     {p.first, p.second + 1},
        {p.first - 1, p.second - 1}, {p.first + 1, p.second - 1},
        {p.first - 1, p.second + 1}, {p.first + 1, p.second + 1}};

    for (auto it = positions.begin(); it != positions.end();) {
        if (!in_bounds(*it)) {
            positions.erase(it);
        }
        else {
            ++it;
        }
    }
    return positions;
}

bool Grid::in_bounds(const Position &p)
{
    return p.first >= 0 && p.first < octopuses.size() && p.second >= 0 &&
           p.second < octopuses.size();
}

Octopus *Grid::octopus_at(const Position &p)
{
    return &octopuses[p.first][p.second];
}

int Grid::get_total_flashed() { return total_flashed_count; }

bool Grid::all_flash()
{
    return current_flashed.size() == (octopuses.size() * octopuses.size());
}

int main()
{
    std::vector<std::string> lines = get_lines("sample.txt");

    Grid grid(lines);
    int step{0};
    while (!grid.all_flash()) {
        step++;
        grid.next_step();
    }
    std::cout << step << '\n';

    return 0;
}