#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <vector>

struct Monkey
{
    std::vector<long long> items;
    std::function<long long(const long long)> operation;
    int test;
    int monkey_true;
    int monkey_false;
    long long inspections;

    Monkey(std::vector<long long> i,
           std::function<long long(const long long)> op, int t, int m_t,
           int m_f)
        : items(i), operation(op), test(t), monkey_true(m_t),
          monkey_false(m_f), inspections{}
    {
    }
};

void input_monkeys(std::vector<Monkey> &v)
{
    v.push_back(Monkey(
        {80}, [](long long x) { return x * 5; }, 2, 4, 3));
    v.push_back(Monkey(
        {75, 83, 74}, [](long long x) { return x + 7; }, 7, 5, 6));
    v.push_back(Monkey(
        {86, 67, 61, 96, 52, 63, 73}, [](long long x) { return x + 5; }, 3, 7,
        0));
    v.push_back(Monkey(
        {85, 83, 55, 85, 57, 70, 85, 52}, [](long long x) { return x + 8; }, 17,
        1, 5));
    v.push_back(Monkey(
        {67, 75, 91, 72, 89}, [](long long x) { return x + 4; }, 11, 3, 1));
    v.push_back(Monkey(
        {66, 64, 68, 92, 68, 77}, [](long long x) { return x * 2; }, 19, 6, 2));
    v.push_back(Monkey(
        {97, 94, 79, 88}, [](long long x) { return x * x; }, 5, 2, 7));
    v.push_back(Monkey(
        {77, 85}, [](long long x) { return x + 6; }, 13, 4, 0));
}

long long monkey_business(const std::vector<Monkey> &v)
{
    long long max1{};
    for (Monkey x : v)
    {
        max1 = std::max(max1, x.inspections);
    }

    long long max2{};
    for (Monkey x : v)
    {
        if (x.inspections != max1) max2 = std::max(max2, x.inspections);
    }

    return max1 * max2;
}

long long lcm(const std::vector<Monkey> &v)
{
    long long lcm = 1;
    for (Monkey n : v)
    {
        lcm *= n.test;
    }
    return lcm;
}

int main()
{
    std::vector<Monkey> monkeys;
    input_monkeys(monkeys);
    long long modulo = lcm(monkeys);

    for (int round = 0; round < 10000; round++)
    {
        for (Monkey &x : monkeys)
        {
            for (int i = 0; i < x.items.size(); i++)
            {
                x.inspections++;
                x.items[i] = x.operation(x.items[i]);
                x.items[i] %= modulo;
                if (x.items[i] % x.test == 0)
                {
                    monkeys[x.monkey_true].items.push_back(x.items[i]);
                }
                else
                {
                    monkeys[x.monkey_false].items.push_back(x.items[i]);
                }

                x.items.erase(x.items.begin() + i);
                i--;
            }
        }
    }

    std::cout << monkey_business(monkeys) << '\n';
    return 0;
}