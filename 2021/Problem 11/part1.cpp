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
    int count;
    std::set<Position> flashed;

    Energy_Grid(std::vector<std::string> lines) : count{}, flashed{}
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
                    ++count;
                    octopus_at(current)->reset();
                    increase_adjacent(current);
                }
            }
        }

        count += flashed.size();
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
        std::set<Position> visited;
        std::queue<Position> queue;
        add_neighbors(start, queue);

        while (!queue.empty()) {
            Position temp = queue.front();
            queue.pop();

            if (!visited.count(temp)) {
                visited.insert(temp);

                Octopus *current = octopus_at(temp);

                // already been flashed
                if (octopus_at(temp)->energy_level == 0) {
                    continue;
                }

                // adding energy to adjacent
                current->increase_energy();

                // if flashed from adding adjacent, reset and add neighbors
                if (current->flashed && current->energy_level == 10) {
                    add_neighbors(temp, queue);
                    ++count;
                    current->reset();
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
};

int main()
{
    std::vector<std::string> lines = get_lines("sample.txt");

    Energy_Grid grid(lines);
    for (int i = 1; i <= 2; i++) {
        grid.next_step();
        std::cout << "After step " << i << ":\n";
        display(grid.octopuses);
        std::cout << '\n';
    }
    std::cout << grid.count << " == " << 35 << '\n';

    return 0;
}