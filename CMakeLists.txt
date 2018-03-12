project(gruppe32)
cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

add_executable(gruppe32 "${CMAKE_SOURCE_DIR}/src/main.cpp")
set_target_properties(gruppe32
    PROPERTIES
    CXX_STANDARD "17"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)
