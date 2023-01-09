#ifndef LANTERN_FISH_H
#define LANTERN_FISH_H

#include <numeric>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using Fish_Map = std::unordered_map<int, long long>;

class Lanternfish_Simulation {
  public:
    Lanternfish_Simulation(const std::vector<std::string> &data);

    long long run_simulation(const size_t &days);

  private:
    Fish_Map m_population;
};

#endif