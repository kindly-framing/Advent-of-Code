#ifndef HEIGHT_MAP_H
#define HEIGHT_MAP_H

#include <algorithm>
#include <cassert>
#include <queue>
#include <set>
#include <string>
#include <vector>

/**
 * @brief Position object that can be used to get neighbors of the position.
 *
 */
struct Position {
    int x;
    int y;

    Position(int x, int y) : x(x), y(y) {}

    /**
     * @brief Returns a list of neighbors (Up, Down, Left, and Right) from
     * position.
     *
     */
    std::vector<Position> neighbors() const;

    // helpful for checking if less than another Position.
    bool operator<(const Position &p) const;
};

/**
 * @brief Height map object that stores a height map and can find the maps
 * low-points and basins.
 *
 */
class Height_Map {
  public:
    Height_Map(std::vector<std::string> lines);

    /**
     * @brief Returns a list of all low point's values in the height map.
     *
     */
    std::vector<int> low_point_values();

    /**
     * @brief Returns a list of all low point's positions in the height map.
     *
     */
    std::vector<Position> low_point_positions();

    /**
     * @brief Returns a list of all sizes of basins in the height map.
     *
     */
    std::vector<int> get_basin_sizes();

  private:
    std::vector<std::vector<int>> map;

    /**
     * @brief Helper function that determines if a position is a low point.
     *
     */
    bool is_low_point(const Position &p) const;

    /**
     * @brief Helper function that returns a list of all valid neighbors for the
     * position.
     *
     */
    std::vector<Position> valid_neighbors(const Position &p) const;

    /**
     * @brief Helper function that inserts valid neighbors and their source
     * position's value into queue.
     *
     */
    void insert_neighbors_in_queue(const Position &p,
                                   std::queue<std::pair<Position, int>> &q);

    /**
     * @brief Returns the value in the height map at that position.
     *
     */
    int map_value(const Position &p) const;

    /**
     * @brief Checks if given position is in bounds of the height map.
     *
     */
    bool in_bounds(const Position &p) const;
};

#endif