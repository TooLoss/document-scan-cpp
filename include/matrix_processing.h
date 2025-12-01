#pragma once

#include "../include/matrix.h"
#include <memory>
#include <cmath>

namespace MatrixProcessing {

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

    template<typename T>
    void treshold(std::span<T> values, T t, T min_value, T max_value) {
        for (int i = 0 ; i < values.size() ; i++) {
            if (values[i] < t) values[i] = min_value;
            else values[i] = max_value;
        }
    }

    template <typename T, typename U>
    T convolve_at(Matrix2D<T> &matrix, Matrix2D<U> &c_matrix, Coord coord) {
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
        return static_cast<T>(sum);
    }

    template <typename T, typename U>
    void convolve(Matrix2D<T> &matrix, Matrix2D<U> &c_matrix) {
        // TODO see if there is other methods to prevent copying
        Matrix2D<T> cache_matrix = matrix;
        for(int i = 0; i < matrix.get_rows() ; i++) {
            for(int j = 0; j < matrix.get_columns() ; j++) {
                const Coord pos(i,j);
                matrix.set_value(pos, convolve_at(cache_matrix, c_matrix, pos));
            }
        }
    }

    inline Matrix2D<float> gaussian_filter(uint32_t size, float sigma) {
        if (sigma <= 0.0f)
            throw std::invalid_argument("Sigma must be positive.");
        if (size <= 0)
            throw std::invalid_argument("Size must be > 0");
        std::vector<float> gaussian_filter;
        gaussian_filter.resize(size*size);
        const uint32_t center = static_cast<uint32_t>(std::round(size / 2.0));
        for (int n = 0 ; n < size*size ; n++) {
            const uint32_t i = n % size;
            const uint32_t j = static_cast<uint32_t>(n / size);
            const float var_i = std::pow(i-(center-1), 2);
            const float var_j = std::pow(j-(center-1), 2);
            const float exp_term = -1 * (var_i + var_j)/(2 * std::pow(sigma, 2));
            gaussian_filter[n] = (1/(2*std::numbers::pi*sigma*sigma)) * std::exp(exp_term);
        }
        Matrix2D<float> gaussian_matrix{std::move(gaussian_filter), size, size};
        return gaussian_matrix;
    }

    template <typename T>
    void apply_blur(Matrix2D<T> &matrix, uint32_t size, float sigma) {
        Matrix2D<float> gaussian_matrix = gaussian_filter(size, sigma);
        convolve(matrix, gaussian_matrix);
    }

    template <typename T>
    void apply_gradient(Matrix2D<T> &matrix) {
        std::vector<int8_t> sobel_filter = {
            -1, 0, 1,
            -1, 0, 1,
            -1, 0, 1
        };
        Matrix2D<int8_t> sobel_matrix{std::move(sobel_filter), 3, 3};
        convolve(matrix, sobel_filter);
    }
}
