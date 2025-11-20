#include <matrix.h>
#include <type_traits>

template <typename T, typename U>
void Matrix2D<T>::convolve(Matrix2D<U> c_matrix) {
    static_assert(std::is_integral_v<U> && std::is_integral_v<T>,
            "Values should be integral");
    for(int i; i < rows; i++) {
        for(int j; j < columns, j++) {
            convolve_at(Coord(i,j), c_matrix);
        }
    }
}

void convolve_at(Coord coord, Matrix2D c_matrix) {
    constexpr uint32_t c_rows, c_columns = c_matrix.get_rows(), c_matrix.get_columns();
}
