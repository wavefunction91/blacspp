/**
 *  This file is a part of blacspp (see LICENSE)
 *
 *  Copyright (c) 2019-2020 David Williams-Young
 *  All rights reserved
 */
#pragma once
#include <blacspp/types.hpp>
#include <blacspp/util/type_traits.hpp>

namespace blacspp {
namespace wrappers {

// Element-wise sum
template <typename T>
detail::enable_if_blacs_supported_t<T> 
  gsum2d( const int64_t ICONTXT, const char* SCOPE, const char* TOP, 
          const int64_t M, const int64_t N, T* A, const int64_t LDA,
          const int64_t RDEST, const int64_t CDEST );

// Element-wise max
template <typename T>
detail::enable_if_blacs_supported_t<T> 
  gamx2d( const int64_t ICONTXT, const char* SCOPE, const char* TOP, 
          const int64_t M, const int64_t N, T* A, const int64_t LDA,
          int64_t* RA, int64_t* CA, const int64_t RCFLAG, 
          const int64_t RDEST, const int64_t CDEST );

// Element-wise min
template <typename T>
detail::enable_if_blacs_supported_t<T> 
  gamn2d( const int64_t ICONTXT, const char* SCOPE, const char* TOP, 
          const int64_t M, const int64_t N, T* A, const int64_t LDA,
          int64_t* RA, int64_t* CA, const int64_t RCFLAG, 
          const int64_t RDEST, const int64_t CDEST );

}
}
