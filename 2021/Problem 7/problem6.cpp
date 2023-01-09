// for each position in list
// calculate the fuel for all value to move to that position
// check if the fuel is the minimum and save the position
// return that fuel number
#include "helpers.h"
#include <algorithm>
#include <cmath>

int part1(const std::vector<int> &crabs)
{
    int max = *std::max_element(crabs.begin(), crabs.end());
    int min = INT_MAX;
    for (int pos = 1; pos <= max; pos++) {
        int fuel{};
        for (int i = 0; i < crabs.size(); i++) {
            fuel += std::abs(crabs[i] - pos);
        }
        min = std::min(min, fuel);
    }
    return min;
}

int part2(const std::vector<int> &crabs)
{
    int max = *std::max_element(crabs.begin(), crabs.end());
    int min = INT_MAX;
    for (int pos = 1; pos <= max; pos++) {
        int fuel{};
        for (int i = 0; i < crabs.size(); i++) {
            int n = std::abs(crabs[i] - pos);
            fuel += n * (n + 1) / 2;
        }
        min = std::min(min, fuel);
    }
    return min;
}

int main()
{
    std::vector<std::string> lines = get_lines("sample.txt");

    std::vector<int> crabs = parse_numbers(lines[0], ',');
    std::cout << part1(crabs) << '\n';
    std::cout << part2(crabs) << '\n';

    return 0;
}