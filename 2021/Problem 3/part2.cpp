#include "helpers.h"
#include <algorithm>
#include <numeric>
#include <utility>

// in the context for this problem, a binary is represented by a string
using Binary = std::string;

// for part 2, bit criteria is utilized more thus functions were configured to
// use this as a parameter.
enum Criteria
{
    LEAST_COMMON,
    MOST_COMMON
};

/**
 * @brief Finds the common bit, either most or least, in the corresponding
 * position for all binary numbers in the list.
 *
 * @throw std::logic_error This function does not take into account equal amount
 * of bits.
 * @param pos Bit position to check in binaries.
 * @param binaries A list of binary numbers of the same length.
 * @param criteria Determines if most common bit or least common bit is
 * returned.
 * @return char 0 or 1.
 */
char common_bit(const int &pos, const std::vector<Binary> &binaries,
                const Criteria &criteria)
{
    // by taking the sum of all bits, treating 0s as -1 and 1s as 1, most
    // common bit would be the bool value of (sum > 0).
    int sum = std::accumulate(binaries.begin(), binaries.end(), 0,
                              [&](int sum, Binary b)
                              { return sum + ((b[pos] - '0') ? 1 : -1); });

    if (sum == 0)
    {
        throw std::logic_error("Equal number of 0s and 1s\n");
    }

    char most_common_bit = int(sum > 0) + '0';
    return (criteria) ? most_common_bit : most_common_bit ^ 1;
}

/**
 * @brief Finds last binary number in list of binaries that matches bit
 * criteria.
 *
 * @param binaries A list of binaries of equal length.
 * @param fallback Bit to use when there are equal number of 0s and 1s.
 * @param criteria Determines which bit to return, most common or least common.
 * @return Binary A binary number that matches bit criteria.
 */
Binary find_rating(std::vector<Binary> binaries, const char &fallback,
                   const Criteria &criteria)
{
    // removing candidates, based on bit criteria for current position, until
    // there is only one remaining.
    for (size_t i = 0; binaries.size() > 1; i++)
    {
        // finding the bit criteria for current position
        char common;
        try
        {
            common = common_bit(i, binaries, criteria);
        }
        catch (const std::logic_error &equal_bits)
        {
            common = fallback;
        }

        // removing numbers that don't match the bit criteria for position.
        auto discard = std::remove_if(binaries.begin(), binaries.end(),
                                      [&](Binary b) { return b[i] != common; });
        binaries.erase(discard, binaries.end());
    }
    return binaries.front();
}

/**
 * @brief Calculates the oxygen generator rating and CO2 scrubber rating from a
 * list of binaries and returns them in binary format.
 *
 * @param binaries A list of binary nunbers of the same length.
 * @return Pair with oxygen generator rating as first, CO2 scrubber rating as
 * second.
 */
std::pair<Binary, Binary>
generator_scrubber(const std::vector<Binary> &binaries)
{
    Binary generator = find_rating(binaries, '1', MOST_COMMON);
    Binary scrubber = find_rating(binaries, '0', LEAST_COMMON);
    return std::make_pair(generator, scrubber);
}

int main()
{
    std::vector<std::string> lines = get_lines("sample.txt");

    std::pair<Binary, Binary> ratings = generator_scrubber(lines);
    int generator = std::stoi(ratings.first, 0, 2);
    int scrubber = std::stoi(ratings.second, 0, 2);
    std::cout << generator * scrubber << '\n';

    return 0;
}