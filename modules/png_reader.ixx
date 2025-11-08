#include <cstdint>
#include <span>
#include <string_view>
#include <vector>

export module module_png_reader;

export enum class PNGColorSpace : uint8_t {
    // Color Type
    Grayscale,
    Truecolor,
    Palette,
    GrayscaleAlpha,
    TruecolorAlpha
};

export std::span<uint8_t> open_as_png(uint32_t &width, uint32_t &height, std::string_view filename, PNGColorSpace& color_space);

bool is_png_file(std::ifstream& file);

uint32_t read_next_bytes(std::ifstream& file, uint8_t bytes);

void get_bytes_per_pixels(size_t &size, PNGColorSpace color_space, uint8_t bit_depth);

void decompress_pixel_value(const std::vector<uint8_t> &input_data, std::vector<uint8_t> &image_pixel_data);