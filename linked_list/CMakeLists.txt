# Specify the minimum version
cmake_minimum_required(VERSION 2.8)

# Add C++ standard library
set (CMAKE_CXX_STANDARD 11)

# Project to create
project(make_test)

# Set source and bin directories
set(CMAKE_SOURCE_DIR source)
set(CMAKE_BINARY_DIR bin)

# Set paths for includes, linking and output
set(CMAKE_INCLUDE_PATH include)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Add include directory to include path
include_directories(${CMAKE_INCLUDE_PATH})
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/*.cpp)

#Executables
add_executable(make_test ${SOURCES})
