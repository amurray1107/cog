#
project(GLion_test)

#
file(GLOB cpp_files "*.cpp")

#
add_executable(GLionTest ${cpp_files})
#add_executable(GLionTest MACOSX_BUNDLE ${cpp_files})
target_link_libraries(GLionTest GLion)

