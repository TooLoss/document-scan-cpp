#include <png_reader.h>
#include <cassert>
#include <iostream>


void test_png_reader(const std::string_view filename) {

    PNGColorSpace colorSpace = PNGColorSpace::Grayscale;
    uint8_t bit_depth;

    Image png_image = std::move(open_as_png(filename, bit_depth));

    std::cout << "Columns " << png_image.get_columns() << std::endl;
    std::cout << "Rows " << png_image.get_rows() << std::endl;
    std::cout << "bit_depth " << (int)bit_depth << std::endl;

    std::cout << "index: " << png_image.vector_to_index(Coord(1,1)) << std::endl;
    std::cout << "Colorspace " << (int)png_image.color_space << std::endl;

    for (int i = 0 ; i < png_image.get_columns()*png_image.get_rows()*3 ; i++) {
        std::cout << (int)png_image.buffer[i] << std::endl;
    }

    assert(png_image.get_columns() == 4);
    assert(png_image.get_rows() == 4);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Usage :" << std::endl;
        std::cout << "Argument 1 : relative filepath" << std::endl;
        return 0;
    }

    std::cout << "Begin test : PNG Reader" << std::endl;
    std::cout << argv[1] << std::endl;
    test_png_reader(argv[1]);
}
