#include "helpers.h"
#include "signal.h"

Signals Parser::parse_signal_patterns(std::string signal)
{
    Signals patterns;
    std::istringstream ss(signal.substr(0, signal.find(" | ")));
    while (std::getline(ss, signal, ' ')) {
        patterns.push_back(signal);
    }
    return patterns;
}

Signals Parser::parse_output_values(std::string signal)
{
    Signals output;
    std::istringstream ss(signal.substr(signal.find(" | ") + 3));
    while (std::getline(ss, signal, ' ')) {
        output.push_back(signal);
    }
    return output;
}

int Decoder::convert_to_unique_digit(const std::string &signal)
{
    if (signal.size() == 2) {
        return 1;
    }
    if (signal.size() == 4) {
        return 4;
    }
    if (signal.size() == 3) {
        return 7;
    }
    if (signal.size() == 7) {
        return 8;
    }
    return 0;
}

std::map<std::string, int>
Decoder::convert_config_to_map(std::vector<std::string> config)
{
    std::map<std::string, int> map;
    for (size_t i = 0; i < config.size(); i++) {
        map[config[i]] = i;
    }
    return map;
}

std::map<std::string, int> Decoder::decode(Signals patterns)
{
    std::vector<std::string> config(10, "");

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

/**
 * @brief By using the output signal and encoder for the output signal, converts
 * to number on segment display.
 *
 */
int output_value(Signals output, std::map<std::string, int> encoder)
{
    std::string out;
    for (auto value : output) {
        std::string unscrambled;
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
    std::vector<std::string> lines = get_lines("sample.txt");

    int sum{};
    for (auto &&line : lines) {
        Signals patterns = Parser::parse_signal_patterns(line);
        Signals output = Parser::parse_output_values(line);
        std::map<std::string, int> encoder = Decoder::decode(patterns);
        sum += output_value(output, encoder);
    }
    std::cout << sum << '\n';

    return 0;
}
