cmake_minimum_required(VERSION 2.8)

# Project Name
PROJECT(Generator)

add_executable(${PROJECT_NAME} main.cpp vertex.cpp primitive.cpp box.cpp cone.cpp plane.cpp sphere.cpp)

target_link_libraries(${PROJECT_NAME})
