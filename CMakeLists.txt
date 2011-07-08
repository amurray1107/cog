#
cmake_minimum_required(VERSION 2.8)
#
#
project(cog)

#
set(CMAKE_CONFIGURATION_TYPES Debug Release)
set(CMAKE_DEBUG_POSTFIX "_d")

#
#add_definitions("-msse" "-msse2" "-std=c++98")

# Source code
include_directories("${CMAKE_SOURCE_DIR}/include")
file(GLOB_RECURSE cpp_files "source/*.cpp")
add_library(cog STATIC ${cpp_files})

# Unit Test
enable_testing()
add_subdirectory(test)

# Demo
add_subdirectory(demo)

