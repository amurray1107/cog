#
#
project(GLion)

#
find_package(OpenGL)
if(NOT ${OPENGL_FOUND})
  return()
endif()

#
include_directories("${COG_SOURCE_DIR}/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

#
file(GLOB cpp_files "source/*.cpp")
file(GLOB prv_h_files "source/*.h")
file(GLOB_RECURSE pub_h_files "include/*.h")

#
unset(osdir)

#
if(${APPLE})
  set(osdir "macosx")
endif()

#
if(NOT DEFINED osdir)
  return()
endif()

#
file(GLOB mm_dep_files "source/${osdir}/*.mm")
file(GLOB cpp_dep_files "source/${osdir}/*.cpp")
file(GLOB prv_h_dep_files "source/${osdir}/*.h")

#
set(srcfiles ${cpp_files} ${priv_h_files} ${pub_h_files})
set(srcfiles ${srcfiles} ${cpp_dep_files} ${prv_h_dep_files})
set(srcfiles ${srcfiles} ${mm_dep_files})

#
add_library(GLion STATIC ${srcfiles})

#
target_link_libraries(GLion COG ${OPENGL_LIBRARIES})

#
set_target_properties(GLion PROPERTIES DEBUG_POSTFIX "_d")


#
add_subdirectory(test)

