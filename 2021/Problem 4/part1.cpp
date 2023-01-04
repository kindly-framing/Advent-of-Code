#include "helpers.h"
#include <queue>
#include <sstream>

struct Board
{
    std::vector<std::vector<int>> grid;

    Board() : grid{} {}
};

struct Bingo_Subsystem
{
    std::queue<int> draw;
    std::vector<Board> boards;

    Bingo_Subsystem(std::vector<std::string> data)
    {
        draw = drawing_numbers(data[0]);

        boards = {};
    }

    std::queue<int> drawing_numbers(const std::string &str)
    {
        std::queue<int> numbers;

        std::stringstream ss(str);
        while (ss.good())
        {
            std::string substr;
            std::getline(ss, substr, ',');
            numbers.push(std::stoi(substr));
        }

        return numbers;
    }
};

int main()
{
    std::vector<std::string> lines = get_lines("sample.txt");
    Bingo_Subsystem board(lines);
    return 0;
}