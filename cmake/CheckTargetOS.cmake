#
message("Check Target OS...")

#
unset(TARGET_OS_NAME)
unset(TARGET_OS_LIBS)

#
if(${APPLE})
  set(TARGET_OS_NAME "macosx")
  set(TARGET_OS_LIBS objc "-framework Cocoa" "-framework OpenGL")
endif()

#
if(NOT DEFINED TARGET_OS_NAME)
  message(FATAL_ERROR "OS: Unknown")
endif()

