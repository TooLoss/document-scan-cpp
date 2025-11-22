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

template <typename T>
class Matrix2D {
public:

    Matrix2D(std::vector<T>&& val) : buffer(std::move(val)), values(val) {};

    std::span<T> values;

    uint32_t to_vector_index(Coord coord);

    bool is_in_range(Coord coord);

    /**
    * Get value of the matrixa type at x y coordinates.
    *
    * @param coord : x y coordinate to get the pixel from
    * @return T value at x y 
    */
    T get_pixel_value(Coord coord);

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


protected:
    std::vector<int> buffer;

    uint32_t rows;
    uint32_t columns;

    template <typename U>
        T convolve_at(Coord coord, Matrix2D<U>& c_matrix);
};
