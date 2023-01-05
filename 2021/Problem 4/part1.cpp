#include "helpers.h"
#include <queue>
#include <sstream>

struct Board
{
    std::vector<std::vector<int>> grid;
    std::vector<std::vector<bool>> marked;

    Board() {}

    using parse_iterator = std::vector<std::string>::iterator;
    Board(parse_iterator start, parse_iterator end)
    {
        size_t row{};
        for (auto it = start; it != end; it++, row++)
        {
            grid.push_back(std::vector<int>{});
            grid[row] = parse_numbers(*it);

            marked.push_back(std::vector<bool>{});
            marked[row] = std::vector<bool>(grid[row].size(), false);
        }
    }

    std::vector<int> parse_numbers(const std::string &str)
    {
        std::vector<int> numbers;
        std::stringstream ss(str);
        int n;
        while (!ss.eof())
        {
            ss >> n;
            numbers.push_back(n);
        }
        return numbers;
    }

    void mark(const int &number)
    {
        for (size_t i = 0; i < grid.size(); i++)
        {
            for (size_t j = 0; j < grid[i].size(); j++)
            {
                if (grid[i][j] == number)
                {
                    marked[i][j] = true;
                }
            }
        }
    }

    bool won() {}
};

struct Bingo_Subsystem
{
    std::queue<int> draw;
    std::vector<Board> boards;
    int last_called;
    Board winner;

    Bingo_Subsystem(std::vector<std::string> data)
    {
        draw = queue_drawing_numbers(data[0]);
        for (size_t i = 2; i < data.size(); i += 6)
        {
            boards.push_back(Board(data.begin() + i, data.begin() + i + 5));
        }
    }

    std::queue<int> queue_drawing_numbers(const std::string &str)
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

    bool won()
    {
        for (Board b : boards)
        {
            if (b.won())
            {
                winner = b;
                return true;
            }
        }
        return false;
    }

    void draw_number()
    {
        if (draw.empty())
        {
            throw std::logic_error("No more numbers to draw!\n");
        }

        last_called = draw.front();
        draw.pop();
        for (Board b : boards)
        {
            b.mark(last_called);
        }
    }

    int score()
    {
        int unmarked_sum{};
        for (size_t i = 0; i < winner.grid.size(); i++)
        {
            for (size_t j = 0; j < winner.grid[i].size(); j++)
            {
                if (!winner.marked[i][j])
                {
                    unmarked_sum += winner.grid[i][j];
                }
            }
        }
        return unmarked_sum * last_called;
    }
};

int main()
{
    std::vector<std::string> lines = get_lines("sample.txt");

    Bingo_Subsystem board(lines);
    while (!board.won())
    {
        board.draw_number();
    }
    std::cout << board.score() << '\n';

    return 0;
}