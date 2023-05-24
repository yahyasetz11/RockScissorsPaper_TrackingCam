# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_opencamera_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED opencamera_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(opencamera_FOUND FALSE)
  elseif(NOT opencamera_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(opencamera_FOUND FALSE)
  endif()
  return()
endif()
set(_opencamera_CONFIG_INCLUDED TRUE)

# output package information
if(NOT opencamera_FIND_QUIETLY)
  message(STATUS "Found opencamera: 0.0.0 (${opencamera_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'opencamera' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${opencamera_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(opencamera_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${opencamera_DIR}/${_extra}")
endforeach()
