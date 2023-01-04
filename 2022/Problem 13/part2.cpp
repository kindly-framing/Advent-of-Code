#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <variant>
#include <vector>

struct Packet_Data {
    std::variant<int, std::vector<Packet_Data>> m_val;
    Packet_Data(std::variant<int, std::vector<Packet_Data>> val = {})
        : m_val(val)
    {
    }
};

struct List_Parser {
    static std::vector<Packet_Data> parse(const std::string &str)
    {
        std::queue<char> queue = string_to_queue(str);
        std::vector<Packet_Data> list = parse_list(queue);
        return list;
    }

    static std::queue<char> string_to_queue(const std::string &str)
    {
        std::queue<char> queue;
        for (char ch : str) {
            queue.push(ch);
        }
        return queue;
    }

    static int parse_int(std::queue<char> &data)
    {
        std::string num;
        while (isdigit(data.front())) {
            num.push_back(data.front());
            data.pop();
        }
        return std::stoi(num);
    }

    static std::vector<Packet_Data> parse_list(std::queue<char> &data)
    {
        std::vector<Packet_Data> list;
        data.pop(); // remves the '[' from the queue
        while (data.front() != ']') {
            Packet_Data n = parse_element(data);
            list.push_back(n);
            if (data.front() == ',') {
                data.pop();
            }
        }
        data.pop(); // removes the ']' from the queue
        return list;
    }

    static Packet_Data parse_element(std::queue<char> &data)
    {
        char next = data.front();
        if (isdigit(next)) {
            return Packet_Data(parse_int(data));
        }
        else if (next == '[') {
            return Packet_Data(parse_list(data));
        }
        else {
            throw std::invalid_argument("Wrong format");
        }
    }
};

struct Packets {
    // implementation of sign bit
    template <typename T> static int sgn(T val)
    {
        return (T(0) < val) - (val < T(0));
    }

    static bool less_than(std::vector<Packet_Data> first,
                          std::vector<Packet_Data> second)
    {
        return compare_lists(first, second) <= 0;
    }

    static std::string list_to_string(const std::vector<Packet_Data> &list)
    {
        std::vector<std::string> as_strings;
        for (Packet_Data packet : list) {
            std::string s;
            if (std::get_if<1>(&packet.m_val)) {
                s = list_to_string(std::get<1>(packet.m_val));
            }
            else {
                s = std::to_string(std::get<0>(packet.m_val));
            }
            as_strings.push_back(s);
        }

        std::string res = "[";
        for (std::string str : as_strings) {
            res.append(str + ",");
        }
        if (res != "[") {
            return res.substr(0, res.size() - 1) + "]";
        }
        return res + "]";
    }

    static int compare_lists(const std::vector<Packet_Data> &left,
                             const std::vector<Packet_Data> &right)
    {
        int max_index = std::min(left.size(), right.size());
        for (int i = 0; i < max_index; i++) {
            Packet_Data pd1 = left[i];
            Packet_Data pd2 = right[i];
            int diff = compare_elements(pd1, pd2);
            if (diff < 0) {
                return -1;
            }
            else if (diff > 0) {
                return 1;
            }
        }
        return sgn(int(left.size() - right.size()));
    }

    static int compare_elements(const Packet_Data &first,
                                const Packet_Data &second)
    {
        using std::get;
        using std::get_if;
        // both are integers
        if (get_if<0>(&first.m_val) && get_if<0>(&second.m_val)) {
            return sgn(get<0>(first.m_val) - get<0>(second.m_val));
        }
        // both are lists
        if (get_if<1>(&first.m_val) && get_if<1>(&second.m_val)) {
            return compare_lists(get<1>(first.m_val), get<1>(second.m_val));
        }
        // mixed types: int, list
        if (get_if<0>(&first.m_val) && get_if<1>(&second.m_val)) {
            return compare_lists({Packet_Data(get<0>(first.m_val))},
                                 get<1>(second.m_val));
        }
        // mixed types: list, int
        if (get_if<1>(&first.m_val) && get_if<0>(&second.m_val)) {
            return compare_lists(get<1>(first.m_val),
                                 {Packet_Data(get<0>(second.m_val))});
        }
        throw std::invalid_argument("not valid list");
    }
};

// converts file into a vector of strings removing empty lines
std::vector<std::string> input(const char *file)
{
    freopen(file, "r", stdin);
    std::vector<std::string> result;
    std::string line;
    while (std::getline(std::cin, line)) {
        if (!line.empty()) {
            result.push_back(line);
        }
    }
    return result;
}

int main()
{
    std::vector<std::string> data = input("actual.txt");

    std::vector<std::vector<Packet_Data>> packets = {};
    packets.push_back(List_Parser::parse("[[2]]"));
    packets.push_back(List_Parser::parse("[[6]]"));
    for (std::string packet : data) {
        packets.push_back(List_Parser::parse(packet));
    }

    std::sort(packets.begin(), packets.end(), Packets::less_than);

    int d1_index{};
    int d2_index{};
    for (int i = 0; i < packets.size(); i++) {
        if (Packets::list_to_string(packets[i]) == "[[2]]") {
            d1_index = i + 1;
        }
        else if (Packets::list_to_string(packets[i]) == "[[6]]") {
            d2_index = i + 1;
        }
    }

    std::cout << d1_index * d2_index << '\n';
    return 0;
}