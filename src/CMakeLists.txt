#
# This file is a part of blacspp (see LICENSE)
#
# Copyright (c) 2019-2020 David Williams-Young
# All rights reserved
#
find_package( BLACS REQUIRED )

set( BLACS_SRC broadcast.cxx
               combine.cxx
               send_recv.cxx
               support.cxx
               mpi_info.cxx
               grid.cxx
               type_conversions.cxx
)

set( BLACS_HEADERS broadcast.hpp
                   grid.hpp
                   information.hpp
                   send_recv.hpp
                   types.hpp
)
set( BLACS_UTIL_HEADERS
                   util/sfinae.hpp
                   util/type_conversions.hpp
)
set( BLACS_WRAPPER_HEADERS
                   wrappers/broadcast.hpp
                   wrappers/combine.hpp
                   wrappers/send_recv.hpp
                   wrappers/support.hpp
)


list( TRANSFORM BLACS_HEADERS PREPEND ${PROJECT_SOURCE_DIR}/include/blacspp/ )
list( TRANSFORM BLACS_UTIL_HEADERS PREPEND ${PROJECT_SOURCE_DIR}/include/blacspp/ )
list( TRANSFORM BLACS_WRAPPER_HEADERS PREPEND ${PROJECT_SOURCE_DIR}/include/blacspp/ )


add_library( blacspp ${BLACS_SRC} )
target_compile_features( blacspp PUBLIC cxx_std_17 )

target_include_directories( blacspp PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  #$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_link_libraries( blacspp PUBLIC BLACS::BLACS )





# INSTALL rules
add_library( blacspp::blacspp ALIAS blacspp )

include( GNUInstallDirs )

# TARGETS
install( TARGETS blacspp
  EXPORT blacspp-targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

set_target_properties( blacspp PROPERTIES EXPORT_NAME blacspp )

# Install Headers
install( 
  FILES ${BLACS_HEADERS} 
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/blacspp 
)
install( 
  FILES ${BLACS_UTIL_HEADERS} 
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/blacspp/util 
)
install( 
  FILES ${BLACS_WRAPPER_HEADERS} 
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/blacspp/wrappers 
)


# Export target to scripe
set( INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/blacspp )
install( EXPORT blacspp-targets
  FILE         blacspp-targets.cmake
  NAMESPACE    blacspp::
  DESTINATION  ${INSTALL_CONFIGDIR}
)


# Create config-version.cmake file
include( CMakePackageConfigHelpers )
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/blacspp-config-version.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)



# Setup blacspp-config.cmake
configure_package_config_file(
  ${PROJECT_SOURCE_DIR}/cmake/blacspp-config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/blacspp-config.cmake
  INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

# Install misc cmake modules
install( FILES
  ${PROJECT_SOURCE_DIR}/cmake/modules/CommonFunctions.cmake
  ${PROJECT_SOURCE_DIR}/cmake/modules/FindBLACS.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/blacspp-config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/blacspp-config-version.cmake
  DESTINATION ${INSTALL_CONFIGDIR}
)
  


