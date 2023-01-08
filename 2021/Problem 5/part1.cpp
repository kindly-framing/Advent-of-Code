#include "helpers.h"
#include "vent.h"

Vent::Line::Line(std::string str)
{
    if (!sscanf(str.c_str(), "%d,%d -> %d,%d", &start.first, &start.second,
                &end.first, &end.second)) {
        throw std::invalid_argument("Lines are not formatted correctly\n");
    }
    if (start > end) {
        std::swap(start, end);
    }
}

std::vector<Position> Vent::Line::convert_to_positions()
{
    if (start.first != end.first && start.second != end.second) {
        throw std::logic_error("Diagonals are not considered for part 1!\n");
    }
    if (start.first != end.first) {
        return horizontal_to_positions();
    }
    return vertical_to_positions();
}

std::vector<Position> Vent::Line::horizontal_to_positions()
{
    std::vector<Position> positions;
    for (int i = start.first; i <= end.first; i++) {
        positions.push_back(Position(i, end.second));
    }
    return positions;
}

std::vector<Position> Vent::Line::vertical_to_positions()
{
    std::vector<Position> positions;
    for (int i = start.second; i <= end.second; i++) {
        positions.push_back(Position(end.first, i));
    }
    return positions;
}

Vent::Vent(std::vector<std::string> data)
{
    for (auto &&position : extract_positions(data)) {
        m_graph[position]++;
    }
    invariant();
}

std::vector<Position>
Vent::extract_positions(const std::vector<std::string> &data)
{
    std::vector<Position> positions;
    for (auto &&str : data) {
        std::vector<Position> converted;
        try {
            converted = Line(str).convert_to_positions();
        }
        catch (const std::logic_error &diagonal) {
            converted = {};
        }
        positions.insert(positions.end(), converted.begin(), converted.end());
    }
    return positions;
}

int Vent::count_intersections(const int &n)
{
    invariant();
    return std::count_if(m_graph.begin(), m_graph.end(),
                         [&](auto elem) { return elem.second >= n; });
}

int main()
{
    std::vector<std::string> lines = get_lines("sample.txt");
    Vent vent(lines);
    std::cout << vent.count_intersections(2) << '\n';
    return 0;
}