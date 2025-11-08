cmake_minimum_required(VERSION 4.0)
project(document-scan-cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(MODULE_FLAGS "")
set(MODULE_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/modules")

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    list(APPEND MODULE_FLAGS -fmodules-ts)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    list(APPEND MODULE_FLAGS -fmodules-ts)
    list(APPEND MODULE_FLAGS -fmodule-output=${MODULE_OUTPUT_DIR})
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    list(APPEND MODULE_FLAGS /experimental:module)
    list(APPEND MODULE_FLAGS /module:output=${MODULE_OUTPUT_DIR})
endif()

add_compile_options(${MODULE_FLAGS})
include_directories(${MODULE_OUTPUT_DIR})

add_subdirectory(modules)
add_subdirectory(tests)