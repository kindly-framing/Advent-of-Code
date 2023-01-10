#include "helpers.h"
#include <algorithm>
#include <map>

using namespace std;

using Signals = vector<string>;

struct Signal_Parser {
    static Signals parse_signal_patterns(string signal)
    {
        Signals patterns;
        istringstream ss(signal.substr(0, signal.find(" | ")));
        while (getline(ss, signal, ' ')) {
            patterns.push_back(signal);
        }
        return patterns;
    }

    static Signals parse_output_values(string signal)
    {
        Signals output;
        istringstream ss(signal.substr(signal.find(" | ") + 3));
        while (getline(ss, signal, ' ')) {
            output.push_back(signal);
        }
        return output;
    }
};

int convert_to_unique_digit(const string &str)
{
    if (str.size() == 2) {
        return 1;
    }
    if (str.size() == 4) {
        return 4;
    }
    if (str.size() == 3) {
        return 7;
    }
    if (str.size() == 7) {
        return 8;
    }
    return 0;
}

int diff(string a, string b)
{
    for (size_t i = 0; i < b.size();) {
        int index_a = a.find(b[i]);
        if (index_a != string::npos) {
            a.erase(index_a, 1);
            b.erase(i, 1);
        }
        else {
            i++;
        }
    }
    return max(a.size(), b.size());
}

map<string, int> convert_config_to_map(vector<string> config)
{
    map<string, int> map;
    for (size_t i = 0; i < config.size(); i++) {
        map[config[i]] = i;
    }
    return map;
}

map<string, int> decode(Signals patterns)
{
    vector<string> config(10, "");

    // find the unique digits
    for (auto it = patterns.begin(); it != patterns.end();) {
        if (int n = convert_to_unique_digit(*it)) {
            config[n] = *it;
            patterns.erase(it);
        }
        else {
            it++;
        }
    }

    // find 9 from 4
    for (auto it = patterns.begin(); it != patterns.end();) {
        if (it->size() == 6 && diff(*it, config[4]) == 2) {
            config[9] = *it;
            patterns.erase(it);
            break;
        }
        else {
            it++;
        }
    }

    // find 2 from 9
    for (auto it = patterns.begin(); it != patterns.end();) {
        if (it->size() == 5 && diff(*it, config[9]) == 2) {
            config[2] = *it;
            patterns.erase(it);
            break;
        }
        else {
            it++;
        }
    }

    // find 5 from 2
    for (auto it = patterns.begin(); it != patterns.end();) {
        if (it->size() == 5 && diff(*it, config[2]) == 2) {
            config[5] = *it;
            patterns.erase(it);
            break;
        }
        else {
            it++;
        }
    }

    // 3 is only 5 segment digit
    for (auto it = patterns.begin(); it != patterns.end();) {
        if (it->size() == 5) {
            config[3] = *it;
            patterns.erase(it);
            break;
        }
        else {
            it++;
        }
    }

    // find 6 from 5
    for (auto it = patterns.begin(); it != patterns.end();) {
        if (it->size() == 6 && diff(*it, config[5]) == 1) {
            config[6] = *it;
            patterns.erase(it);
            break;
        }
        else {
            it++;
        }
    }

    // 0 is last
    config[0] = patterns.front();

    return convert_config_to_map(config);
}

bool same_chars(string a, string b)
{
    if (a.size() != b.size()) {
        return false;
    }

    map<char, int> occur1;
    for (char c : a) {
        occur1[c]++;
    }
    map<char, int> occur2;
    for (char c : b) {
        occur2[c]++;
    }

    return occur1 == occur2;
}

int output_value(Signals output, map<string, int> encoder)
{
    string out;
    for (auto value : output) {
        string unscrambled;
        for (auto &digit : encoder) {
            if (same_chars(value, digit.first)) {
                unscrambled = digit.first;
                break;
            }
        }

        out.push_back(encoder[unscrambled] + '0');
    }
    return std::stoi(out);
}

int main()
{
    vector<string> lines = get_lines("sample.txt");

    int sum{};
    for (auto &&line : lines) {
        Signals patterns = Signal_Parser::parse_signal_patterns(line);
        Signals output = Signal_Parser::parse_output_values(line);
        map<string, int> encoder = decode(patterns);
        sum += output_value(output, encoder);
    }
    std::cout << sum << '\n';

    return 0;
}
