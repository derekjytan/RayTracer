cmake_minimum_required(VERSION 3.10)
project(RayTracer)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable
add_executable(raytrace src/main.cpp)

# Include directories
target_include_directories(raytrace PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
