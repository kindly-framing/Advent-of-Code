#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

struct Binary
{
    std::string binary;

    Binary(std::string b) : binary(b){};

    bool valid_bit_criteria(const int &pos, const int &bit)
    {
        return binary[pos] == bit + '0';
    }

    int to_decimal() { return std::stoi(binary, 0, 2); }
};

struct Diagnostic
{
    std::vector<Binary> report;
    int binary_size;

    Diagnostic(std::vector<std::string> r)
    {
        binary_size = r[0].size();
        for (std::string s : r)
        {
            report.push_back(Binary(s));
        }
    }

    int calculate_generator_rating()
    {
        std::vector<Binary> possible(report);
        int pos{};
        while (pos < binary_size && possible.size() > 1)
        {
            std::pair<int, int> bits = most_least_bit(pos, possible);
            int bit_criteria = (bits.first == bits.second) ? 1 : bits.first;
            int i{};
            while (i < possible.size())
            {
                if (!possible[i].valid_bit_criteria(pos, bit_criteria))
                {
                    possible.erase(possible.begin() + i);
                }
                else
                {
                    i++;
                }
            }
            pos++;
        }
        return possible.front().to_decimal();
    }

    int calculate_scrubber_rating()
    {
        std::vector<Binary> possible(report);
        int pos{};
        while (pos < binary_size && possible.size() > 1)
        {
            std::pair<int, int> bits = most_least_bit(pos, possible);
            int bit_criteria =
                (bits.first == bits.second) ? 0 : bits.second; // change
            int i{};
            while (i < possible.size())
            {
                if (!possible[i].valid_bit_criteria(pos, bit_criteria))
                {
                    possible.erase(possible.begin() + i);
                }
                else
                {
                    i++;
                }
            }
            pos++;
        }
        return possible.front().to_decimal();
    }

    std::pair<int, int> most_least_bit(const int &pos,
                                       const std::vector<Binary> &data)
    {
        int count{};
        for (Binary b : data)
        {
            count += (b.binary[pos] ^ '0') ? 1 : -1;
        }
        if (count == 0)
        {
            return {0, 0};
        }
        if (count < 0)
        {
            return std::make_pair(0, 1);
        }
        return std::make_pair(1, 0);
    }
};

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

int main()
{
    std::vector<std::string> lines = input("sample.txt");
    Diagnostic report(lines);
    int generator = report.calculate_generator_rating();
    int scrubber = report.calculate_scrubber_rating();
    std::cout << generator * scrubber << '\n';
    return 0;
}