#ifndef SUBSYSTEM_H
#define SUBSYSTEM_H

#include <cassert>
#include <queue>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

struct Board {
  public:
    /**
     * @brief Element that tracks value and if the value has been marked.
     *
     */
    struct Element {
        int value;
        bool marked;

        Element(int value, bool marked = false) : value{value}, marked{marked}
        {
        }
    };

    std::vector<std::vector<Element>> grid;
    std::pair<int, int> last_marked;

    /**
     * @brief Construct an empty Board object.
     *
     */
    Board() : grid{}, last_marked{} {}

    /**
     * @brief Construct a new Board object from a string of numbers.
     *
     * @param begin An iterator to the first string to read.
     * @param end An iterator to the last string to read.
     */
    Board(std::vector<std::string>::iterator begin,
          std::vector<std::string>::iterator end);

    /**
     * @brief A helper function that parses numbers from a string into an
     * Element list.
     *
     * @param str A string containing integers seperated by whitespaces.
     * @return A list of Elements.
     */
    std::vector<Element> parse_numbers(const std::string &str);

    /**
     * @brief Finds element in the grid and marks it as being found.
     *
     * @param element A value to find in the grid and mark it as being found.
     */
    void mark(const int &element);

    /**
     * @brief Checks the last marked location if there is a vertical line of
     * marked numbers or a horizontal line of marked numbers.
     *
     * @return True if there is a line of marked numbers the size of the grid.
     */
    bool won();
};

/**
 * @brief Bingo object that replicates a bingo subsystem where multiple games of
 * bingo can be played at the same time.
 *
 */
class Bingo {
  public:
    /**
     * @brief Construct a new Bingo object from strings whose first line is the
     * drawing numbers and subsequent lines are the different bingo boards.
     * NOTE: Is intended for 5x5 grids.
     *
     * @param data A list of strings containing the drawing numbers and the
     * different bingo boards.
     */
    Bingo(std::vector<std::string> data);

    /**
     * @brief Checks all of the boards and returns true if the board matches the
     * win condition.
     *
     * @return True if a board won.
     */
    bool won();

    /**
     * @brief Draws the next number from the drawing and marks that number in
     * the bingo boards.
     *
     */
    void draw_number();

    /**
     * @brief Calculates the score of the winning board by multiplying the sum
     * of all unmarked numbers in the board and the last drawn number. Use in
     * tandem with won() to ensure there is a winning board.
     *
     * @return The score of the winning board.
     */
    int score();

  private:
    std::queue<int> m_drawing_numbers;
    std::vector<Board> m_boards;
    int m_last_drawn;
    Board m_winner;

    /**
     * @brief Takes a string containing comma-seperated integers and places them
     * in a queue.
     *
     * @param data A string containing comma-seperated integers.
     */
    void queue_drawing_numbers(const std::string &data);

    /**
     * @brief Conditions that must be true for the bingo subsystem.
     *
     */
    void invariant();
};

#endif