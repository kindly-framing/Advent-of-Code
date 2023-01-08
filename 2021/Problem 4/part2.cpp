#include "helpers.h"
#include "subsystem.h"

Board::Board(std::vector<std::string>::iterator begin,
             std::vector<std::string>::iterator end)
{
    size_t row{};
    for (auto it = begin; it != end; it++, row++) {
        grid.push_back(std::vector<Element>{});
        grid[row] = parse_numbers(*it);
    }
}

std::vector<Board::Element> Board::parse_numbers(const std::string &str)
{
    std::vector<Element> numbers;
    std::stringstream ss(str);
    int n;
    while (ss >> n) {
        numbers.push_back(Element(n));
    }
    return numbers;
}

void Board::mark(const int &value)
{
    for (size_t i = 0; i < grid.size(); i++) {
        for (size_t j = 0; j < grid[i].size(); j++) {
            if (grid[i][j].value == value) {
                grid[i][j].marked = true;
                last_marked = std::make_pair(i, j);
            }
        }
    }
}

bool Board::won()
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

Bingo::Bingo(std::vector<std::string> data)
{
    queue_drawing_numbers(data[0]);
    for (auto it = data.begin() + 2; it - 1 != data.end(); it += 6) {
        m_boards.push_back(Board(it, it + 5));
    }
    invariant();
}

bool Bingo::won()
{
    invariant();
    for (auto it = m_boards.begin(); it != m_boards.end();) {
        bool won = it->won();
        if (won && m_boards.size() == 1) {
            m_winner = m_boards.front();
            return true;
        }
        else if (won) {
            it = m_boards.erase(it);
        }
        else {
            it++;
        }
    }
    return false;
}

void Bingo::draw_number()
{
    invariant();
    m_last_drawn = m_drawing_numbers.front();
    m_drawing_numbers.pop();
    for (Board &b : m_boards) {
        b.mark(m_last_drawn);
    }
}

int Bingo::score()
{
    invariant();
    assert(!m_winner.grid.empty());
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

void Bingo::queue_drawing_numbers(const std::string &data)
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

void Bingo::invariant()
{
    assert(!m_drawing_numbers.empty());
    assert(!m_boards.empty());
}

int main()
{
    std::vector<std::string> lines = get_lines("sample.txt");

    Bingo boards(lines);
    while (!boards.won()) {
        boards.draw_number();
    }
    std::cout << boards.score() << '\n';

    return 0;
}