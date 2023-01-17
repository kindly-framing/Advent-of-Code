#ifndef OCTOPUS_H
#define OCTOPUS_H

#include <set>
#include <string>
#include <utility>
#include <vector>

using Position = std::pair<int, int>;

struct Octopus {
    int energy_level;
    bool flashed;

    Octopus(int energy_level, bool flashed = false)
        : energy_level(energy_level), flashed(flashed)
    {
    }
    void increase_energy();
    void reset();
};

class Grid {
  public:
    Grid(std::vector<std::string> lines);

    void next_step();
    void increase_levels();
    void increase_adjacent(const Position &p);

    std::vector<Position> valid_neighbors(const Position &p);
    bool in_bounds(const Position &p);

    Octopus *octopus_at(const Position &p);
    int get_total_flashed();

    bool all_flash();

  private:
    std::vector<std::vector<Octopus>> octopuses;
    int total_flashed_count;
    std::set<Position> current_flashed;
};

#endif