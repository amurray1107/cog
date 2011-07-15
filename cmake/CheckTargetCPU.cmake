#
message("Check Target CPU...")

#
file(GLOB testcpu_files "${CMAKE_MODULE_PATH}/*_cpu.cpp")

#
unset(TARGET_CPU_NAME)

#
foreach(i ${testcpu_files})
  message("Try Compile: ${i}")
  
  set(bd "${CMAKE_BINARY_DIR}/cmake/cpu")
  try_run(run_result build_result ${bd} ${i} RUN_OUTPUT_VARIABLE output)
  
  if(build_result AND (run_result EQUAL 0))
    set(TARGET_CPU_NAME "${output}")
    
    message("Processor: ${TARGET_CPU_NAME}")
    add_definitions("-D__${TARGET_CPU_NAME}__")
    
    break()
  endif()
  
endforeach(i)

#
if(NOT DEFINED TARGET_CPU_NAME)
  message(FATAL_ERROR "Processor: Unknown")
endif()

#
include("config_${TARGET_CPU_NAME}" OPTIONAL)
