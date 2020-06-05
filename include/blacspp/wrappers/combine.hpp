/**
 *  This file is a part of blacspp (see LICENSE)
 *
 *  Copyright (c) 2019-2020 David Williams-Young
 *  All rights reserved
 */
#pragma once
#include <blacspp/types.hpp>
#include <blacspp/util/sfinae.hpp>

namespace blacspp {
namespace wrappers {

// Element-wise sum
template <typename T>
detail::enable_if_blacs_supported_t<T> 
  gsum2d( const blacs_int ICONTXT, const char* SCOPE, const char* TOP, 
          const blacs_int M, const blacs_int N, T* A, const blacs_int LDA,
          const blacs_int RDEST, const blacs_int CDEST );

// Element-wise max
template <typename T>
detail::enable_if_blacs_supported_t<T> 
  gamx2d( const blacs_int ICONTXT, const char* SCOPE, const char* TOP, 
          const blacs_int M, const blacs_int N, T* A, const blacs_int LDA,
          blacs_int* RA, blacs_int* CA, const blacs_int RCFLAG, 
          const blacs_int RDEST, const blacs_int CDEST );

// Element-wise min
template <typename T>
detail::enable_if_blacs_supported_t<T> 
  gamn2d( const blacs_int ICONTXT, const char* SCOPE, const char* TOP, 
          const blacs_int M, const blacs_int N, T* A, const blacs_int LDA,
          blacs_int* RA, blacs_int* CA, const blacs_int RCFLAG, 
          const blacs_int RDEST, const blacs_int CDEST );

}
}
