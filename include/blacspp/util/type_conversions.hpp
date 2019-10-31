#pragma once
#include <blacspp/types.hpp>
#include <string>

namespace blacspp::detail {

  extern std::string type_string( const Triangle tri );

  extern std::string type_string( const Diagonal diag );

  extern std::string type_string( const Scope scope );

  extern std::string type_string( const Topology top );

}
