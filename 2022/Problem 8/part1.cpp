#include <iostream>
#include <string>
#include <vector>

struct Tree
{
    short m_size;
    bool m_visible;

    Tree(short size = 0, bool visible = false)
        : m_size{size}, m_visible{visible}
    {
    }
};

using TreeMap = std::vector<std::vector<Tree>>;

bool is_visible(const int &x, const int &y, const TreeMap &map)
{
    // boundary trees are always visible
    if (x == 0 || y == 0 || x == map.size() - 1 || y == map.size() - 1)
    {
        return true;
    }

    // check up
    bool up = true;
    for (int i = x - 1; i >= 0; i--)
    {
        if (map[i][y].m_size >= map[x][y].m_size)
        {
            up = false;
        }
    }

    // check down
    bool down = true;
    for (int i = x + 1; i < map.size(); i++)
    {
        if (map[i][y].m_size >= map[x][y].m_size)
        {
            down = false;
        }
    }

    // check left
    bool left = true;
    for (int i = y - 1; i >= 0; i--)
    {
        if (map[x][i].m_size >= map[x][y].m_size)
        {
            left = false;
        }
    }

    // check right
    bool right = true;
    for (int i = y + 1; i < map[x].size(); i++)
    {
        if (map[x][i].m_size >= map[x][y].m_size)
        {
            right = false;
        }
    }
    return up || down || left || right;
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
            map[i][j].m_visible = is_visible(i, j, map);
        }
    }
}

int main()
{
    freopen("actual.txt", "r", stdin);

    // constructing the tree map from input
    TreeMap map{};
    construct_tree_map(map);

    // going through each tree and checking if they are visible
    int count{};
    for (std::vector<Tree> trees : map)
    {
        for (Tree x : trees)
        {
            if (x.m_visible) count++;
        }
    }
    std::cout << count << '\n';

    return 0;
}