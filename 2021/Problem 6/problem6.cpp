/**
 * I wasn't able to use my previous solution for part 1 for part 2 due to
 * REALLY long execution times. Therefore, I decided to utilize a map to store
 * the amount of each fish group along with their total counts. Then for each
 * day, move the counts to their respective groups.
 */
#include "helpers.h"
#include "lanternfish.h"

Lanternfish_Simulation::Lanternfish_Simulation(
    const std::vector<std::string> &data)
{
    std::istringstream ss(data[0]);
    std::string substr;
    while (std::getline(ss, substr, ',')) {
        m_population[std::stoi(substr)]++;
    }
}

long long Lanternfish_Simulation::run_simulation(const size_t &days)
{
    for (size_t i = 0; i < days; i++) {
        Fish_Map updated;

        for (auto &&fish : m_population) {
            // checking if fish will create offspring
            if (fish.first == 0) {
                updated[6] += fish.second; // reset fish back to 6
                updated[8] += fish.second; // add offspring to 8
            }
            // all other fish move to the next lower level
            else {
                updated[fish.first - 1] += fish.second;
            }
        }

        m_population = updated;
    }

    // summing the count of each fish group to get total fish after simulation
    return std::accumulate(
        m_population.begin(), m_population.end(), 0LL,
        [](long long sum, auto fish) { return sum + fish.second; });
}

int main()
{
    std::vector<std::string> lines = get_lines("actual.txt");

    Lanternfish_Simulation sim(lines);
    std::cout << sim.run_simulation(80) << '\n';

    Lanternfish_Simulation sim2(lines);
    std::cout << sim2.run_simulation(256) << '\n';

    return 0;
}