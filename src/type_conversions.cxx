/**
 *  This file is a part of blacspp (see LICENSE)
 *
 *  Copyright (c) 2019-2020 David Williams-Young
 *  All rights reserved
 */
#include <blacspp/util/type_conversions.hpp>
#include <stdexcept>
#include <sstream>
#include <limits>

namespace blacspp {
namespace detail  {

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


  internal::blacs_int to_blacs_int( int64_t i ) {

    if( i >= std::numeric_limits<internal::blacs_int>::max() ) {
      std::stringstream ss;
      ss << "BLACSPP ENCOUNTERED INTEGER CONVERSION ERROR: "
         << "  * INTEGER INPUT = " << i 
         << "  * BLACS INT_MAX = " <<std::numeric_limits<internal::blacs_int>::max();

      throw std::runtime_error( ss.str() );
    }

    return i;

  }

}
}
