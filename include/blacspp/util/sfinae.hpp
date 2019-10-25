#pragma once
#include <blacspp/types.hpp>
#include <type_traits>

namespace blacspp {
namespace detail {

  template <typename T>
  struct blacs_supported : public std::false_type { };

  template<>
  struct blacs_supported< blacs_int > : public std::true_type { };
  template<>
  struct blacs_supported< float >     : public std::true_type { };
  template<>
  struct blacs_supported< double >    : public std::true_type { };
  template<>
  struct blacs_supported< scomplex >  : public std::true_type { };
  template<>
  struct blacs_supported< dcomplex >  : public std::true_type { };

  template <typename T, typename U = void>
  using enable_if_blacs_supported_t = 
    typename std::enable_if< blacs_supported<T>::value, U >::type;

}
}
