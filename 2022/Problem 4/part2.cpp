#include <iostream>

// stores the start and end time for elf assignments
struct Assignment
{
    unsigned int start;
    unsigned int end;
};

// checks if assignments overlap
bool overlap(const Assignment &a, const Assignment &b)
{
    if (a.start <= b.start) return b.start <= a.end;
    return a.start <= b.end;
}

int main()
{
    freopen("actual.txt", "r", stdin);
    int count = 0;
    Assignment first, second;
    while (scanf("%u-%u,%u-%u", &first.start, &first.end, &second.start,
                 &second.end) != EOF)
    {
        if (overlap(first, second)) count++;
    }
    std::cout << count << '\n';
    return 0;
}