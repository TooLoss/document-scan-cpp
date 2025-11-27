add_executable(test_png_reader test_png_reader.cpp)

target_link_libraries(test_png_reader PRIVATE png_reader image ZLIB::ZLIB)