#include <cstdint>
#include <span>
#include <string_view>
#include <vector>
#include <image.h>

enum class PNGColorSpace : uint8_t {
    Grayscale,
    Truecolor,
    Palette,
    GrayscaleAlpha,
    TruecolorAlpha
};


Image open_as_png(uint32_t &width, uint32_t &height, std::string_view filename, PNGColorSpace &color_space, uint8_t &bit_depth);
