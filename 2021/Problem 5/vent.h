#ifndef VENT_H
#define VENT_H

#include "helpers.h"
#include <algorithm>
#include <cassert>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

// rather than making a struct, decided to use pair container for Position
using Position = std::pair<int, int>;

/**
 * @brief Vent object that contains positions of vent lines.
 *
 */
class Vent {
  public:
    /**
     * @brief Line object that is made up of two points, a start and an end.
     *
     */
    struct Line {
        Position start;
        Position end;

        /**
         * @brief Construct a new Line object from a string containing two
         * points.
         *
         * @throw std::invalid_argument if the string isn't formmatted
         * correctly.
         * @param str String formatted "%d,%d, -> %d,%d".
         */
        Line(std::string str);

        /**
         * @brief Converts line to a list of Positions that make up that line.
         *
         */
        std::vector<Position> convert_to_positions();

        /**
         * @brief Helper function that returns the horizontal line as a list of
         * positions. Functions does not check if line is horizontal.
         *
         */
        std::vector<Position> horizontal_to_positions();

        /**
         * @brief Helper function that returns the vertical line as a list of
         * positions. Functions does not check if line is vertical.
         */
        std::vector<Position> vertical_to_positions();

        /**
         * @brief Helper function that returns the diagonal line as a list of
         * positions. Function does not check if line is diagonal.
         *
         */
        std::vector<Position> diagonal_to_positions();
    };

    /**
     * @brief Construct a new Vent object from a list of vent lines.
     *
     * @param data A list of vent lines formmatted "%d,%d -> %d,%d".
     */
    Vent(std::vector<std::string> data);

    /**
     * @brief Returns the count of positions in vent that are intersected by
     * lines greater than or equal to n times.
     *
     * @param n Minimum number of intersections at a position.
     */
    int count_intersections(const int &n);

  private:
    std::unordered_map<Position, int, Pair_Hash> m_graph;

    /**
     * @brief Helper function that extracts positions from a list of strings of
     * lines and return them in a vector.
     *
     * @param data A list of strings formmatted "%d,%d -> %d,%d"
     */
    std::vector<Position>
    extract_positions(const std::vector<std::string> &data);

    void invariant() { assert(!m_graph.empty()); }
};

#endif