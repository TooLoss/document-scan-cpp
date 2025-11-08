import module_png_reader;
#include <cassert>
#include <iostream>

int main(int argc, char* argv[]) {
    try {
        uint32_t width, height;
        PNGColorSpace colorSpace;
        uint8_t bit_depth;
        std::string_view filename = argv[1];

        auto image = open_as_png(width, height, filename, colorSpace);
    } catch (const std::exception& e) {
        assert(false);
    }
}