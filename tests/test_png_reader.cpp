#include <png_reader.h>
#include <cassert>
#include <iostream>


void test_png_reader(const std::string_view filename) {

    PNGColorSpace colorSpace = PNGColorSpace::Grayscale;

    Image png_image = std::move(open_as_png(filename));

    std::cout << "Columns " << png_image.get_columns() << std::endl;
    std::cout << "Rows " << png_image.get_rows() << std::endl;
    std::cout << "bit_depth " << (int)png_image.get_bit_depth()<< std::endl;

    std::cout << "index: " << png_image.vector_to_index(Coord(1,1)) << std::endl;
    std::cout << "Colorspace " << (int)png_image.get_color_space() << std::endl;

    assert(png_image.get_columns() == 4);
    assert(png_image.get_rows() == 4);

    for (int i = 0 ; i < png_image.get_columns() ; i++) {
        for (int j = 0 ; j < png_image.get_rows() ; j++) {
            std::cout << (int)png_image.get_grayscale_value(Coord(i,j)) << std::endl;
        }
    }

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
