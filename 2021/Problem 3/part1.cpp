#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

std::vector<std::string> input(const char *file)
{
    std::ifstream in(file);
    std::vector<std::string> lines;
    std::string l;
    while (std::getline(in, l))
    {
        lines.push_back(l);
    }
    return lines;
}

std::pair<std::string, std::string>
gamma_epsilon(const std::vector<std::string> &binaries)
{
    std::string gamma;
    std::string epsilon;
    for (int i = 0; i < binaries[i].size(); i++)
    {
        // count with bit is the most common
        int count{};
        for (std::string binary : binaries)
        {
            count += (binary[i] ^ '0') ? 1 : -1;
        }

        // for the current bit index, place most common in gamma, and least
        // common in epsilon
        char most_common = (count < 0) ? '0' : '1';
        gamma += most_common;
        epsilon += most_common ^ 1;
    }
    return {gamma, epsilon};
}

int main()
{
    std::vector<std::string> binaries = input("sample.txt");
    std::pair<std::string, std::string> rate = gamma_epsilon(binaries);
    std::cout << std::stoi(rate.first, 0, 2) * std::stoi(rate.second, 0, 2)
              << '\n';
    return 0;
}