#include "helpers.h"
#include <unordered_set>

int main()
{
    std::vector<std::string> lines = get_lines("sample.txt");

    std::pair<int, int> entries;
    std::unordered_set<int> set;
    for (auto &&line : lines) {
        int current_expense = std::stoi(line);
        int other_expense = 2020 - current_expense;
        if (set.count(other_expense)) {
            entries.first = current_expense;
            entries.second = other_expense;
            break;
        }
        else {
            set.insert(current_expense);
        }
    }

    std::cout << entries.first * entries.second << '\n';

    return 0;
}