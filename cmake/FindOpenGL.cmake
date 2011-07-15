# - Try to find OpenGL
# Once done this will define
#  
#  OPENGL_FOUND        - system has OpenGL
#  OPENGL_XMESA_FOUND  - system has XMESA
#  OPENGL_INCLUDE_DIR  - the GL include directory
#  OPENGL_LIBRARIES    - Link these to use OpenGL and GLU
#   
# If you want to use just GL you can use these values
#  OPENGL_gl_LIBRARY   - Path to OpenGL Library
#  
# On OSX default to using the framework version of opengl
# People will have to change the cache values of OPENGL_glu_LIBRARY 
# and OPENGL_gl_LIBRARY to use OpenGL with X11 on OSX

message("Finding OpenGL....")

IF (WIN32)
  IF (CYGWIN)
    FIND_PATH(OPENGL_INCLUDE_DIR GL/gl.h)
    FIND_LIBRARY(OPENGL_gl_LIBRARY opengl32)
  ELSE (CYGWIN)
    IF(BORLAND)
      SET (OPENGL_gl_LIBRARY import32 CACHE STRING "OpenGL library for win32")
    ELSE(BORLAND)
      SET (OPENGL_gl_LIBRARY opengl32 CACHE STRING "OpenGL library for win32")
    ENDIF(BORLAND)
  ENDIF (CYGWIN)
ELSE (WIN32)
  IF (APPLE)
    FIND_LIBRARY(OPENGL_gl_LIBRARY OpenGL PATH_SUFFIXES OpenGL.framework)
    FIND_PATH(incdir OpenGL.h PATH_SUFFIXES OpenGL.framework/Headers)
    SET(OPENGL_INCLUDE_DIR ${incdir})
    message("${OPENGL_gl_LIBRARY}")
    message("${OPENGL_INCLUDE_DIR}")
  ELSE(APPLE)
    # The first line below is to make sure that the proper headers
    # are used on a Linux machine with the NVidia drivers installed.
    # They replace Mesa with NVidia's own library but normally do not
    # install headers and that causes the linking to
    # fail since the compiler finds the Mesa headers but NVidia's library.
    # Make sure the NVIDIA directory comes BEFORE the others.
    #  - Atanas Georgiev <atanas@cs.columbia.edu>

    FIND_PATH(OPENGL_INCLUDE_DIR GL/gl.h
      /usr/share/doc/NVIDIA_GLX-1.0/include
      /usr/openwin/share/include
      /opt/graphics/OpenGL/include /usr/X11R6/include
    )

    FIND_PATH(OPENGL_xmesa_INCLUDE_DIR GL/xmesa.h
      /usr/share/doc/NVIDIA_GLX-1.0/include
      /usr/openwin/share/include
      /opt/graphics/OpenGL/include /usr/X11R6/include
    )

    FIND_LIBRARY(OPENGL_gl_LIBRARY
      NAMES GL MesaGL
      PATHS /opt/graphics/OpenGL/lib
            /usr/openwin/lib
            /usr/shlib /usr/X11R6/lib
    )

    # On Unix OpenGL most certainly always requires X11.
    # Feel free to tighten up these conditions if you don't 
    # think this is always true.
    # It's not true on OSX.

    IF (OPENGL_gl_LIBRARY)
      IF(NOT X11_FOUND)
        find_package(X11)
      ENDIF(NOT X11_FOUND)
      IF (X11_FOUND)
        IF (NOT APPLE)
          SET (OPENGL_LIBRARIES ${X11_LIBRARIES})
        ENDIF (NOT APPLE)
      ENDIF (X11_FOUND)
    ENDIF (OPENGL_gl_LIBRARY)
  ENDIF(APPLE)
ENDIF (WIN32)

IF(OPENGL_gl_LIBRARY)
    IF(OPENGL_xmesa_INCLUDE_DIR)
      SET( OPENGL_XMESA_FOUND "YES" )
    ELSE(OPENGL_xmesa_INCLUDE_DIR)
      SET( OPENGL_XMESA_FOUND "NO" )
    ENDIF(OPENGL_xmesa_INCLUDE_DIR)
    
    SET( OPENGL_LIBRARIES  ${OPENGL_gl_LIBRARY} ${OPENGL_LIBRARIES})
ENDIF(OPENGL_gl_LIBRARY)

# This deprecated setting is for backward compatibility with CMake1.4
SET(OPENGL_INCLUDE_PATH ${OPENGL_INCLUDE_DIR})

# handle the QUIETLY and REQUIRED arguments and set OPENGL_FOUND to TRUE if
# all listed variables are TRUE
#INCLUDE(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
#FIND_PACKAGE_HANDLE_STANDARD_ARGS(OpenGL DEFAULT_MSG OPENGL_gl_LIBRARY)

#MARK_AS_ADVANCED(
#  OPENGL_INCLUDE_DIR
#  OPENGL_xmesa_INCLUDE_DIR
#  OPENGL_gl_LIBRARY
#)
