#ifndef INPUT_H
#define INPUT_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// return all the lines from file into an array. if file can't be opened,
// returns an empty array.
std::vector<std::string> get_lines(const char *file)
{
    std::ifstream in(file);
    if (!in.is_open())
    {
        return {};
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(in, line))
    {
        lines.push_back(line);
    }
    return lines;
}

// displays a vector using cout. Make sure that for own objects to have an <<
// operator overload.
template <typename T> void display(const std::vector<T> &vec)
{
    for (auto &&elem : vec)
    {
        std::cout << elem << '\n';
    }
    std::cout << '\n';
}

// Usuable simple hash for pairs.
struct Pair_Hash
{
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2> &p) const
    {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2;
    }
};

#endif