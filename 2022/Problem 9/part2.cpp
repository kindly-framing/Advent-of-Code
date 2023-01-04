#include <iostream>
#include <set>
#include <utility>
#include <vector>

int main()
{
    freopen("actual.txt", "r", stdin);

    std::vector<std::pair<int, int>> rope(10, std::make_pair(0, 0));
    std::set<std::pair<int, int>> visited;
    visited.insert(rope[0]);

    char dir;
    int steps;
    while (scanf("%c %d\n", &dir, &steps) != EOF)
    {
        for (int i = 0; i < steps; i++)
        {
            // move head of the rope
            switch (dir)
            {
            case 'U': rope[0].second++; break;
            case 'D': rope[0].second--; break;
            case 'L': rope[0].first--; break;
            case 'R': rope[0].first++; break;
            }

            // move rest of rope
            for (int i = 0; i + 1 < rope.size(); i++)
            {
                // determine if head and tail are touching
                int dx = rope[i].first - rope[i + 1].first;
                int dy = rope[i].second - rope[i + 1].second;
                bool not_adjacent = std::abs(dx) > 1 || std::abs(dy) > 1;

                // update tail and insert position into visited set
                if (not_adjacent)
                {
                    rope[i + 1].first += (dx == 0) ? 0 : dx / std::abs(dx);
                    rope[i + 1].second += (dy == 0) ? 0 : dy / std::abs(dy);
                    if (i + 1 == rope.size() - 1)
                    {
                        visited.insert(rope[i + 1]);
                    }
                }
            }
        }
    }

    std::cout << visited.size() << '\n';

    return 0;
}