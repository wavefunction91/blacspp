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

// Send
template <typename T>
detail::enable_if_blacs_supported_t<T> 
  gesd2d( const blacs_int ICONTXT, const blacs_int M, const blacs_int N,
          const T* A, const blacs_int LDA, const blacs_int RDEST,
          const blacs_int CDEST );

template <typename T>
detail::enable_if_blacs_supported_t<T> 
  trsd2d( const blacs_int ICONTXT, const char* UPLO, const char* DIAG, 
          const blacs_int M, const blacs_int N, const T* A, const blacs_int LDA, 
          const blacs_int RDEST, const blacs_int CDEST );

// Recv
template <typename T>
detail::enable_if_blacs_supported_t<T> 
  gerv2d( const blacs_int ICONTXT, const blacs_int M, const blacs_int N,
          T* A, const blacs_int LDA, const blacs_int RSRC,
          const blacs_int CSRC );

template <typename T>
detail::enable_if_blacs_supported_t<T> 
  trrv2d( const blacs_int ICONTXT, const char* UPLO, const char* DIAG, 
          const blacs_int M, const blacs_int N, T* A, const blacs_int LDA, 
          const blacs_int RSRC, const blacs_int CSRC );

}
}
