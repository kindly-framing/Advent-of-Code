#include "helpers.h"
#include <queue>
#include <set>

using Position = std::pair<int, int>;

struct Octopus {
    int energy_level;
    bool flashed;

    Octopus(int energy_level, bool flashed = false)
        : energy_level(energy_level), flashed(flashed)
    {
    }

    void increase_energy()
    {
        ++energy_level;
        if (!flashed && energy_level > 9) {
            flashed = true;
        }
    }

    void reset()
    {
        energy_level = 0;
        flashed = false;
    }

    friend std::ostream &operator<<(std::ostream &os, const Octopus &o)
    {
        os << o.energy_level;
        return os;
    }

    bool operator==(const Octopus &o)
    {
        return energy_level == o.energy_level && flashed == o.flashed;
    }
};

struct Energy_Grid {
    std::vector<std::vector<Octopus>> octopuses;
    std::set<Position> flashed;

    Energy_Grid(std::vector<std::string> lines) : flashed{}
    {
        int r{};
        for (auto &&line : lines) {
            octopuses.push_back(std::vector<Octopus>());
            for (int c = 0; c < line.size(); c++) {
                octopuses[r].push_back(Octopus(line[c] - '0'));
            }
            r++;
        }
    }

    void next_step()
    {
        flashed.clear();

        increase_levels();

        for (size_t r = 0; r < octopuses.size(); r++) {
            for (size_t c = 0; c < octopuses[r].size(); c++) {
                Position current(r, c);
                if (octopus_at(current)->flashed) {
                    increase_adjacent(current);
                }
            }
        }
    }

    void increase_levels()
    {
        for (auto &&row : octopuses) {
            for (auto &&col : row) {
                col.increase_energy();
            }
        }
    }

    void increase_adjacent(const Position &start)
    {
        Octopus *current = octopus_at(start);
        if (current->flashed && !flashed.count(start)) {
            flashed.insert(start);
            current->reset();
            for (auto &&position : neighbors(start)) {
                if (!flashed.count(position)) {
                    octopus_at(position)->increase_energy();
                    increase_adjacent(position);
                }
            }
        }
    }

    void add_neighbors(const Position &p, std::queue<Position> &q)
    {
        for (auto &&pos : neighbors(p)) {
            q.push(pos);
        }
    }

    std::vector<Position> neighbors(const Position &p)
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

    bool in_bounds(const Position &p)
    {
        return p.first >= 0 && p.first < octopuses.size() && p.second >= 0 &&
               p.second < octopuses.size();
    }

    Octopus *octopus_at(const Position &p)
    {
        return &octopuses[p.first][p.second];
    }

    bool all_flash()
    {
        return flashed.size() == (octopuses.size() * octopuses.size());
    }
};

int main()
{
    std::vector<std::string> lines = get_lines("actual.txt");

    Energy_Grid grid(lines);
    int step{0};
    while (!grid.all_flash()) {
        step++;
        grid.next_step();
    }
    std::cout << step << '\n';

    return 0;
}