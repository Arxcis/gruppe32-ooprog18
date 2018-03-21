project(gruppe32)
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

#set(CMAKE_CXX_COMPILER "g++-7")
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
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/.."
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/.."
)
if (DARWIN)
target_compile_options(gruppe32
    PRIVATE "-Wno-invalid-source-encoding" # Problem with encoding of norwegian characters cross platform. PRobably something to do with UTF-8 vs UTF-16 on Windows(Visual Studio) vs Linux/Mac.
)
endif()

target_include_directories(gruppe32
    PRIVATE "${CMAKE_SOURCE_DIR}/include"
)

if(MSVC)
configure_file("${CMAKE_SOURCE_DIR}/data/read/seed-idrettene.yml" "${CMAKE_BINARY_DIR}/data/read/seed-idrettene.yml" COPYONLY)
configure_file("${CMAKE_SOURCE_DIR}/data/read/seed-spillerene.yml" "${CMAKE_BINARY_DIR}/data/read/seed-spillerene.yml" COPYONLY)
#configure_file("${CMAKE_SOURCE_DIR}/data/read-write/idrettene.yml" "${CMAKE_BINARY_DIR}/data/read-write/idrettene.yml" COPYONLY)
#configure_file("${CMAKE_SOURCE_DIR}/data/read-write/spillerene.yml" "${CMAKE_BINARY_DIR}/data/read-write/spillerene.yml" COPYONLY)
endif()

#[[# test_valid.cpp build
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


]]


