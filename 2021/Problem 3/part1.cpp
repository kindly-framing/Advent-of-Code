#include "helpers.h"
#include <numeric>
#include <utility>

// in the context for this problem, a binary is represented by a string
using Binary = std::string;

/**
 * @brief Finds the most common bit in the corresponding position for all binary
 * numbers in the list.
 *
 * @throw std::logic_error This function does not take into account no common
 * bit.
 * @param pos Position to check in binaries.
 * @param binaries A list of binary numbers of the same length.
 * @return char 0 or 1.
 */
char most_common_bit(const int &pos, const std::vector<Binary> &binaries)
{
    // by taking the sum of all bits, treating 0s as -1 and 1s as itself, the
    // most common bit would be if the sum is negative(0) or positve(1).
    int sum = std::accumulate(binaries.begin(), binaries.end(), 0,
                              [&](int sum, Binary b)
                              { return sum + ((b[pos] - '0') ? 1 : -1); });
    if (sum == 0)
    {
        throw std::logic_error("There is no fallback for no common bit.\n");
    }
    return (sum < 0) ? '0' : '1';
}

/**
 * @brief Calculates the gamma and epsilon of a list of binaries and returns
 * them in binary format.
 *
 * @param binaries A list of binary numbers of the same length.
 * @return std::pair<std::string, std::string>
 */
std::pair<Binary, Binary> gamma_epsilon(const std::vector<Binary> &binaries)
{
    Binary gamma;
    Binary epsilon;
    for (int i = 0; i < binaries[i].size(); i++)
    {
        char most_common = most_common_bit(i, binaries);
        gamma += most_common;
        epsilon += most_common ^ 1; // swtiches '0'->'1' and '1'->'0'
    }
    return {gamma, epsilon};
}

int main()
{
    std::vector<std::string> binaries = get_lines("sample.txt");

    std::pair<std::string, std::string> rates = gamma_epsilon(binaries);
    int gamma = std::stoi(rates.first, 0, 2);
    int epsilon = std::stoi(rates.second, 0, 2);
    std::cout << gamma * epsilon << '\n';

    return 0;
}