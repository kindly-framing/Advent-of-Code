// reading each command
// apply movement to submarine
// end multiply horizontal position and depth
#include <fstream>
#include <iostream>
#include <string>

struct Submarine
{
    int pos;
    int depth;
    int aim;

    Submarine() : pos{}, depth{}, aim{} {}

    void execute(const std::string &command)
    {
        int val = std::stoi(command.substr(command.find(' ') + 1));
        switch (command[0])
        {
        case 'f':
            pos += val;
            depth += aim * val;
            break;
        case 'u':
            aim -= val;
            break;
        case 'd':
            aim += val;
            break;
        default:
            throw std::invalid_argument("Not a valid command: " + command);
        }
    }
};

int main()
{
    std::ifstream in("sample.txt");

    Submarine sub;
    std::string command;
    while (std::getline(in, command))
    {
        sub.execute(command);
    }

    std::cout << sub.depth * sub.pos << '\n';
    return 0;
}