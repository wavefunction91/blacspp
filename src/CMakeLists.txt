set( BLACS_SRC broadcast.cxx
               combine.cxx
               send_recv.cxx
               support.cxx
               mpi_info.cxx
               grid.cxx
)

add_library( blacspp ${BLACS_SRC} )
target_compile_features( blacspp PUBLIC cxx_std_17 )

target_include_directories( blacspp PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  #$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_link_libraries( blacspp PUBLIC BLACS::BLACS )
