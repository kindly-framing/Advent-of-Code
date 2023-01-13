#include "helpers.h"

struct Octopus {
    int energy_level;
    bool flashed;

    Octopus(int energy_level, bool flashed = false)
        : energy_level(energy_level), flashed(flashed)
    {
    }

    friend std::ostream &operator<<(std::ostream &os, const Octopus &o)
    {
        os << o.energy_level;
        return os;
    }
};

struct Energy_Grid {
    std::vector<std::vector<Octopus>> octopuses;

    Energy_Grid(std::vector<std::string> lines)
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
};

int main()
{
    std::vector<std::string> lines = get_lines("sample.txt");
    Energy_Grid grid(lines);
    display(grid.octopuses);
    return 0;
}