#include <png_reader/png_reader.h>
#include <iostream>

int main() {
    std::cout << "Program started!" << std::endl; // Flush with endl
    try {
        uint32_t width, height;
        PNGColorSpace colorSpace = PNGColorSpace::Grayscale;
        uint8_t bit_depth;
        std::string_view filename = "E:/Documents/Code/document-scan-cpp/data/example.png";
        std::cout << "Opening file: " << filename << std::endl;
        std::cout << "About to open PNG..." << std::endl;
        auto image = png_reader::open_as_png(width, height, filename, colorSpace, bit_depth);
        std::cout << "PNG opened!" << std::endl;
        std::cout << image.size() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown error!" << std::endl;
        return 1;
    }
    return 0;
}
