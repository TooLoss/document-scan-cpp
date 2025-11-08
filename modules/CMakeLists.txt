add_library(png_reader_module INTERFACE)

target_sources(png_reader_module INTERFACE
        png_reader.ixx
        png_reader.cpp
)