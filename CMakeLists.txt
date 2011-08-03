#
cmake_minimum_required(VERSION 2.8)
#
# COG PROJECT
#
project(cog_project)

# INCLUDE MODULES
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(CheckTargetCPU)
include(CheckTargetOS)

# ENABLE UNIT TEST
enable_testing()

# COG PROJECT
add_subdirectory(COG)

# GLion PROJECT
add_subdirectory(GLion)

