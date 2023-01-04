#include <cstring>
#include <iostream>
#include <string>

const int TOTAL_ITEMS = 256;
using Item = int;
using Sack = std::string;

// gets the priority for the item (a-z 1-26 || A-Z 27-52)
int priority(const Item &a)
{
    if (isupper(a)) return a - 38;
    return a - 96;
}

// fills an array with frequencies of each item in sack
void count_freq(const Sack &sack, int arr[TOTAL_ITEMS])
{
    for (Item a : sack)
    {
        arr[a]++;
    }
}

// finds the common item between the three elf sacks
Item find_common(const Sack &a, const Sack &b, const Sack &c)
{
    // generating hash maps for item frequencies in each elf sack
    Item a_freq[TOTAL_ITEMS] = {0};
    Item b_freq[TOTAL_ITEMS] = {0};
    Item c_freq[TOTAL_ITEMS] = {0};
    count_freq(a, a_freq);
    count_freq(b, b_freq);
    count_freq(c, c_freq);

    // finding the item that appears only once in all three sacks
    for (int i = 0; i < a.size(); i++)
    {
        if (a_freq[a[i]] && b_freq[a[i]] && c_freq[a[i]]) return a[i];
    }
}

int main()
{
    freopen("actual.txt", "r", stdin);
    int sum{};
    while (std::cin.peek() != EOF)
    {
        Sack elf1, elf2, elf3;
        std::getline(std::cin, elf1);
        std::getline(std::cin, elf2);
        std::getline(std::cin, elf3);
        sum += priority(find_common(elf1, elf2, elf3));
    }
    std::cout << sum << '\n';
    return 0;
}