#
cmake_minimum_required(VERSION 2.8)
#
#
project(cog)

#
set(CMAKE_DEBUG_POSTFIX "_d")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

#
include(CheckTargetCPU)

# Source code
include_directories("${CMAKE_SOURCE_DIR}/include")
file(GLOB_RECURSE cpp_files "source/*.cpp")
file(GLOB_RECURSE h_files "source/*.h")
add_library(cog STATIC ${cpp_files} ${h_files})

# Unit Test
enable_testing()
add_subdirectory(test)

# Demo
add_subdirectory(demo)

