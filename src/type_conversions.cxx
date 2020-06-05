/**
 *  This file is a part of blacspp (see LICENSE)
 *
 *  Copyright (c) 2019-2020 David Williams-Young
 *  All rights reserved
 */
#include <blacspp/util/type_conversions.hpp>
namespace blacspp::detail {

  std::string type_string( const Triangle tri ) {
    if( tri == Upper ) return std::string( "Upper" );
    else               return std::string( "Lower" );
  }


  std::string type_string( const Diagonal diag ) {
    if( diag == Unit ) return std::string( "U" );
    else               return std::string( "N" );
  }

  std::string type_string( const Scope scope ) {
    if( scope == All )      return std::string( "All" );
    else if( scope == Row ) return std::string( "Row" );
    else                    return std::string( "Column" );
  }

  std::string type_string( const Topology top ) {
    return std::string( "i-ring" );
  }
}
