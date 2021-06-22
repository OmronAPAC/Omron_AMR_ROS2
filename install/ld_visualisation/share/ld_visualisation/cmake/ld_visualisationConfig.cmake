# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_ld_visualisation_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED ld_visualisation_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(ld_visualisation_FOUND FALSE)
  elseif(NOT ld_visualisation_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(ld_visualisation_FOUND FALSE)
  endif()
  return()
endif()
set(_ld_visualisation_CONFIG_INCLUDED TRUE)

# output package information
if(NOT ld_visualisation_FIND_QUIETLY)
  message(STATUS "Found ld_visualisation: 0.0.0 (${ld_visualisation_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'ld_visualisation' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${ld_visualisation_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(ld_visualisation_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${ld_visualisation_DIR}/${_extra}")
endforeach()
