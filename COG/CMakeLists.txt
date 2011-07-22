#
#
project(COG)

#
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

#
file(GLOB_RECURSE cpp_files "source/*.cpp")
file(GLOB_RECURSE prv_h_files "source/*.h")
file(GLOB_RECURSE pub_h_files "include/*.h")

#
add_library(COG STATIC ${cpp_files} ${priv_h_files} ${pub_h_files})

#
set_target_properties(COG PROPERTIES DEBUG_POSTFIX "_d")

# Unit Test
add_subdirectory(test)

