#include <iostream>

// stores the start and end time for elf assignments
struct Assignment
{
    unsigned int start;
    unsigned int end;
};

// checks if assignments are contained within one another
bool fully_contains(const Assignment &a, const Assignment &b)
{
    bool is_a_in_b = a.start >= b.start && a.end <= b.end;
    bool is_b_in_a = b.start >= a.start && b.end <= a.end;
    return is_a_in_b || is_b_in_a;
}

int main()
{
    freopen("actual.txt", "r", stdin);
    int count = 0;
    Assignment first, second;
    while (scanf("%u-%u,%u-%u", &first.start, &first.end, &second.start,
                 &second.end) != EOF)
    {
        if (fully_contains(first, second)) count++;
    }
    std::cout << count << '\n';
    return 0;
}