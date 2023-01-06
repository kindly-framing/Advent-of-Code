#include "helpers.h"

/**
 * @brief A Submarine object that takes a series of commands to change it's
 * horizontal position, depth, and aim.
 *
 */
struct Submarine
{
    int m_pos;
    int m_depth;
    int m_aim;

    Submarine() : m_pos{}, m_depth{}, m_aim{} {}

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

        // for part 2, the commands have been changed to reflect the addition of
        // the aim value.
        int units;
        sscanf(command.c_str(), "%*s %d", &units);
        switch (command[0])
        {
        case 'f':
            m_pos += units;
            m_depth += m_aim * units;
            break;
        case 'u':
            m_aim -= units;
            break;
        case 'd':
            m_aim += units;
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
        // reading word, number, and last character in string.
        char direction[8];
        int units;
        char last;
        sscanf(str.c_str(), "%8s %d%c", direction, &units, &last);
        std::string dir = direction;

        // checking that characteristics of an executable command are met.
        bool is_direction = (dir == "forward" || dir == "down" || dir == "up");
        bool is_positive_units = (units >= 0);
        bool is_end_of_string = (last == '\0');
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
    std::cout << sub.m_depth * sub.m_pos << '\n';

    return 0;
}