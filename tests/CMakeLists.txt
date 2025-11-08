add_executable(test_png_reader test_png_reader.cpp)

target_link_libraries(test_png_reader PRIVATE png_reader_module)

add_custom_command(
        TARGET test_png_reader PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/data/example.png
        ${CMAKE_CURRENT_BINARY_DIR}/example.png
)