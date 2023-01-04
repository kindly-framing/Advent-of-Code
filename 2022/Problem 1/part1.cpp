#include <iostream>
#include <string>

int main()
{
    freopen("sample.txt", "r", stdin);

    int most_calories = 0; // elf with the most calories
    int calories = 0;      // current elf's inventory

    std::string in;
    while (std::getline(std::cin, in))
    {
        // current elf's inventory is done
        if (in.empty())
        {
            most_calories = std::max(most_calories, calories);
            calories = 0;
        }
        // summing current elf's inventory
        else
        {
            calories += std::stoi(in);
        }
    }

    std::cout << most_calories << std::endl;
    return 0;
}