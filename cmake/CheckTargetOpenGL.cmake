#
unset(TARGET_OPENGL_LIBS)

#
if(${TARGET_OS_NAME} STREQUAL "macosx")
  set(TARGET_OPENGL_LIBS "-framework OpenGL")
endif()

#
if(${TARGET_OS_NAME} STREQUAL "mswindows")
  set(TARGET_OPENGL_LIBS "OpenGL32.lib")
endif()

