project(cog_test)

#
function(ScanAndAddExecutable prefix test)
  set(p "${CMAKE_CURRENT_SOURCE_DIR}")
  file(GLOB_RECURSE cpp_files RELATIVE ${p} "*.cpp")
  
  foreach(i ${cpp_files})
    string(REGEX REPLACE "[/\\]" "_" base_name "${i}")
    string(REGEX REPLACE "[.][^.]+$" "" base_name "${base_name}")
    set(e "${prefix}${base_name}")
    
    add_executable(${e} ${i})
    
    set(libs ${ARGV})
    list(REMOVE_AT libs 0 1)
    list(LENGTH libs len)
    if(${len} GREATER 0)
      target_link_libraries(${e} ${libs})
    endif()
   
    message("Auto Add Exe: ${e} with libs: ${libs}")
    
    if(${test})
      message("Add Test: ${e}")
      add_test(${e} ${e} WORKING_DIRECTORY ${p})
    endif()
    
  endforeach(i)
  
endfunction()

#
ScanAndAddExecutable("unit_test_" TRUE "cog")

