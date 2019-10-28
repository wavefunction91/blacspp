#
# a simple c++ wrapper for blacs along with minimal extra functionality to 
# aid the the high-level development of distributed memory linear algebra.
# copyright (c) 2016-2018 david williams-young
#
# this program is free software: you can redistribute it and/or modify
# it under the terms of the gnu general public license as published by
# the free software foundation, either version 3 of the license, or
# (at your option) any later version.
#
# this program is distributed in the hope that it will be useful,
# but without any warranty; without even the implied warranty of
# merchantability or fitness for a particular purpose.  see the
# gnu general public license for more details.
#
# you should have received a copy of the gnu general public license
# along with this program.  if not, see <http://www.gnu.org/licenses/>.
#
#

# CQ GTest TARGET
add_library( blacspp::gtest INTERFACE IMPORTED )

# Try to find GTest
find_package( GTest QUIET )

if( GTEST_FOUND )
  
  message(STATUS "Found GTest!" )
  target_link_libraries( blacspp::gtest INTERFACE GTest::GTest )

else()

  # Pull GTest
  message(STATUS "Could not find GTest! Building..." )

  include( DownloadProject ) 
  download_project(
    PROJ                googletest
    GIT_REPOSITORY      https://github.com/google/googletest.git
    GIT_TAG             master
    UPDATE_DISCONNECTED 1
  )

  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

  target_link_libraries( blacspp::gtest INTERFACE gtest )

endif()
