cmake_minimum_required( VERSION 3.13 FATAL_ERROR )
project( blacspp VERSION 0.0.0 LANGUAGES C CXX )

# Append local cmake directory to find CMAKE Modules
if( CMAKE_MODULE_PATH )
  list( APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
else()
  set( CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
endif()
list( APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules")

add_subdirectory( src )

if(NOT DEFINED BLACSPP_ENABLE_TESTS )
  set( BLACSPP_ENABLE_TESTS ON )
endif()

if( BLACSPP_ENABLE_TESTS )
  add_subdirectory( tests )
endif()
