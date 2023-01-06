#include "helpers.h"
#include <algorithm>
#include <numeric>

/**
 * @brief Counts the number of times an integer is greater than the previous
 * integer in a list.
 *
 * @param report A list of integers.
 * @return Total count of increases from previous integer.
 */
int count_increases(const std::vector<int> &report)
{
    int count{};
    for (int i = 1; i < report.size(); i++)
    {
        if (report[i] > report[i - 1])
        {
            count++;
        }
    }
    return count;
}

/**
 * @brief Converts a list of string representations of numbers to a list of
 * integers, using stoi().
 *
 * @param nums List of string representations of integers.
 * @return Converted list to integers.
 */
std::vector<int> convert_to_numbers(const std::vector<std::string> &nums)
{
    std::vector<int> numbers;
    std::transform(nums.begin(), nums.end(), std::back_inserter(numbers),
                   [&](std::string s) { return std::stoi(s); });
    return numbers;
}

/**
 * @brief Converts a list of integers to a list of sliding window sums of given
 * size.
 *
 * @throw std::logic_error Window size cannot be greater than report size.
 * @param report A list of integers.
 * @param size The window size for sum.
 * @return A list of the window sums of given size of the list of integers.
 */
std::vector<int> convert_to_window_sum(const std::vector<int> &report,
                                       const int &size)
{
    if (size > report.size() || size <= 0)
    {
        throw std::logic_error("Invalid window size: " + std::to_string(size));
    }

    std::vector<int> window_sums;
    for (auto it = report.begin(); it + size - 1 != report.end(); it++)
    {
        window_sums.push_back(std::accumulate(it, it + size, 0));
    }
    return window_sums;
}

int main()
{
    std::vector<std::string> input = get_lines("sample.txt");

    // part 1 - only the depth measurements
    std::vector<int> report = convert_to_numbers(input);
    std::cout << count_increases(report) << std::endl;

    // part 2 - three-measurement sliding window
    std::vector<int> windows = convert_to_window_sum(report, 3);
    std::cout << count_increases(windows) << std::endl;

    return 0;
}