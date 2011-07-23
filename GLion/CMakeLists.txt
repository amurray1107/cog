#
#
project(GLion)

#
include_directories("${COG_SOURCE_DIR}/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

#
file(GLOB_RECURSE cpp_files "source/*.cpp")
file(GLOB_RECURSE prv_h_files "source/*.h")
file(GLOB_RECURSE pub_h_files "include/*.h")

#
if(${APPLE})
  add_definitions("-ObjC++")
endif()

#
add_library(GLion STATIC ${cpp_files} ${priv_h_files} ${pub_h_files})

#
target_link_libraries(GLion COG ${OPENGL_LIBRARIES})

#
set_target_properties(GLion PROPERTIES DEBUG_POSTFIX "_d")

