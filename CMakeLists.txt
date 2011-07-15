#
cmake_minimum_required(VERSION 2.8)
#
#
project(cog)

#
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

#
include(CheckTargetCPU)

# Source code
include_directories("${CMAKE_SOURCE_DIR}/include")
file(GLOB_RECURSE cpp_files "source/*.cpp")
file(GLOB_RECURSE prv_h_files "source/*.h")
file(GLOB_RECURSE pub_h_files "include/*.h")
add_library(cog STATIC ${cpp_files} ${priv_h_files} ${pub_h_files})

# Unit Test
enable_testing()
add_subdirectory(test)

# Demo
add_subdirectory(demo)

