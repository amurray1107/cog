#
message("Check Target OS...")

#
unset(TARGET_OS_NAME)
unset(TARGET_OS_LIBS)

#
if(${APPLE})
  set(TARGET_OS_NAME "macosx")
  set(TARGET_OS_LIBS objc "-framework Cocoa")
endif()

#
if(${WIN32})
  set(TARGET_OS_NAME "mswindows")
  set(TARGET_OS_LIBS "Kernel32.lib" "User32.lib" "Gdi32.lib" "GdiPlus.lib")
endif()

#
if(NOT DEFINED TARGET_OS_NAME)
  message(FATAL_ERROR "OS: Unknown")
endif()

#
add_definitions("-D__${TARGET_OS_NAME}__")

