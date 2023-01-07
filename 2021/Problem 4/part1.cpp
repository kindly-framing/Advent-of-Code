#include "helpers.h"
#include <queue>
#include <sstream>
#include <utility>

struct Number
{
    int value;
    bool marked;
    Number(int _val, int _marked = false) : value(_val), marked(_marked) {}
};

struct Board
{
    std::vector<std::vector<Number>> grid;
    std::pair<int, int> last_marked;

    Board() : grid{}, last_marked{} {}

    Board(std::vector<std::string>::iterator start,
          std::vector<std::string>::iterator end)
    {
        size_t row{};
        for (auto it = start; it != end; it++, row++)
        {
            grid.push_back(std::vector<Number>{});
            grid[row] = parse_numbers(*it);
        }
    }

    std::vector<Number> parse_numbers(const std::string &str)
    {
        std::vector<Number> numbers;
        std::stringstream ss(str);
        int n;
        while (ss >> n)
        {
            numbers.push_back(Number(n));
        }
        return numbers;
    }

    void mark(const int &number)
    {
        for (size_t i = 0; i < grid.size(); i++)
        {
            for (size_t j = 0; j < grid[i].size(); j++)
            {
                if (grid[i][j].value == number)
                {
                    grid[i][j].marked = true;
                    last_marked = std::make_pair(i, j);
                }
            }
        }
    }

    bool won()
    {
        bool vertical_win = true;
        for (size_t i = 0; i < grid.size(); i++)
        {
            if (!grid[i][last_marked.second].marked)
            {
                vertical_win = false;
            }
        }

        bool horizontal_win = true;
        for (size_t i = 0; i < grid[last_marked.first].size(); i++)
        {
            if (!grid[last_marked.first][i].marked)
            {
                horizontal_win = false;
            }
        }

        return vertical_win || horizontal_win;
    }
};

struct Bingo_Subsystem
{
    std::queue<int> draw;
    std::vector<Board> boards;
    int last_drawn;
    Board winner;

    Bingo_Subsystem(std::vector<std::string> data)
    {
        draw = queue_drawing_numbers(data[0]);
        for (auto it = data.begin() + 2; it - 1 != data.end(); it += 6)
        {
            boards.push_back(Board(it, it + 5));
        }
    }

    std::queue<int> queue_drawing_numbers(const std::string &str)
    {
        std::queue<int> numbers;
        std::stringstream ss(str);
        std::string substr;
        while (std::getline(ss, substr, ','))
        {
            numbers.push(std::stoi(substr));
        }
        return numbers;
    }

    bool won()
    {
        for (Board &b : boards)
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
            throw std::logic_error("No more drawing numbers!\n");
        }

        last_drawn = draw.front();
        draw.pop();
        for (Board &b : boards)
        {
            b.mark(last_drawn);
        }
    }

    int score()
    {
        int unmarked_sum{};
        for (size_t i = 0; i < winner.grid.size(); i++)
        {
            for (size_t j = 0; j < winner.grid[i].size(); j++)
            {
                if (!winner.grid[i][j].marked)
                {
                    unmarked_sum += winner.grid[i][j].value;
                }
            }
        }
        return unmarked_sum * last_drawn;
    }
};

int main()
{
    std::vector<std::string> lines = get_lines("sample.txt");

    Bingo_Subsystem boards(lines);
    while (!boards.won())
    {
        boards.draw_number();
    }
    std::cout << boards.score() << '\n';

    return 0;
}