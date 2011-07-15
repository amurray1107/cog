project(cog_demo)

#
find_package(OpenGL)
if(NOT ${OPENGL_FOUND})
  return()
endif()

#
find_package(GLUT)
if(NOT ${GLUT_FOUND})
  return()
endif()

#
add_subdirectory(common)

#
function(add_demo)
  include_directories("${cog_demo_common_SOURCE_DIR}/include")
  file(GLOB_RECURSE cpp_files "*.cpp")
  
  file(RELATIVE_PATH e ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
  string(REGEX REPLACE "[/\\]" "_" e ${e})
  
  add_executable(${e} ${cpp_files})
  target_link_libraries(${e} cog cog_demo_common)
  
  set_target_properties(${e} PROPERTIES DEBUG_POSTFIX "_d")
  
  set(od "${CMAKE_SOURCE_DIR}/bin")
  set_target_properties(${e} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${od}")
  set_target_properties(${e} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${od}")
  set_target_properties(${e} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${od}")
  
  #message("demo added: ${e}")
  #foreach(i ${cpp_files})
  #  message("demo source file: ${i}")
  #endforeach(i)
endfunction(add_demo)

#
set(p "${CMAKE_CURRENT_SOURCE_DIR}")
file(GLOB_RECURSE main_files RELATIVE ${p} "main.cpp")
foreach(i ${main_files})
  string(REGEX REPLACE "[/\\]main.cpp$" "" dir_name "${i}")
  message("Found demo: ${dir_name}")
  add_subdirectory("${dir_name}")
endforeach(i)

