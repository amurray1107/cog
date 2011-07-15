project(cog_demo_common)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
file(GLOB_RECURSE cpp_files "*.cpp")
file(GLOB_RECURSE c_files "*.c")

set(e "cog_demo_common")
add_library(${e} STATIC ${cpp_files} ${c_files})
target_link_libraries(${e} cog ${GLUT_LIBRARY} ${OPENGL_LIBRARIES})

