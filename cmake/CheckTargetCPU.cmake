#
message("Check Target CPU...")

#
set(bd "${CMAKE_BINARY_DIR}/cmake/cpu")
set(sc "${CMAKE_MODULE_PATH}/CheckTargetCPU.cpp")
try_run(run_result build_result ${bd} ${sc} RUN_OUTPUT_VARIABLE output)
if(build_result AND (run_result EQUAL 0))
  set(TARGET_CPU_NAME "${output}")
  message("Processor: ${TARGET_CPU_NAME}")
  add_definitions("-D__${TARGET_CPU_NAME}__")
else()
  unset(TARGET_CPU_NAME)
endif()

if(NOT DEFINED TARGET_CPU_NAME)
  message(FATAL_ERROR "Processor: Unknown")
endif()

########### CONFIG

if(${TARGET_CPU_NAME} MATCHES "^x86")
  message("Processor Family: Intel x86")
  add_definitions("-D__SSE__" "-D__SSE2__")
  if(${CMAKE_COMPILER_IS_GNUCXX})
    add_definitions("-msse" "-msse2")
    add_definitions("-fabi-version=0")
    add_definitions("-Wall")
  endif()
elseif(${TARGET_CPU_NAME} MATCHES "^arm")
  message("Processor Family: ARM")
endif()

