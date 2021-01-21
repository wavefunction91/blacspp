/**
 *  This file is a part of blacspp (see LICENSE)
 *
 *  Copyright (c) 2019-2020 David Williams-Young
 *  All rights reserved
 */
#pragma once
#include <blacspp/types.hpp>
#include <string>

namespace blacspp {
namespace detail  {

  extern std::string type_string( const Triangle tri );

  extern std::string type_string( const Diagonal diag );

  extern std::string type_string( const Scope scope );

  extern std::string type_string( const Topology top );

  extern internal::blacs_int to_blacs_int( int64_t );

}
}
