#include <iostream>
#include <string>
#include <vector>

using Crates = std::vector<char>;
using Stack = std::vector<Crates>;

// stack of crates from problem
Stack crates = {{'R', 'G', 'H', 'Q', 'S', 'B', 'T', 'N'},
                {'H', 'S', 'F', 'D', 'P', 'Z', 'J'},
                {'Z', 'H', 'V'},
                {'M', 'Z', 'J', 'F', 'G', 'H'},
                {'T', 'Z', 'C', 'D', 'L', 'M', 'S', 'R'},
                {'M', 'T', 'W', 'V', 'H', 'Z', 'J'},
                {'T', 'F', 'P', 'L', 'Z'},
                {'Q', 'V', 'W', 'S'},
                {'W', 'H', 'L', 'M', 'T', 'D', 'N', 'C'}};

// executes the given step on stack of crates
void execute_step(const int &n, const int &origin, const int &dest)
{
    // for n times, moves crate from origin stack to destination stack
    for (int i = 0; i < n; i++)
    {
        char temp = crates[origin - 1].back();
        crates[origin - 1].pop_back();
        crates[dest - 1].push_back(temp);
    }
}

int main()
{
    freopen("actual.txt", "r", stdin);

    // executing the procedure on stack of crates
    int count, origin, dest;
    while (scanf("move %d from %d to %d\n", &count, &origin, &dest) != EOF)
    {
        execute_step(count, origin, dest);
    }

    // checking the last crate in each stack to get answer
    std::string ans;
    for (Crates a : crates)
    {
        ans.push_back(a.back());
    }
    std::cout << ans << '\n';

    return 0;
}