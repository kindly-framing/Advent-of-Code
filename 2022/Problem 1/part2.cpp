#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

std::vector<int> input_calories(const char *file)
{
    freopen(file, "r", stdin);

    std::vector<int> calories;
    std::string in;
    int inventory{};

    // adding each elf's inventory from input
    while (std::getline(std::cin, in))
    {
        // current elf's inventory is done
        if (in.empty())
        {
            calories.push_back(inventory);
            inventory = 0;
        }
        // keep adding to current elf's inventory
        else
        {
            inventory += std::stoi(in);
        }
    }

    calories.push_back(inventory); // last element is missed by loop
    return calories;
}

int main()
{
    // adding the 3 elves with the highest inventories
    std::vector<int> calories = input_calories("sample.txt");
    std::sort(calories.begin(), calories.end());
    std::cout << std::accumulate(calories.end() - 3, calories.end(), 0);
    return 0;
}