#include "helpers.h"

/**
 * @brief A Submarine object that takes a series of commands to change it's
 * horizontal position and depth.
 *
 */
struct Submarine
{
    int pos;
    int depth;

    Submarine() : pos{}, depth{} {}

    /**
     * @brief Executes the command given after checking if the command can be
     * executed.
     *
     * @throw std::invalid_argument Command must be in the correct format.
     * (direction X) with X being an integer.
     * @param command An executable submarine command.
     */
    void execute(const std::string &command)
    {
        if (!is_executable(command))
        {
            throw std::invalid_argument("Not a submarine command: " + command);
        }

        int units;
        sscanf(command.c_str(), "%*s %d", &units);
        switch (command[0])
        {
        case 'f':
            pos += units;
            break;
        case 'u':
            depth -= units;
            break;
        case 'd':
            depth += units;
            break;
        }
    }

    /**
     * @brief Checks if the given string is an executable Submarine command.
     *
     * @param str A string.
     * @return If the command can be executed on the submarine.
     */
    bool is_executable(const std::string &str)
    {
        char direction[8];
        int units;
        char terminated;
        sscanf(str.c_str(), "%8s %d%c", direction, &units, &terminated);
        std::string dir = direction;

        bool is_direction = (dir == "forward" || dir == "down" || dir == "up");
        bool is_positive_units = (units >= 0);
        bool is_end_of_string = (terminated == '\0');
        return is_direction && is_positive_units && is_end_of_string;
    }
};

int main()
{
    std::vector<std::string> lines = get_lines("sample.txt");

    Submarine sub;
    for (std::string command : lines)
    {
        sub.execute(command);
    }
    std::cout << sub.depth * sub.pos << '\n';

    return 0;
}