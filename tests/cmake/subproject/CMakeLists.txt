cmake_minimum_required( VERSION 3.17 FATAL_ERROR )
project( blacspp_as_subproject LANGUAGES C CXX )

if( NOT GIT_REVISION )
  # Get current Git Revision
  find_package( Git REQUIRED )
  execute_process( 
    COMMAND ${GIT_EXECUTABLE} rev-parse HEAD
    OUTPUT_VARIABLE GIT_REVISION
    ERROR_QUIET
  )
  string( STRIP "${GIT_REVISION}" GIT_REVISION )
endif()

message( STATUS "Pulling GIT_REVISION = ${GIT_REVISION}" )

include( FetchContent )
FetchContent_Declare( blacspp
  GIT_REPOSITORY https://github.com/wavefunction91/blacspp.git
  GIT_TAG        ${GIT_REVISION}
)
FetchContent_MakeAvailable( blacspp )

add_executable( blacspp_linker_test blacspp_linker_test.cxx )
target_link_libraries( blacspp_linker_test PUBLIC blacspp::blacspp )
