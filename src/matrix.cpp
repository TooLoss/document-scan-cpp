#include "../include/matrix.h"
#include <type_traits>
#include <stdexcept>


template <typename T>
T Matrix2D<T>::get_pixel_value(Coord coord) {
    if (!is_in_range(coord)) {
        throw std::out_of_range("Coordinates are outside matrix boundaries.");
    }
    uint32_t index = vector_to_index(coord);
    return this->buffer[index];
}

template <typename T>
uint32_t Matrix2D<T>::vector_to_index(Coord coord) {
    return coord.y * columns + coord.x;
}

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

template class Matrix2D<uint8_t>;


uint8_t Image::get_channel_count(PNGColorSpace my_color_space) {
    switch (my_color_space) {
        case PNGColorSpace::Palette:
        case PNGColorSpace::Grayscale:
            return 1;
        case PNGColorSpace::GrayscaleAlpha:
            return 2;
        case PNGColorSpace::Truecolor:
            return 3;
        case PNGColorSpace::TruecolorAlpha:
            return 4;
    };
    return 0;
}

uint8_t Image::get_color_channel_count(PNGColorSpace my_color_space) {
    switch (my_color_space) {
        case PNGColorSpace::Palette:
        case PNGColorSpace::Grayscale:
        case PNGColorSpace::GrayscaleAlpha:
            return 1;
        case PNGColorSpace::Truecolor:
        case PNGColorSpace::TruecolorAlpha:
            return 3;
    };
    return 0;
}

uint32_t Image::get_grayscale_value(Coord coord) {
    const uint8_t channel = get_channel_count(color_space);
    const int8_t colored_channel = get_color_channel_count(color_space);
    const int32_t pixel_index = channel * vector_to_index(coord);

    if (colored_channel == 0) throw std::runtime_error("Error: colored_channel is 0.");

    int32_t sum{0};

    for (int i = 0 ; i < channel ; i++) {

        if (pixel_index + i >= values.size()) throw std::out_of_range("Error : coordinate out of range.");

        if (i <= colored_channel) {
            sum += values[pixel_index + i];
        } else {
            sum *= values[pixel_index + i]/255;
        };
    }

    return static_cast<uint8_t>(sum/colored_channel);
}