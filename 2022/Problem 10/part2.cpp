#include <iostream>
#include <string>

// draws correct pixel if sprite is over cycle position
void draw_pixel(const int &cycle, const int &sprite)
{
    if (cycle - 1 == sprite || cycle == sprite || cycle + 1 == sprite)
    {
        std::cout << '#';
    }
    else
    {
        std::cout << '.';
    }
}

int main()
{
    freopen("actual.txt", "r", stdin);

    int total_cycles{};
    int x_register = 1;

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

            // draw pixel
            draw_pixel((total_cycles - 1) % 40, x_register);

            // CRT is only 40 pixels wide horizontally
            if (total_cycles % 40 == 0) std::cout << '\n';
        }

        // execute instruction if needed
        if (instruction != "noop") x_register += std::stoi(line.substr(5));
    }

    return 0;
}