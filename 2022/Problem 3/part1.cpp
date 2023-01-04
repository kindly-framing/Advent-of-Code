#include <algorithm>
#include <iostream>
#include <string>

// gets the priority for the item
int priority(const int &item)
{
    // a-z 1-26 || A-Z 27-52
    if (isupper(item)) return item - 38;
    return item - 96;
}

// finds the common item between compartments
char find_common(const std::string &a, const std::string &b)
{
    for (char c : a)
    {
        if (std::find(b.begin(), b.end(), c) != b.end()) return c;
    }
    return 0;
}

int main()
{
    freopen("actual.txt", "r", stdin);

    int sum{};
    std::string rucksack;
    while (std::getline(std::cin, rucksack))
    {
        std::string first = rucksack.substr(0, rucksack.size() / 2);
        std::string second = rucksack.substr(rucksack.size() / 2);
        sum += priority(find_common(first, second));
    }
    std::cout << sum << '\n';
    return 0;
}