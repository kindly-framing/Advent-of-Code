#include <iostream>
#include <set>
#include <string>

// find the index of the end of the packet marker in data string.
int find_start_of_packet_marker(const std::string &data, const int &len)
{
    for (size_t i = 0; i + len < data.size(); i++)
    {
        // using set to remove duplicates and compare set length with len
        std::set<char> marker(data.begin() + i, data.begin() + i + len);
        if (marker.size() == len)
        {
            // the start of the packet marker would be the end of the string
            return i + len;
        }
    }
}

int main()
{
    freopen("actual.txt", "r", stdin);

    // reads datastream and finds the start of the packet marker
    std::string datastream;
    std::getline(std::cin, datastream);
    std::cout << find_start_of_packet_marker(datastream, 4) << '\n';

    return 0;
}