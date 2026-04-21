cmake_minimum_required(VERSION 3.16)
project(cppatrix LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SRC_FILES
    "${CMAKE_SOURCE_DIR}/main.cpp"
    "${CMAKE_SOURCE_DIR}/sources/functions.cpp"
    "${CMAKE_SOURCE_DIR}/sources/regression.cpp"
)


add_executable(cppatrix ${SRC_FILES})

target_include_directories(cppatrix PRIVATE "${CMAKE_SOURCE_DIR}/include")
