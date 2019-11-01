cmake_minimum_required( VERSION 3.13 FATAL_ERROR )
project( blacspp_cmake_test LANGUAGES CXX C )

find_package( blacspp REQUIRED )
add_executable( blacspp_cmake_test test.cxx )
target_link_libraries( blacspp_cmake_test PUBLIC blacspp::blacspp )
