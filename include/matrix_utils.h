#pragma once

#include <iostream>
#include <matrix.h>
#include <iomanip>

namespace MatrixUtils{
    template <typename T>
    void print(Matrix2D<T> &matrix) {
        for (int i = 0 ; i < matrix.get_columns() ; i++) {
            for (int j = 0 ; j < matrix.get_rows() ; j++) {
                std::cout << std::setfill('0') << std::setw(3)
                          << static_cast<int>(matrix.get_value(Coord(i,j))) << " ";
            }
            std::cout << std::endl;
        }
    }
}
