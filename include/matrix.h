#include <vector>
#include <span>

struct Coord {
    uint32_t x;
    uint32_t y;
}; 

template <typename T>
class Matrix2D {
public:

    Matrix2D(std::vector<T>&& val) : buffer(std::move(val)), values(val) {};

    std::span<T> values;

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

    void convolve(Matrix2D c_matrix);


protected:
    std::vector<int> buffer;

    uint32_t rows;
    uint32_t columns;

    void convolve_at(Coord coord, Matrix2D c_matrix);
};
