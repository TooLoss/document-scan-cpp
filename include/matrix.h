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

    std::span<T> values;

    virtual uint32_t vector_to_index(Coord coord);

    bool is_in_range(Coord coord);

    /**
    * Get value of the matrixa type at x y coordinates.
    *
    * @param coord : x y coordinate to get the pixel from
    * @return T value at x y 
    */
    virtual T get_pixel_value(Coord coord);

    /**
     * Set value of the matrix type at x y coordinates.
     *
     * @param coord : x y coordinate to get the pixel from
     * @param value : T value to set
     */
    void set_pixel_value(Coord coord, T value);

    template <typename U>
        void convolve(Matrix2D<U>& c_matrix);

    uint32_t get_rows() { return rows; }
    uint32_t get_columns() { return columns; }


    std::vector<T> buffer;
protected:

    uint32_t rows;
    uint32_t columns;

    template <typename U>
        T convolve_at(Coord coord, Matrix2D<U>& c_matrix);
};




class Image : public Matrix2D<uint8_t> {

public:

    using Matrix2D<uint8_t>::Matrix2D;

    template <typename U>
    Image(std::vector<U>&& val, uint32_t width, uint32_t height, PNGColorSpace color)
    : Matrix2D<uint8_t>(std::move(val), width, height), color_space(color) {};

    PNGColorSpace color_space;

    uint8_t get_pixel_value(Coord coord) override;
    uint32_t vector_to_index(Coord coord) override;

    /**
     * Connected Component Labeling
     * Detect islands in the image. Islands are separated with background
     * (ignored_value).
     *
     * @param ignored_value
     * @return matrix with labels
     */
    Matrix2D connected_component_labeling(uint8_t ignored_value);

};
