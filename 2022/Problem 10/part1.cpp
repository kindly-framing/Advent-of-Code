#include <iostream>
#include <string>

// determines if cycle is a target cycle
bool is_target_cycle(const int &cycle)
{
    int arr[6] = {20, 60, 100, 140, 180, 220};
    for (int i = 0; i < 6; i++)
    {
        if (arr[i] == cycle) return true;
    }
    return false;
}

int main()
{
    freopen("actual.txt", "r", stdin);

    int total_cycles{};
    int x_register = 1;
    long signal_sum{};

    std::string line;
    while (std::getline(std::cin, line))
    {
        // determine amount of cycles based on instruction
        std::string instruction = line.substr(0, 4);
        int cycles = (instruction == "noop") ? 1 : 2;

        // run cycles of instruction
        for (int i = 0; i < cycles; i++)
        {
            total_cycles++;

            // add signal strength at cycle
            if (is_target_cycle(total_cycles))
            {
                signal_sum += total_cycles * x_register;
            }
        }

        // execute instruction if needed
        if (instruction != "noop") x_register += std::stoi(line.substr(5));
    }

    std::cout << signal_sum << '\n';

    return 0;
}