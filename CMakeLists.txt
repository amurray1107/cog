#
cmake_minimum_required(VERSION 2.8)
#
#
project(cog)

#
set(CMAKE_CONFIGURATION_TYPES Debug Release)
set(CMAKE_DEBUG_POSTFIX "_d")

#
set(CPU ${CMAKE_SYSTEM_PROCESSOR})
if((${CPU} MATCHES "^i?[x3456789]86")OR(${CPU} STREQUAL "amd64"))
  message("Processor: Intel x86/x64 Family")
  if(${CMAKE_COMPILER_IS_GNUCXX})
    add_definitions("-msse" "-msse2")
    add_definitions("-fabi-version=0")
    add_definitions("-Wall")
  endif()
  
  if(${CPU} MATCHES "64$")
    add_definitions("-D__x86_64__")
  else()
    add_definitions("-D__x86__")
  endif()
  
  add_definitions("-D__SSE__" "-D__SSE2__")

else()
  message(FATAL_ERROR "Processor: Unknown")  
endif()

# Source code
include_directories("${CMAKE_SOURCE_DIR}/include")
file(GLOB_RECURSE cpp_files "source/*.cpp")
add_library(cog STATIC ${cpp_files})

# Unit Test
enable_testing()
add_subdirectory(test)

# Demo
add_subdirectory(demo)

