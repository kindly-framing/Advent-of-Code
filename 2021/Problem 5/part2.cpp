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
        return diagonal_to_positions();
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

std::vector<Position> Vent::Line::diagonal_to_positions()
{
    std::vector<Position> positions;
    int x_step = (end.first - start.first > 0) ? 1 : -1;
    int y_step = (end.second - start.second > 0) ? 1 : -1;
    Position p(start);
    while (p <= end) {
        positions.push_back(p);
        p.first += x_step;
        p.second += y_step;
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
        std::vector<Position> converted = Line(str).convert_to_positions();
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