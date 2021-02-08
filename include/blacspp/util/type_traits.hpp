/**
 *  This file is a part of blacspp (see LICENSE)
 *
 *  Copyright (c) 2019-2020 David Williams-Young
 *  All rights reserved
 */
#pragma once
#include <blacspp/types.hpp>
#include <type_traits>

namespace blacspp {
namespace detail {

#if __cplusplus < 201402L
  template <bool B, class T = void>
  using enable_if_t = typename std::enable_if<B,T>::type;
#else
  template <bool B, class T = void>
  using enable_if_t = std::enable_if_t<B,T>;
#endif

#if __cplusplus < 201703L
  template <class...>
  using void_t = void;
#else
  template <class... Args>
  using void_t = std::void_t<Args...>;
#endif

  /**
   *  \brief A SFINAE struct to check if a type is BLACS enabled.
   *  
   *  @tparam T Type to query for BLACS support.
   *
   *  Type is queried by blacs_supported<T>::value (true/false)
   *  
   *  The following types are BLACS enabled:
   *    - blacs_int (i)
   *    - float     (s)
   *    - double    (d)
   *    - scomplex  (c)
   *    - dcomplex  (z)
   */
  template <typename T>
  struct blacs_supported : public std::false_type { };

  template<>
  struct blacs_supported< internal::blacs_int > : public std::true_type { };
  template<>
  struct blacs_supported< float >     : public std::true_type { };
  template<>
  struct blacs_supported< double >    : public std::true_type { };
  template<>
  struct blacs_supported< internal::scomplex >  : public std::true_type { };
  template<>
  struct blacs_supported< internal::dcomplex >  : public std::true_type { };

  template <typename T, typename U = void>
  using enable_if_blacs_supported_t = 
    typename std::enable_if< blacs_supported<T>::value, U >::type;


  template <typename T, typename = blacspp::detail::void_t<>>
  struct has_data_member : public std::false_type { };

  template <typename T>
  struct has_data_member< T,
    blacspp::detail::void_t< decltype( std::declval<T>().data() ) >
  > : public std::true_type { };

#if __cplusplus >= 201703L
  template <typename T>
  inline constexpr bool has_data_member_v = has_data_member<T>::value;
#endif

  template <typename T, typename = blacspp::detail::void_t<>>
  struct has_size_member : public std::false_type { };

  template <typename T>
  struct has_size_member< T,
    blacspp::detail::void_t< decltype( std::declval<T>().size() ) >
  > : public std::true_type { };

#if __cplusplus >= 201703L
  template <typename T>
  inline constexpr bool has_size_member_v = has_size_member<T>::value;
#endif



}
}
