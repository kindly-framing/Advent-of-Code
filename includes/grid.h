#ifndef GRID_H
#define GRID_H

#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

template <typename T> class Grid {
  public:
    // builds a grid from a file and uses a function that converts line into a
    // vector
    Grid(std::string filename, std::vector<T> (*extractor)(const std::string &))
    {
        std::ifstream in(filename);
        if (!in.is_open()) {
            throw std::invalid_argument("Can't open file: " + filename);
        }

        std::string line;
        while (std::getline(in, line)) {
            data.push_back(extractor(line));
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const Grid<T> &grid)
    {
        for (auto &&row : grid.data) {
            for (auto &&col : row) {
                os << col << ' ';
            }
            os << '\n';
        }

        return os;
    }

  protected:
    std::vector<std::vector<T>> data;
};

/**
template <typename T> class Grid {
  public:
    Grid(int rows, int cols) : rows_(rows), cols_(cols)
    {
        data_ = new T[rows * cols];
    }
    ~Grid() { delete[] data_; }
    T &operator()(int row, int col) { return data_[row * cols_ + col]; }
    int rows() const { return rows_; }
    int cols() const { return cols_; }

  private:
    int rows_, cols_;
    T *data_;
};

class MyDerivedClass : public Grid<int> {
  public:
    MyDerivedClass(int rows, int cols) : Grid<int>(rows, cols) {}
    // Additional member functions and data members can be defined here
    void SomeFunction()
    {
        // Accessing the grid data using the operator() function
        (*this)(0, 0) = 5;
    }
};
*/
#endif
