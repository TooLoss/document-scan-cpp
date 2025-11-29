#include <png_reader.h>
#include <cassert>
#include <iostream>
#include <matrix_processing.h>
#include <matrix_utils.h>

void print_details(Image &image) {
    std::cout << "Columns " << image.get_columns() << std::endl;
    std::cout << "Rows " << image.get_rows() << std::endl;
    std::cout << "Vector size " << image.get_values().size() << std::endl;
    std::cout << "bit_depth " << (int)image.get_bit_depth()<< std::endl;

    std::cout << "index: " << image.vector_to_index(Coord(1,1)) << std::endl;
    std::cout << "Colorspace " << (int)image.get_color_space() << std::endl;
}

void test_png_reader(const std::string_view filename) {

    Image png_image = std::move(open_as_png(filename));

    print_details(png_image);

    for (int i = 0 ; i < png_image.get_columns() ; i++) {
        for (int j = 0 ; j < png_image.get_rows() ; j++) {
            std::cout << (int)png_image.get_grayscale_value(Coord(i,j)) << std::endl;
        }
    }

    MatrixProcessing::convert_to_grayscale(png_image);
    std::span<uint8_t> values = png_image.get_values();

    for (int i = 0 ; i < values.size() ; i++) {
        std::cout << (int)values[i] << std::endl;
    }

}

void test_blur(const std::string_view filename) {

    Image image = std::move(open_as_png(filename));

    MatrixProcessing::convert_to_grayscale(image);
    print_details(image);
    MatrixProcessing::apply_blur(image, 3, 1.0);
    MatrixUtils::print(image);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Usage :" << std::endl;
        std::cout << "Argument 1 : relative filepath" << std::endl;
        return 0;
    }

    std::cout << "Begin test : PNG Reader" << std::endl;
    std::cout << argv[1] << std::endl;
    //test_png_reader(argv[1]);
    test_blur(argv[1]);
}
