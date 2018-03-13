project(gruppe32)
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

add_executable(gruppe32 "${CMAKE_SOURCE_DIR}/src/main.cpp")

target_sources(gruppe32
    PRIVATE "${CMAKE_SOURCE_DIR}/src/ListTool2b.cpp"
    PRIVATE "${CMAKE_SOURCE_DIR}/src/DB.cpp"
    PRIVATE "${CMAKE_SOURCE_DIR}/src/IO.cpp"
    PRIVATE "${CMAKE_SOURCE_DIR}/src/App.cpp"
)

set_target_properties(gruppe32
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)

target_include_directories(gruppe32
    PRIVATE "${CMAKE_SOURCE_DIR}/include"
)
