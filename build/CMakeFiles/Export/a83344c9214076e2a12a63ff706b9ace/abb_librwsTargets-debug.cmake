#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "abb_librws::abb_librws" for configuration "Debug"
set_property(TARGET abb_librws::abb_librws APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(abb_librws::abb_librws PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/abb_librws.lib"
  )

list(APPEND _cmake_import_check_targets abb_librws::abb_librws )
list(APPEND _cmake_import_check_files_for_abb_librws::abb_librws "${_IMPORT_PREFIX}/lib/abb_librws.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
