#include "helpers.h"
#include <algorithm>
#include <stack>

std::string find_incomplete_sequence(const std::string &line)
{
    std::map<char, char> braces = {
        {'(', ')'}, {'[', ']'}, {'<', '>'}, {'{', '}'}};

    // matching opening braces with closing braces
    std::stack<char> stack;
    for (char c : line) {
        // checking if c is opening brace
        if (braces.find(c) != braces.end()) {
            stack.push(c);
        }
        // checking if brace is complete, otherwise, line is corrupt
        else {
            if (braces[stack.top()] == c) {
                stack.pop();
            }
            else {
                return "";
            }
        }
    }

    // building sequence from incomplete braces, if any
    std::string sequence;
    while (!stack.empty()) {
        sequence.push_back(braces[stack.top()]);
        stack.pop();
    }
    return sequence;
}

int main()
{
    std::vector<std::string> lines = get_lines("actual.txt");

    // finding the scores for incomplete lines using scoring table.
    std::map<char, int> table = {{')', 1}, {']', 2}, {'}', 3}, {'>', 4}};
    std::vector<long long> scores;
    for (auto &&line : lines) {
        std::string sequence = find_incomplete_sequence(line);

        if (!sequence.empty()) {
            long long score{};
            for (char c : sequence) {
                score = (score * 5) + table[c];
            }
            scores.push_back(score);
        }
    }

    // finding the middle value
    std::sort(scores.begin(), scores.end());
    std::cout << scores[scores.size() / 2] << '\n';
    return 0;
}