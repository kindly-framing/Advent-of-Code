#include <iostream>
#include <string>
#include <vector>

struct Tree
{
    short m_size;
    long m_score;

    Tree(short size = 0, long score = 0) : m_size{size}, m_score{score} {}
};

using TreeMap = std::vector<std::vector<Tree>>;

long calculate_score(const int &x, const int &y, const TreeMap &map)
{
    // check up
    long viewing_up{};
    for (int i = x - 1; i >= 0; i--)
    {
        viewing_up++;
        if (map[i][y].m_size >= map[x][y].m_size)
        {
            break;
        }
    }

    // check down
    long viewing_down{};
    for (int i = x + 1; i < map.size(); i++)
    {
        viewing_down++;
        if (map[i][y].m_size >= map[x][y].m_size)
        {
            break;
        }
    }

    // check left
    long viewing_left{};
    for (int i = y - 1; i >= 0; i--)
    {
        viewing_left++;
        if (map[x][i].m_size >= map[x][y].m_size)
        {
            break;
        }
    }

    // check right
    long viewing_right{};
    for (int i = y + 1; i < map[x].size(); i++)
    {
        viewing_right++;
        if (map[x][i].m_size >= map[x][y].m_size)
        {
            break;
        }
    }
    return viewing_up * viewing_down * viewing_left * viewing_right;
}

void construct_tree_map(TreeMap &map)
{
    std::string in;
    int row = 0;
    while (std::getline(std::cin, in))
    {
        map.push_back(std::vector<Tree>());
        for (char c : in)
        {
            map[row].push_back(Tree(c - '0'));
        }
        row++;
    }

    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            map[i][j].m_score = calculate_score(i, j, map);
        }
    }
}

int main()
{
    freopen("actual.txt", "r", stdin);

    // constructing the tree map from input
    TreeMap map;
    construct_tree_map(map);

    // going through each tree and finding tree with highest scenic score
    Tree max(0, 0);
    for (std::vector<Tree> trees : map)
    {
        for (Tree x : trees)
        {
            if (x.m_score > max.m_score)
            {
                max = x;
            }
        }
    }
    std::cout << max.m_score << '\n';

    return 0;
}