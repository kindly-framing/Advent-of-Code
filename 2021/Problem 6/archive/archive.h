#ifndef LANTERN_FISH_H
#define LANTERN_FISH_H

#include <algorithm>
#include <list>
#include <sstream>
#include <string>

class Lanternfish_Simulation {
  public:
    Lanternfish_Simulation(const std::string &initial_population);

    long long run_simulation(int days);

    void display_population();

  private:
    struct Lanternfish {
        int timer;

        Lanternfish(int timer = 8) : timer{timer} {}
        void next_day();
    };

    static std::list<Lanternfish> m_population;
};

#endif