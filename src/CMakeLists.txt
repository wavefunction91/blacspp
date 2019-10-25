set( BLACS_SRC broadcast.cxx
               combine.cxx
               send_recv.cxx
               support.cxx
)

add_library( blacspp ${BLACS_SRC} )
target_compile_features( blacspp PUBLIC cxx_std_14 )

target_include_directories( blacspp PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
