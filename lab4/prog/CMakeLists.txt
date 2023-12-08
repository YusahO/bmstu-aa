cmake_minimum_required(VERSION 3.6.0)
project(lab_01 LANGUAGES CXX VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_CXX_FLAGS "-O0 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -O0 -Wall -Wextra")

add_executable(app main.cpp)
add_subdirectory(lib)

target_link_libraries(app lib)