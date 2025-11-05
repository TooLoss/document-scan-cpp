#include <cstdint>
#include <span>
#include <stdexcept>

export module image_core;

export struct Coord {
    int x,y;

    Coord(int x_pass, int y_pass) {
        x = x_pass;
        y = y_pass;
    }
};

export struct Image {
    int height, width;
    std::span<uint8_t> pixels;
};

export namespace image_core {

    uint8_t* get_pixel(Image& image, Coord pos);
    void set_pixel(Image& image, Coord pos, uint8_t value);

}

uint8_t* get_pixel(Image& image, Coord pos) {
    if (pos.x >= image.height || pos.y >= image.width || pos.x < 0 || pos.y < 0) {
        throw std::out_of_range("Pixel coordinate out of range");
    }
    return &image.pixels[(pos.y*image.width) + pos.x];
}

void set_pixel(Image &image, Coord pos, uint8_t value) {
    *get_pixel(image, pos) = value;
}