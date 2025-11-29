#include "../include/matrix.h"
#include <stdexcept>


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