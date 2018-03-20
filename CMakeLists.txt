project(gruppe32)
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set(CMAKE_BUILD_TYPE Debug)

# Application
add_executable(gruppe32 "${CMAKE_SOURCE_DIR}/src/main.cpp")

target_sources(gruppe32
    PRIVATE "${CMAKE_SOURCE_DIR}/src/ListTool2b.cpp"
    PRIVATE "${CMAKE_SOURCE_DIR}/src/DB.cpp"
    PRIVATE "${CMAKE_SOURCE_DIR}/src/IO.cpp"
    PRIVATE "${CMAKE_SOURCE_DIR}/src/App.cpp"
    PRIVATE "${CMAKE_SOURCE_DIR}/src/Terminal.cpp"
	PRIVATE "${CMAKE_SOURCE_DIR}/src/Valid.cpp"
	PRIVATE "${CMAKE_SOURCE_DIR}/src/Parser.cpp"
)

set_target_properties(gruppe32
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

target_include_directories(gruppe32
    PRIVATE "${CMAKE_SOURCE_DIR}/include"
)

if(WINDOWS)
file(COPY "${CMAKE_SOURCE_DIR}/data/" DESTINATION "${CMAKE_BINARY_DIR}/data/")
endif()

# test_valid.cpp build
add_executable(testgruppe32 "${CMAKE_SOURCE_DIR}/test/test.cpp")

set_target_properties(testgruppe32
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)

target_sources(testgruppe32
    PRIVATE "${CMAKE_SOURCE_DIR}/src/ListTool2b.cpp"
    PRIVATE "${CMAKE_SOURCE_DIR}/src/Valid.cpp"
    PRIVATE "${CMAKE_SOURCE_DIR}/src/Parser.cpp"
    PRIVATE "${CMAKE_SOURCE_DIR}/src/DB.cpp"
)

target_include_directories(testgruppe32
    PRIVATE "${CMAKE_SOURCE_DIR}/include"
    PRIVATE "${CMAKE_SOURCE_DIR}/test"
)





