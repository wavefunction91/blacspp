#find_library( CXXBLACS REQUIRED )
add_executable( blacs_test blacs_test.cxx )
target_link_libraries( blacs_test PUBLIC blacspp )
