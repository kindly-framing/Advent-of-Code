#include <iostream>
#include <set>
#include <utility>

int main()
{
    freopen("actual.txt", "r", stdin);

    std::pair<int, int> head(0, 0);
    std::pair<int, int> tail(0, 0);
    std::set<std::pair<int, int>> visited;
    visited.insert(tail);

    char dir;
    int steps;
    while (scanf("%c %d\n", &dir, &steps) != EOF)
    {
        std::cout << dir << " " << steps << '\n';
        for (int i = 0; i < steps; i++)
        {
            // move head
            switch (dir)
            {
            case 'U': head.second++; break;
            case 'D': head.second--; break;
            case 'L': head.first--; break;
            case 'R': head.first++; break;
            }

            // determine if head and tail are touching
            int dx = head.first - tail.first;
            int dy = head.second - tail.second;
            bool not_adjacent = std::abs(dx) > 1 || std::abs(dy) > 1;

            // update tail and insert position into visited set
            if (not_adjacent)
            {
                tail.first += (dx == 0) ? 0 : dx / std::abs(dx);
                tail.second += (dy == 0) ? 0 : dy / std::abs(dy);
                visited.insert(tail);
            }
        }
    }

    std::cout << visited.size() << '\n';

    return 0;
}