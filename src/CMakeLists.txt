add_library(png_reader STATIC
        png_reader.cpp
)
target_include_directories(png_reader PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(png_reader PRIVATE ZLIB::ZLIB)
