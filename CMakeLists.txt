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
    "${CMAKE_SOURCE_DIR}/sources/functions.cpp"
    "${CMAKE_SOURCE_DIR}/sources/regression.cpp"
    "${CMAKE_SOURCE_DIR}/sources/graph.cpp"
)

add_compile_options(-fsanitize=address -fno-omit-frame-pointer -g -O1)
add_link_options(-fsanitize=address)

add_compile_options(-fsanitize=undefined,array-bounds -fno-omit-frame-pointer -g -O1)
add_link_options(-fsanitize=undefined,array-bounds)

add_executable(cppatrix main.cpp ${SRC_FILES})
target_link_libraries(cppatrix PRIVATE raylib)
target_include_directories(cppatrix PRIVATE "${CMAKE_SOURCE_DIR}/include")

# add_executable(raylibqwq raylib.cpp)
# target_link_libraries(raylibqwq PRIVATE raylib)
# target_include_directories(raylibqwq PRIVATE "${CMAKE_SOURCE_DIR}/include")

# add_executable(gate gate.cpp ${SRC_FILES})
# target_link_libraries(gate PRIVATE raylib)
# target_include_directories(gate PRIVATE "${CMAKE_SOURCE_DIR}/include")
