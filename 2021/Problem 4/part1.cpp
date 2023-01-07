#include "helpers.h"
#include <cassert>
#include <queue>
#include <sstream>
#include <utility>

struct Board {
    struct Element {
        int value;
        bool marked;
        Element(int _val, bool _marked = false) : value(_val), marked(_marked)
        {
        }
    };

    std::vector<std::vector<Element>> grid;
    std::pair<int, int> last_marked;

    Board() : grid{}, last_marked{} {}

    Board(std::vector<std::string>::iterator start,
          std::vector<std::string>::iterator end)
    {
        size_t row{};
        for (auto it = start; it != end; it++, row++) {
            grid.push_back(std::vector<Element>{});
            grid[row] = parse_numbers(*it);
        }
    }

    std::vector<Element> parse_numbers(const std::string &str)
    {
        std::vector<Element> numbers;
        std::stringstream ss(str);
        int n;
        while (ss >> n) {
            numbers.push_back(Element(n));
        }
        return numbers;
    }

    void mark(const int &Element)
    {
        for (size_t i = 0; i < grid.size(); i++) {
            for (size_t j = 0; j < grid[i].size(); j++) {
                if (grid[i][j].value == Element) {
                    grid[i][j].marked = true;
                    last_marked = std::make_pair(i, j);
                }
            }
        }
    }

    bool won()
    {
        bool vertical_win = true;
        for (size_t i = 0; i < grid.size(); i++) {
            if (!grid[i][last_marked.second].marked) {
                vertical_win = false;
            }
        }

        bool horizontal_win = true;
        for (size_t i = 0; i < grid[last_marked.first].size(); i++) {
            if (!grid[last_marked.first][i].marked) {
                horizontal_win = false;
            }
        }

        return vertical_win || horizontal_win;
    }
};

class Bingo {
  public:
    Bingo(std::vector<std::string> data)
    {
        queue_drawing_numbers(data[0]);
        for (auto it = data.begin() + 2; it - 1 != data.end(); it += 6) {
            m_boards.push_back(Board(it, it + 5));
        }
        invariant();
    }

    bool won()
    {
        invariant();
        for (Board b : m_boards) {
            if (b.won()) {
                m_winner = b;
                return true;
            }
        }
        return false;
    }

    void draw_number()
    {
        invariant();
        m_last_drawn = m_drawing_numbers.front();
        m_drawing_numbers.pop();
        for (Board &b : m_boards) {
            b.mark(m_last_drawn);
        }
    }

    int score()
    {
        invariant();
        int unmarked_sum{};
        for (size_t i = 0; i < m_winner.grid.size(); i++) {
            for (size_t j = 0; j < m_winner.grid[i].size(); j++) {
                if (!m_winner.grid[i][j].marked) {
                    unmarked_sum += m_winner.grid[i][j].value;
                }
            }
        }
        return unmarked_sum * m_last_drawn;
    }

  private:
    std::queue<int> m_drawing_numbers;
    std::vector<Board> m_boards;
    int m_last_drawn;
    Board m_winner;

    void queue_drawing_numbers(const std::string &data)
    {
        std::stringstream ss(data);
        std::string substr;
        while (std::getline(ss, substr, ',')) {
            int n;
            try {
                n = std::stoi(substr);
            }
            catch (const std::exception &e) {
                throw std::invalid_argument(
                    "Drawing numbers aren't formatted/placed correctly in "
                    "file!\n");
            }

            m_drawing_numbers.push(n);
        }
    }

    void invariant()
    {
        assert(!m_drawing_numbers.empty());
        assert(!m_boards.empty());
    }
};

int main()
{
    std::vector<std::string> lines = get_lines("sample.txt");

    Bingo m_boards(lines);
    while (!m_boards.won()) {
        m_boards.draw_number();
    }
    std::cout << m_boards.score() << '\n';

    return 0;
}