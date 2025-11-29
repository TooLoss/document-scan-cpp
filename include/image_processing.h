#pragma once

#include <matrix.h>

namespace ImageProcessing {
    template<typename T>
    void treshold(std::span<T> values, T t, T min_value, T max_value);

    void convert_to_grayscale(Image& image);

    /**
     * Connected Component Labeling
     * Detect islands in the image. Islands are separated with background
     * (ignored_value).
     *
     * @param ignored_value
     * @return matrix with labels
     */
    template<typename T>
    void connected_component_labeling(Matrix2D<T> matrix, uint8_t ignored_value);

    template <typename T, typename U>
    void convolve(Matrix2D<T> &matrix, Matrix2D<U> &c_matrix);

    template <typename T, typename U>
    T convolve_at(Matrix2D<T> &matrix, Matrix2D<U> &c_matrix, Coord coord);
}