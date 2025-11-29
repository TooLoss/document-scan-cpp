#include "../include/matrix.h"
#include <type_traits>
#include <stdexcept>


template <typename T>
T Matrix2D<T>::get_value(Coord coord) {
    if (!is_in_range(coord))
        throw std::out_of_range("Coordinates are outside matrix boundaries.");
    const uint32_t index = vector_to_index(coord);
    return values[index];
}

template <typename T>
uint32_t Matrix2D<T>::vector_to_index(Coord coord) {
    return coord.y * columns + coord.x;
}

template <typename T>
void Matrix2D<T>::set_value(Coord coord, T value) {
    if(!is_in_range(coord))
        throw std::out_of_range("Error : out of range");
   const uint32_t index = vector_to_index(coord);
   values[index] = value;
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

void Image::set_pixel_value(Coord coord, uint8_t value) {
    const uint8_t channel = get_channel_count(color_space);
    const int32_t pixel_index = channel * vector_to_index(coord);

    for (int i = 0 ; i < channel ; i++) {

        if (pixel_index + i >= values.size()) throw std::out_of_range("Error : coordinate out of range.");

        values[pixel_index + i] = value;
    }
}