#pragma once

#include <vector>
#include <stdint.h>
#include <span>

struct Coord {
    uint32_t x;
    uint32_t y;

    Coord(uint32_t ix, uint32_t iy) : x(ix), y(iy) {};

    bool operator>=(int i) const {
        return (this->x >= i) && (this->y >= i);
    }

    bool operator>(int i) const {
        return (this->x > i) && (this->y > i);
    }

    bool operator==(int i) const {
        return (this->x == i) && (this->y == i);
    }

    Coord operator*(int i) const {
        return Coord(this->x * i, this->y * i);
    }
};

enum class PNGColorSpace : uint8_t {
    // see png doc
    Grayscale = 0,
    Truecolor = 2,
    Palette = 3,
    GrayscaleAlpha = 4,
    TruecolorAlpha = 6
};



template <typename T>
class Matrix2D {
public:
    Matrix2D(std::vector<T>&& val, uint32_t width, uint32_t height)
            : buffer(std::move(val)), values(buffer), rows(height), columns(width) {};

    uint32_t vector_to_index(Coord coord);

    bool is_in_range(Coord coord);

    /**
    * Get value of the matrixa type at x y coordinates.
    *
    * @param coord : x y coordinate to get the pixel from
    * @return T value at x y 
    */
    T get_value(Coord coord);

    /**
     * Set value of the matrix type at x y coordinates.
     *
     * @param coord : x y coordinate to get the pixel from
     * @param value : T value to set
     */
    void set_value(Coord coord, T value);

    uint32_t get_rows() const { return rows; }
    uint32_t get_columns() const { return columns; }
    std::span<T> get_values() const { return values; }

protected:
    uint32_t rows;
    uint32_t columns;

    std::vector<T> buffer;
    std::span<T> values;
};




class Image : public Matrix2D<uint8_t> {

public:
    using Matrix2D<uint8_t>::Matrix2D;

    template <typename U>
    Image(std::vector<U>&& val, uint32_t width, uint32_t height, PNGColorSpace color, uint8_t depth)
            : Matrix2D<uint8_t>(std::move(val), width, height),
              color_space(color),
              bit_depth(depth) {};

    uint32_t get_grayscale_value(Coord coord);
    void set_pixel_value(Coord coord, uint8_t value);

    uint8_t get_channel_count(PNGColorSpace my_color_space);
    uint8_t get_color_channel_count(PNGColorSpace my_color_space);

    PNGColorSpace get_color_space() const { return color_space; };
    uint8_t get_bit_depth() const { return bit_depth; };

private:
    PNGColorSpace color_space;
    uint8_t bit_depth;

};
