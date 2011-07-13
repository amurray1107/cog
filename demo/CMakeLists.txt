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
  
  string(LENGTH "${CMAKE_SOURCE_DIR}" pl)
  string(LENGTH "${CMAKE_CURRENT_SOURCE_DIR}" l)
  math(EXPR pl ${pl}+1) # remove leading '/'
  math(EXPR l ${l}-${pl})
  string(SUBSTRING "${CMAKE_CURRENT_SOURCE_DIR}" ${pl} ${l} pe)
  
  string(REGEX REPLACE "[/]" "__" e ${pe})
  
  add_executable(${e} ${cpp_files})
  target_link_libraries(${e} cog cog_demo_common)
  
  set(od "${CMAKE_SOURCE_DIR}/bin")
  set_target_properties(${e} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${od})
  set_target_properties(${e} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${od})
  set_target_properties(${e} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${od})
  
  #message("demo added: ${e}")
  #foreach(i ${cpp_files})
  #  message("demo source file: ${i}")
  #endforeach(i)
endfunction(add_demo)

#
add_subdirectory(samples)

