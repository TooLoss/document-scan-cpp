#include <cstdint>
#include <span>
#include <string_view>
#include <vector>
#include <matrix.h>

Image open_as_png(std::string_view filename, uint8_t &bit_depth);
