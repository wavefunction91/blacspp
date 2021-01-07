cmake_minimum_required( VERSION 3.17 FATAL_ERROR )
project( blacspp_as_subproject LANGUAGES C CXX )

find_package( blacspp REQUIRED )
add_executable( blacspp_linker_test blacspp_linker_test.cxx )
target_link_libraries( blacspp_linker_test PUBLIC blacspp::blacspp )
