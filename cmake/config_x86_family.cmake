message("configuring for x86 family...")

add_definitions("-D__SSE__" "-D__SSE2__")

if(${CMAKE_COMPILER_IS_GNUCXX})
  add_definitions("-msse" "-msse2")
  add_definitions("-fabi-version=0")
  add_definitions("-Wall")
endif()

