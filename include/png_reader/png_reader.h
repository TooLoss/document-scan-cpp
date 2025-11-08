#include <cstdint>
#include <span>
#include <string_view>
#include <vector>

enum class PNGColorSpace : uint8_t {
    // Color Type
    Grayscale,
    Truecolor,
    Palette,
    GrayscaleAlpha,
    TruecolorAlpha
};

namespace png_reader {
    std::span<uint8_t> open_as_png(uint32_t &width, uint32_t &height, std::string_view filename, PNGColorSpace &color_space, uint8_t &bit_depth);
}