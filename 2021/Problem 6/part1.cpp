#include "helpers.h"
#include "lanternfish.h"

std::list<Lanternfish_Simulation::Lanternfish>
    Lanternfish_Simulation::m_population;

Lanternfish_Simulation::Lanternfish_Simulation(
    const std::string &initial_population)
{
    Lanternfish_Simulation::m_population = {};
    std::stringstream ss(initial_population);
    std::string substr;
    while (std::getline(ss, substr, ',')) {
        int timer;
        try {
            timer = std::stoi(substr);
        }
        catch (const std::invalid_argument &e) {
            throw std::invalid_argument("Population format is incorrect\n");
        }
        m_population.push_back(Lanternfish(timer));
    }
}

long long Lanternfish_Simulation::run_simulation(int days)
{
    while (days-- > 0) {
        auto it = m_population.begin();
        const size_t end = m_population.size();
        for (size_t i = 0; i < end; i++) {
            it->next_day();
            std::advance(it, 1);
        }
    }
    return m_population.size();
}

void Lanternfish_Simulation::Lanternfish::next_day()
{
    if (--timer < 0) {
        // leave this in this order. unsure why but causes timers to go to -1
        timer = 6;
        m_population.push_back(Lanternfish());
    }
}

void Lanternfish_Simulation::display_population()
{
    for (auto it = m_population.begin(); it != m_population.end(); it++) {
        std::cout << it->timer << ' ';
    }
    std::cout << '\n';
}

int main()
{
    std::vector<std::string> lines = get_lines("actual.txt");
    Lanternfish_Simulation sim(lines[0]);
    std::cout << sim.run_simulation(80) << '\n';
    return 0;
}
