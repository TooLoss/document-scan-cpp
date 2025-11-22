#include "../include/matrix.h"
#include <type_traits>

template <typename T>
template <typename U>
void Matrix2D<T>::convolve(Matrix2D<U>& c_matrix) {
    static_assert(std::is_integral_v<U> && std::is_integral_v<T>,
            "Values should be integral");
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            const Coord pos(i,j);
            set_pixel_value(pos, convolv_at(pos, c_matrix));
        }
    }
}

template <typename T>
template <typename U>
T Matrix2D<T>::convolve_at(Coord coord, Matrix2D<U>& c_matrix) {
    const uint32_t c_rows = c_matrix.get_rows();
    const uint32_t c_columns =  c_matrix.get_columns();
    const Coord center((c_rows - 1)/2, (c_columns - 1)/2);

    Coord current_pos(0,0);

    T sum = 0;

    for(int i = 0; i < c_rows; i++) {
        for(int j = 0; j < c_columns; j++) {
            current_pos.x = coord.x - center.x + i;
            current_pos.y = coord.y - center.y + j;
            if(is_in_range(current_pos))
                sum += get_pixel_value(current_pos) * c_matrix.get_pixel_value(Coord(i,j));
        }
    }

    return sum;
}

template <typename T>
bool Matrix2D<T>::is_in_range(Coord coord) {
    return (coord >= 0) && (coord.x < columns) && (coord.y < rows);
}
