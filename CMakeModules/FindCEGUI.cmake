# Find CEGUI includes and library
#
# This module defines
#  CEGUI_INCLUDE_DIR
#  CEGUI_LIBRARY, the library to link against to use CEGUI.
#  CEGUILUA_LIBRARY, the library to link against to use the CEGUI script module.
#  CEGUI_TOLUA_LIBRARY, the library to link against to use Tolua++.
#  CEGUI_FOUND, If false, do not try to use CEGUI
#  CEGUI_VERSION, the version as string "x.y.z"
#
# Input:
#  ENV{CEGUIDIR}, CEGUI path, optional
#
# Created by Matt Williams to find OGRE libraries
# Copyright © 2007, Matt Williams
#
# Modified by Nicolas Schlumberger to find CEGUI libraries
# and make it run on the Tardis-Infrastucture of the ETH Zurich
# Copyright 2007, Nicolas Schlumberger
#
# Redistribution and use is allowed according to the terms of the BSD license.
#
# Several changes and additions by Fabian 'x3n' Landau
# Lots of simplifications by Adrian Friedli and Reto Grieder
# Version checking and CEGUILua finding by Reto Grieder
#                 > www.orxonox.net <

# Find CEGUI headers
FIND_PATH(CEGUI_INCLUDE_DIR CEGUI.h
  PATHS $ENV{CEGUI_HOME}
  PATH_SUFFIXES include include/CEGUI cegui cegui/include
)

# Find CEGUI library
macro(_FIND_CEGUI_LIBRARY _var)
  find_library(${_var}
     NAMES
        ${ARGN}
     HINTS
		"$ENV{CEGUI_HOME}"
     PATH_SUFFIXES lib
  )
  mark_as_advanced(${_var})
endmacro()

macro(_CEGUI_APPEND_LIBRARIES _list _release)
   set(_debug ${_release}_DEBUG)
   if(${_debug})
      set(${_list} ${${_list}} optimized ${${_release}} debug ${${_debug}})
   else()
      set(${_list} ${${_list}} ${${_release}})
   endif()
endmacro()

find_path(CEGUI_INCLUDE_DIR NAMES CEGUI.h
  HINTS
	"$ENV{CEGUI_HOME}/cegui"
	"$ENV{CEGUI_HOME}/cegui/include"
  PATH_SUFFIXES CEGUI
)

# Find the libraries

_FIND_CEGUI_LIBRARY(CEGUI_BASE_LIBRARY        		CEGUIBase)
_FIND_CEGUI_LIBRARY(CEGUI_BASE_LIBRARY_DEBUG  		CEGUIBase_d)
_FIND_CEGUI_LIBRARY(CEGUI_OGRERENDER_LIBRARY       	CEGUIOgreRenderer)
_FIND_CEGUI_LIBRARY(CEGUI_OGRERENDER_LIBRARY_DEBUG 	CEGUIOgreRenderer_d)

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(CEGUI DEFAULT_MSG
    CEGUI_BASE_LIBRARY CEGUI_OGRERENDER_LIBRARY CEGUI_INCLUDE_DIR)

set(CEGUI_INCLUDE_DIRS ${CEGUI_INCLUDE_DIR})
if(CEGUI_FOUND)
   _CEGUI_APPEND_LIBRARIES(CEGUI_LIBRARIES CEGUI_BASE_LIBRARY)
   _CEGUI_APPEND_LIBRARIES(CEGUI_LIBRARIES CEGUI_OGRERENDER_LIBRARY)
endif()