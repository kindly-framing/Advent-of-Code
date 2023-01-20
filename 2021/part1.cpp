#include "helpers.h"

using namespace std;

int main()
{
    vector<string> lines = get_lines("sample.txt");

    map<string, vector<string>> caves;
    for (auto &&line : lines) {
        int split = line.find('-');
        string source_label = line.substr(0, split);
        string connected_label = line.substr(split + 1);
        caves[source_label].push_back(connected_label);
        caves[connected_label].push_back(source_label);
    }

    for (auto &&elem : caves) {
        std::cout << elem.first << ' ';
        display(elem.second);
    }

    return 0;
}