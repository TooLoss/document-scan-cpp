#include <png_reader/png_reader.h>
#include <cstdint>
#include <fstream>
#include <vector>
#include <span>
#include <fstream>
#include <zlib.h>
#include <iostream>

bool is_png_file(std::ifstream &file) {
    const std::array<uint8_t, 8> png_signature = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
    std::array<char, 8> file_signature{};
    file.read(file_signature.data(), 8);
    for (size_t i = 0; i < 8; i++) {
        if (static_cast<uint8_t>(file_signature[i]) != png_signature[i]) return false;
    }
    return true;
}

uint32_t read_next_bytes(std::ifstream &file, uint8_t bytes) {
    std::vector<char> buffer(bytes);
    file.read(buffer.data(), bytes);
    uint32_t value = 0;
    for (uint8_t i = 0; i < bytes; i++) {
        value = (value << 8) | static_cast<uint8_t>(buffer[i]);
    }
    return value;
}

void get_bytes_per_pixels(size_t &size, PNGColorSpace color_space, uint8_t bit_depth) {
    size = (bit_depth + 7) / 8;

    switch (color_space) {
        case PNGColorSpace::Truecolor:
            size *= 3;
            break;
        case PNGColorSpace::GrayscaleAlpha:
            size *= 2;
            break;
        case PNGColorSpace::TruecolorAlpha:
            size *= 4;
            break;
        case PNGColorSpace::Grayscale:
            break;
        case PNGColorSpace::Palette:
            break;
    }
}

void decompress_pixel_value(const std::vector<uint8_t> &input_data, std::vector<uint8_t> &image_pixel_data) {
    z_stream stream = {nullptr};
    stream.next_in = const_cast<Bytef *>(input_data.data());
    stream.avail_in = input_data.size();
    stream.next_out = image_pixel_data.data();
    stream.avail_out = image_pixel_data.size();

    if (inflateInit(&stream) != Z_OK) {
        throw std::runtime_error("Fail to initialize ZLib Stream");
    }

    int inflate_int = inflate(&stream, Z_FINISH);

    if (inflate_int != Z_STREAM_END) {
        throw std::runtime_error("Fail to decompress IDAT Data");
    }

    inflateEnd(&stream);
}

namespace png_reader {

   std::vector<uint8_t>
    open_as_png(uint32_t &width, uint32_t &height, std::string_view filename, PNGColorSpace &color_space,
                uint8_t &bit_depth) {

        std::ifstream file{std::string(filename), std::ios::binary};

        if (!file.good()) throw std::runtime_error("File path is invalid.");

        if (!is_png_file(file)) throw std::runtime_error("File is not recognized as PNG");

        static std::vector<uint8_t> pixel_data; // should not be destroyed

        while (file) {
            uint32_t length = read_next_bytes(file, 4);
            std::array<char, 4> chunk{};
            file.read(chunk.data(), 4);

            if (std::string(chunk.data(), 4) == "IHDR") {
                // Start of the IHDR section
                width = read_next_bytes(file, 4);
                height = read_next_bytes(file, 4);
                color_space = static_cast<PNGColorSpace>(file.get());
                bit_depth = file.get();
                file.seekg(7, std::ios::cur); // skip metadata

                size_t bytes_per_pixel = 0;
                get_bytes_per_pixels(bytes_per_pixel, color_space, bit_depth);

                size_t row_size = width * bytes_per_pixel + 1;
                pixel_data.resize(row_size * height);
            } else if (std::string(chunk.data(), 4) == "IDAT") {
                // IDAT contains pixel values
                std::vector<uint8_t> IDAT_data(length);
                std::vector<char> IDAT_data_character(length);
                file.read(IDAT_data_character.data(), length);
                for (size_t i = 0; i < length; i++) {
                    IDAT_data[i] = static_cast<uint8_t>(IDAT_data_character[i]);
                }
                decompress_pixel_value(IDAT_data, pixel_data);
                file.seekg(4, std::ios::cur); // skip CRC
            } else if (std::string(chunk.data(), 4) == "IEND") {
                break;
            } else {
                // Not expected value
                file.seekg(4, std::ios::cur);
            }

        }

        return pixel_data;
    }
}