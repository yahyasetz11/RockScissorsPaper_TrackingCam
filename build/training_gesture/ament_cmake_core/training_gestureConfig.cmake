# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_training_gesture_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED training_gesture_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(training_gesture_FOUND FALSE)
  elseif(NOT training_gesture_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(training_gesture_FOUND FALSE)
  endif()
  return()
endif()
set(_training_gesture_CONFIG_INCLUDED TRUE)

# output package information
if(NOT training_gesture_FIND_QUIETLY)
  message(STATUS "Found training_gesture: 0.0.0 (${training_gesture_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'training_gesture' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${training_gesture_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(training_gesture_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${training_gesture_DIR}/${_extra}")
endforeach()
