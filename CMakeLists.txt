#
# This file is a part of blacspp (see LICENSE)
#
# Copyright (c) 2019-2020 David Williams-Young
# All rights reserved
#

cmake_minimum_required( VERSION 3.12 FATAL_ERROR )
project( blacspp VERSION 0.0.0 LANGUAGES C CXX )

# Append local cmake directory to find CMAKE Modules
if( CMAKE_MODULE_PATH )
  list( APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
else()
  set( CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
endif()


# Get Modifed BLAS/LAPACK/ScaLAPACK Modules
include( FetchContent )
FetchContent_Declare( linalg-cmake-modules 
  GIT_REPOSITORY https://github.com/wavefunction91/linalg-cmake-modules.git
  GIT_TAG        main
)
FetchContent_GetProperties( linalg-cmake-modules )
if( NOT linalg-cmake-modules_POPULATED )
  FetchContent_Populate( linalg-cmake-modules )
  list( APPEND CMAKE_MODULE_PATH ${linalg-cmake-modules_SOURCE_DIR} )
endif()

# Configure Options
include( CMakeDependentOption )
option( BLACSPP_ENABLE_ILP64 "Enable search for ILP64 ScaLAPACK bindings" OFF )
cmake_dependent_option( BLACSPP_FORCE_ILP64 "Force ILP64 - Fail if not found" OFF
                        "BLACSPP_ENABLE_ILP64" OFF )



add_subdirectory( src )

if(NOT DEFINED BLACSPP_ENABLE_TESTS )
  set( BLACSPP_ENABLE_TESTS ON )
endif()

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  include(CTest)
endif()

if( CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BLACSPP_ENABLE_TESTS AND BUILD_TESTING )
  add_subdirectory( tests )
endif()
