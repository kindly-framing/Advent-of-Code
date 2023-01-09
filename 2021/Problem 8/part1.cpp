#include "helpers.h"

using Signals = std::vector<std::string>;

struct Signal_Parser {
    static Signals parse_signal_patterns(std::string signal)
    {
        Signals patterns;
        std::istringstream ss(signal.substr(0, signal.find(" | ")));
        while (std::getline(ss, signal, ' ')) {
            patterns.push_back(signal);
        }
        return patterns;
    }

    static Signals parse_output_values(std::string signal)
    {
        Signals output;
        std::istringstream ss(signal.substr(signal.find(" | ") + 3));
        while (std::getline(ss, signal, ' ')) {
            output.push_back(signal);
        }
        return output;
    }
};

bool is_easy_digit(int n) { return n == 2 || n == 3 || n == 4 || n == 7; }

int count_easy_digits(Signals patterns, Signals output)
{
    int count{};
    for (auto &&pattern : patterns) {
        for (auto &&value : output) {
            if (pattern.size() == value.size() && is_easy_digit(value.size())) {
                count++;
            }
        }
    }
    return count;
}

int main()
{
    std::vector<std::string> lines = get_lines("actual.txt");

    int count{};
    for (auto &&line : lines) {
        Signals patterns = Signal_Parser::parse_signal_patterns(line);
        Signals output = Signal_Parser::parse_output_values(line);
        count += count_easy_digits(patterns, output);
    }
    std::cout << count << '\n';

    return 0;
}
