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
