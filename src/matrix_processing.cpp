#include "../include/matrix_processing.h"

void MatrixProcessing::convert_to_grayscale(Image &image) {
    if (image.get_color_space() == PNGColorSpace::Grayscale) return;

    const uint32_t rows = image.get_rows();
    const uint32_t columns = image.get_columns();

    std::vector<uint8_t> grayscale_pixels;
    grayscale_pixels.resize(rows * columns);

    for (int i = 0 ; i < columns ; i++) {
        for (int j = 0 ; j < rows ; j++) {
            grayscale_pixels[i + columns * j] = image.get_grayscale_value(Coord(i,j));
        }
    }

    image = Image{std::move(grayscale_pixels), columns, rows, PNGColorSpace::Grayscale, image.get_bit_depth()};
}