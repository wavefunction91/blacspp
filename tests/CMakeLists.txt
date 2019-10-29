include( HandleGTest )

add_library( ut_framework ut.cxx )
target_link_libraries( ut_framework PUBLIC blacspp blacspp::gtest )
target_compile_features( ut_framework PUBLIC cxx_std_17 )

add_executable( constructor constructor.cxx send_recv.cxx )
target_link_libraries( constructor PUBLIC ut_framework )

#find_library( CXXBLACS REQUIRED )
add_executable( blacs_test blacs_test.cxx )
target_link_libraries( blacs_test PUBLIC blacspp )
