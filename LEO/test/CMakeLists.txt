#
project(LeoTest)

#
file(GLOB cpp_files "*.cpp")

#
#add_executable(LeoTest ${cpp_files})
add_executable(LeoTest MACOSX_BUNDLE ${cpp_files})
target_link_libraries(LeoTest Leo)

