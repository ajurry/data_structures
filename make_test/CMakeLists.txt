# Specify the minimum version
cmake_minimum_required(VERSION 3.1)

# Add C++ standard library
set (CMAKE_CXX_STANDARD 17)

# Downloading and unpacking gtest library
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

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
target_link_libraries(make_test gtest gtest_main)
add_test(NAME make_test COMMAND example)
