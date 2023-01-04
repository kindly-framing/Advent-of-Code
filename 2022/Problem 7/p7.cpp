#include <iostream>
#include <string>
#include <vector>

class Directory
{
  public:
    std::string m_name;
    long m_size;
    std::vector<Directory *> m_directories;
    Directory *m_parent;

    Directory(std::string name = "", Directory *parent = nullptr)
        : m_name(name), m_size{}, m_directories{}, m_parent(parent)
    {
    }

    int find_directory(std::string name)
    {
        for (int i = 0; i < m_directories.size(); i++)
        {
            if (m_directories[i]->m_name == name) return i;
        }
        return -1;
    }

    void update_sizes()
    {
        if (this != nullptr)
        {
            for (auto dir : this->m_directories)
            {
                dir->update_sizes();
                this->m_size += dir->m_size;
            }
        }
    }

    void sum(const int &limit, long &sum)
    {
        for (auto dict : this->m_directories)
        {
            dict->sum(limit, sum);
        }
        if (this->m_size <= limit)
        {
            sum += this->m_size;
        }
    }

    void min(const long &leftover, long &temp)
    {
        if (temp == 0)
        {
            temp = __LONG_MAX__;
        }

        for (auto dict : this->m_directories)
        {

            dict->min(leftover, temp);
        }

        if (this->m_size >= leftover && this->m_size < temp)
        {
            temp = this->m_size;
        }
    }
};

void construct_file_system(Directory **root)
{
    std::string line;
    Directory *prev, *current;
    while (std::getline(std::cin, line))
    {
        std::string cmd = line.substr(0, 4);

        // initial initialization
        if (line == "$ cd /")
        {
            *root = new Directory("/");
            current = *root;
        }
        // move back from current directory
        else if (line == "$ cd ..")
        {
            if (prev->m_parent == nullptr)
            {
                current = prev;
            }
            else
            {
                current = current->m_parent;
                prev = prev->m_parent;
            }
        }
        // populating files in directory
        else if (cmd == "$ ls")
        {
            std::string file;
            while (std::cin.peek() != '$' && std::cin.peek() != EOF)
            {
                std::getline(std::cin, file);

                // add directory to current directory
                if (file[0] == 'd')
                {
                    current->m_directories.push_back(
                        new Directory(file.substr(4), current));
                }
                // add file to current directory's size
                else
                {
                    current->m_size +=
                        std::stoi(file.substr(0, file.find(' ')));
                }
            }
        }
        // moving into directory
        else
        {
            prev = current;
            current = prev->m_directories[prev->find_directory(line.substr(5))];
        }
    }
}

int main()
{
    freopen("actual.txt", "r", stdin);

    // constructs the file system from input
    Directory *root;
    construct_file_system(&root);
    root->update_sizes();

    // find the sum of all dirs with sizes under limit
    long sum{};
    root->sum(100000, sum);
    std::cout << "part1: " << sum << '\n';

    // finds minimum directory to delete
    long leftover = 30000000 - (70000000 - root->m_size);
    long size{};
    root->min(leftover, size);
    std::cout << "part2: " << size << '\n';

    return 0;
}
