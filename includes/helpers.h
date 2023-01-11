#ifndef INPUT_H
#define INPUT_H

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

// return all the lines from file into an array. if file can't be opened,
// returns an empty array.
std::vector<std::string> get_lines(const char *file)
{
    std::ifstream in(file);
    if (!in.is_open()) {
        return {};
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(in, line)) {
        lines.push_back(line);
    }
    return lines;
}

// displays a vector using cout. Make sure that for own objects to have an <<
// operator overload.
template <typename T> void display(const std::vector<T> &vec)
{
    for (auto &&elem : vec) {
        std::cout << elem << ' ';
    }
    std::cout << '\n';
}

// displays a 2d vector using cout. Make sure that for own objects to have an <<
// operator overload.
template <typename T> void display(const std::vector<std::vector<T>> &vec)
{
    for (auto &&row : vec) {
        for (auto &&elem : row) {
            std::cout << elem << ' ';
        }
        std::cout << '\n';
    }
}

// Usuable simple hash for pairs.
struct Pair_Hash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2> &p) const
    {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2;
    }
};

// general function to parse numbers from string into a vector seperated by
// delimeter.
std::vector<int> parse_numbers(const std::string &s, const char &delim)
{
    std::vector<int> numbers;
    std::istringstream ss(s);
    std::string substr;
    while (std::getline(ss, substr, delim)) {
        numbers.push_back(std::stoi(substr));
    }
    return numbers;
}

// returns the number of characters that are different between the two strings.
int diff(std::string a, std::string b)
{
    for (size_t i = 0; i < b.size();) {
        int index_a = a.find(b[i]);
        if (index_a != std::string::npos) {
            a.erase(index_a, 1);
            b.erase(i, 1);
        }
        else {
            i++;
        }
    }
    return std::max(a.size(), b.size());
}

// returns true if the two strings are equal in terms of content regardless of
// order.
bool same_chars(std::string a, std::string b)
{
    if (a.size() != b.size()) {
        return false;
    }

    std::map<char, int> occur1;
    for (char c : a) {
        occur1[c]++;
    }
    std::map<char, int> occur2;
    for (char c : b) {
        occur2[c]++;
    }
    return occur1 == occur2;
}

#endif