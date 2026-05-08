cmake_minimum_required(VERSION 3.16)
project(cppatrix LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(APPLE)
    list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew")
endif()

find_package(raylib 4.0 REQUIRED)

file(GLOB SRC_FILES
    "${CMAKE_SOURCE_DIR}/main.cpp"
    "${CMAKE_SOURCE_DIR}/sources/functions.cpp"
    "${CMAKE_SOURCE_DIR}/sources/regression.cpp"
    "${CMAKE_SOURCE_DIR}/sources/graph.cpp"
)

add_executable(cppatrix ${SRC_FILES})
target_link_libraries(cppatrix PRIVATE raylib)
target_include_directories(cppatrix PRIVATE "${CMAKE_SOURCE_DIR}/include")

add_executable(test raylib.cpp sources/graph.cpp)
target_link_libraries(test PRIVATE raylib)
target_include_directories(test PRIVATE "${CMAKE_SOURCE_DIR}/include")
