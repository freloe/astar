cmake_minimum_required(VERSION 3.0.0)
project(A_Star VERSION 0.1.0)


find_library(SFML NAMES -lsfml-graphics -lsfml-window -lsfml-system) 

add_executable(main src/main.cpp)

target_link_libraries(main -lsfml-graphics -lsfml-window -lsfml-system)

target_compile_options(main PUBLIC -std=c++2a)