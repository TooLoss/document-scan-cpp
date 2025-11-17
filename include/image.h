#include <span>
#include <cstdint>

struct Image {

    std::vector<uint8_t> buffer;
    std::span<uint8_t> image_view;

    uint32_t width;
    uint32_t height;

    Image(std::vector<uint8_t>&& pixel_data) : buffer(std::move(pixel_data)), image_view(buffer) {};
};
