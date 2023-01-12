#include "helpers.h"
#include <stack>

char find_corrupt(const std::string &line)
{
    std::map<char, char> braces = {
        {'(', ')'}, {'[', ']'}, {'<', '>'}, {'{', '}'}};

    // checking if line is corrupt and return the first illegal character
    std::stack<char> stack;
    for (char c : line) {
        if (braces.find(c) != braces.end()) {
            stack.push(c);
        }
        else {
            if (braces[stack.top()] == c) {
                stack.pop();
            }
            else {
                return c;
            }
        }
    }

    return '0'; // false for if statement checks
}

int main()
{
    std::vector<std::string> lines = get_lines("sample.txt");

    std::map<char, int> table = {
        {')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};

    int sum{};
    for (auto &&line : lines) {
        char incorrect = find_corrupt(line);
        if (incorrect) {
            sum += table[incorrect];
        }
    }
    std::cout << sum << '\n';

    return 0;
}