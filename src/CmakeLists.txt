cmake_minimum_required(VERSION 3.6.0)
add_library(a custom_allocator.hpp)
add_library(c custom_container.hpp)
add_executable(lab4 main.cpp)

target_link_libraries(lab4 a c)