project(cog_test)

set(p "${CMAKE_CURRENT_SOURCE_DIR}")
file(GLOB_RECURSE cpp_files RELATIVE ${p} "*.cpp")

foreach(i ${cpp_files}) 
  #message("found test source code: ${i}")
  #string(REGEX MATCH "([^/]+)([.])(.+)$" base_name "${i}")
  string(REGEX REPLACE "[/]" "__" base_name "${i}")
  string(REGEX REPLACE "[.][^.]+$" "" exe_name "${base_name}")
  #message("base_name = ${base_name}")
  #message("exe_name = ${exe_name}")
  
  set(n "${exe_name}")
  set(e "unit_test_${exe_name}")
  add_executable(${e} ${i})
  target_link_libraries(${e} cog)
  add_test(${n} ${e} WORKING_DIRECTORY ${p})
endforeach(i)

