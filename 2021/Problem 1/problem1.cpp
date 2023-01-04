#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int part1(const std::vector<std::string> &input)
{
    int count{};
    int prev = std::stoi(input[0]);
    for (int i = 1; i < input.size(); i++)
    {
        int next = std::stoi(input[i]);
        if (next - prev > 0)
        {
            count++;
        }
        prev = next;
    }
    return count;
}

int part2(const std::vector<std::string> &input)
{
    using std::stoi;
    std::vector<int> windows;
    for (size_t i = 0; i + 2 < input.size(); i++)
    {
        int w = stoi(input[i]) + stoi(input[i + 1]) + stoi(input[i + 2]);
        windows.push_back(w);
    }

    int count{};
    int prev = windows[0];
    for (int i = 1; i < windows.size(); i++)
    {
        int next = windows[i];
        if (next - prev > 0)
        {
            count++;
        }
        prev = next;
    }
    return count;
}

std::vector<std::string> read_lines(const char *file)
{
    std::ifstream in(file);
    std::vector<std::string> lines;
    std::string token;
    while (std::getline(in, token))
    {
        lines.push_back(token);
    }
    return lines;
}

int main()
{
    std::vector<std::string> input = read_lines("sample.txt");
    std::cout << part1(input) << std::endl;
    std::cout << part2(input) << std::endl;
    return 0;
}