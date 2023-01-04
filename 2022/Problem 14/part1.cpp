#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

enum Obstacles { ROCK = '#', AIR = '.', SAND_SOURCE = '+', SAND = 'o' };

using Point = std::pair<int, int>;

struct Line {
    Point start;
    Point end;
    Line(Point _a, Point _b)
    {
        // sorting the points to simplify logic for converting a line to points
        if (_a == _b) {
            throw std::invalid_argument("Points can't be the same!");
        }
        else if (_a < _b) {
            start = _a;
            end = _b;
        }
        else {
            start = _b;
            end = _a;
        }
    }

    std::vector<Point> line_to_points()
    {
        std::vector<Point> points;

        // since the two points are sorted, no need to handle case start > end
        if (start.first - end.first != 0) {
            for (int i = start.first; i <= end.first; i++) {
                points.push_back({i, start.second});
            }
        }
        if (start.second - end.second != 0) {
            for (int i = start.second; i <= end.second; i++) {
                points.push_back({start.first, i});
            }
        }

        return points;
    }

    static std::vector<Line> parse(const std::vector<std::string> &points)
    {
        std::vector<Line> lines;

        for (std::string p : points) {
            std::vector<Point> points = parse_points(p);
            for (int i = 0; i + 1 < points.size(); i++) {
                lines.push_back(Line(points[i], points[i + 1]));
            }
        }

        return lines;
    }

    static std::vector<Point> parse_points(std::string data)
    {
        std::vector<Point> points;

        size_t pos = 0;
        Point p;
        std::string point;
        while ((pos = data.find(" -> ")) != std::string::npos) {
            point = data.substr(0, pos);
            p = {std::stoi(point),
                 std::stoi(point.substr(point.find(',') + 1))};
            points.push_back(p);
            data.erase(0, pos + 4);
        }

        p = {std::stoi(data), std::stoi(data.substr(point.find(',') + 1))};
        points.push_back(p);
        return points;
    }

    void display()
    {
        std::cout << start.first << ',' << start.second;
        std::cout << " -> " << end.first << ',' << end.second << '\n';
    }
};

struct Sand {
    Point fall(const Point &source, const std::vector<std::vector<char>> &cave)
    {
        // code
    }
};

struct Cave {
    std::vector<std::vector<char>> system;
    Point sand_source;
    int settled_sand;

    Cave(std::vector<std::string> data) : settled_sand{}
    {
        initialize_system(data);
        std::vector<Line> rock_structures = Line::parse(data);
        construct_cave(rock_structures);
    }

    void initialize_system(const std::vector<std::string> &data) {}

    void construct_cave(const std::vector<Line> &structures) {}

    bool drop_sand() {}

    void display()
    {
        for (auto &&row : system) {
            for (auto &&i : row) {
                std::cout << i << ' ';
            }
            std::cout << '\n';
        }
    }
};

std::vector<std::string> input(const char *file)
{
    std::ifstream in(file);
    if (!in.is_open()) {
        throw std::invalid_argument("can't open file: " + std::string(file));
    }

    std::vector<std::string> data;
    std::string line;
    while (std::getline(in, line)) {
        data.push_back(line);
    }
    return data;
}

int main()
{
    std::vector<std::string> data = input("sample.txt");

    std::vector<Line> lines = Line::parse(data);
    for (auto &elem : lines) {
        elem.display();
        std::cout << "\tPoints in between:\n";
        for (auto point : elem.line_to_points()) {
            std::cout << "\t" << point.first << ',' << point.second << '\n';
        }
        std::cout << '\n';
    }
    return 0;
}