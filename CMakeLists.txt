project(gruppe32)
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

SET(CMAKE_BUILD_TYPE Debug)

add_executable(gruppe32 "${CMAKE_SOURCE_DIR}/src/main.cpp")

set_target_properties(gruppe32
    PROPERTIES
    CXX_STANDARD 17
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)

if (WIN32)
target_compile_options(gruppe32
	PRIVATE "/std:c++latest"
)
endif()