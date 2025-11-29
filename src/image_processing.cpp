#include "../include/image_processing.h"

template<typename T>
void ImageProcessing::treshold(std::span<T> values, T t, T min_value, T max_value) {
    for (int i = 0 ; i < values.size() ; i++) {
        if (values[i] < t) values[i] = min_value;
        else values[i] = max_value;
    }
}

void ImageProcessing::convert_to_grayscale(Image &image) {
    if (image.get_color_space() == PNGColorSpace::Grayscale) return;

    const uint32_t rows = image.get_rows();
    const uint32_t columns = image.get_columns();

    std::vector<uint8_t> grayscale_pixels;
    grayscale_pixels.resize(rows * columns);

    for (int i = 0 ; i < columns ; i++) {
        for (int j = 0 ; j < rows ; j++) {
            image.get_values()[i + columns * j] = image.get_grayscale_value(Coord(i,j));
        }
    }

    image = Image{std::move(grayscale_pixels), columns, rows, PNGColorSpace::Grayscale, image.get_bit_depth()};
}

template <typename T, typename U>
void ImageProcessing::convolve(Matrix2D<T> &matrix, Matrix2D<U> &c_matrix) {
    static_assert(std::is_integral_v<U> && std::is_integral_v<T>,
                  "Values should be integral");
    for(int i = 0; i < matrix.get_rows() ; i++) {
        for(int j = 0; j < matrix.get_columns() ; j++) {
            const Coord pos(i,j);
            set_value(pos, convolv_at(pos, c_matrix));
        }
    }
}

template <typename T, typename U>
T ImageProcessing::convolve_at(Matrix2D<T> &matrix, Matrix2D<U> &c_matrix, Coord coord) {
    const uint32_t c_rows = c_matrix.get_rows();
    const uint32_t c_columns =  c_matrix.get_columns();
    const Coord center((c_rows - 1)/2, (c_columns - 1)/2);

    Coord current_pos(0,0);

    T sum = 0;

    for(int i = 0; i < c_rows; i++) {
        for(int j = 0; j < c_columns; j++) {
            current_pos.x = coord.x - center.x + i;
            current_pos.y = coord.y - center.y + j;
            if(matrix.is_in_range(current_pos))
                sum += matrix.get_value(current_pos) * c_matrix.get_value(Coord(i, j));
        }
    }

    return sum;
}