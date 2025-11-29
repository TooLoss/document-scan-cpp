add_library(png_reader STATIC
        png_reader.cpp
)
target_include_directories(png_reader PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(png_reader PRIVATE ZLIB::ZLIB)

add_library(image STATIC
        matrix.cpp
        matrix_processing.cpp
        matrix_utils.cpp
)

target_include_directories(image PUBLIC ${CMAKE_SOURCE_DIR}/include)