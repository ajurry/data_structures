# Specify the minimum version
cmake_minimum_required(VERSION 3.1)

# Add C++ standard library
set (CMAKE_CXX_STANDARD 17)

# Project to create
project(test_containers)

# Set source and bin directories
set(CMAKE_SOURCE_DIR source)
set(CMAKE_BINARY_DIR ../bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../lib)

# Set paths for includes, linking and output
set(CMAKE_INCLUDE_PATH include)
set(LIBRARY_OUTPUT_PATH ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

# Add include directory to include path
include_directories(${CMAKE_INCLUDE_PATH})
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/*.cpp)

# Executables
add_library(containers ${SOURCES})

