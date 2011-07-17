project(COGDEMOFWK)

message("Configuring Demo Framework...")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
file(GLOB_RECURSE cpp_files "*.cpp")
file(GLOB_RECURSE c_files "*.c")

set(e "COGdemofwk")
add_library(${e} STATIC ${cpp_files} ${c_files})
target_link_libraries(${e} COG ${GLUT_LIBRARY} ${OPENGL_LIBRARIES})
