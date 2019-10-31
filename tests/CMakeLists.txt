include( HandleCatch2 )

add_library( ut_framework ut.cxx )
target_link_libraries( ut_framework PUBLIC blacspp blacspp::catch2 )

add_executable( test_blacspp constructor.cxx send_recv.cxx broadcast.cxx )
target_link_libraries( test_blacspp PUBLIC ut_framework )

#find_library( CXXBLACS REQUIRED )
#add_executable( blacs_test blacs_test.cxx )
#target_link_libraries( blacs_test PUBLIC blacspp )
