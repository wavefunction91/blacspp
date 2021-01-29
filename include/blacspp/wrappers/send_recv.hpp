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

// Send
template <typename T>
detail::enable_if_blacs_supported_t<T> 
  gesd2d( const int64_t ICONTXT, const int64_t M, const int64_t N,
          const T* A, const int64_t LDA, const int64_t RDEST,
          const int64_t CDEST );

template <typename T>
detail::enable_if_blacs_supported_t<T> 
  trsd2d( const int64_t ICONTXT, const char* UPLO, const char* DIAG, 
          const int64_t M, const int64_t N, const T* A, const int64_t LDA, 
          const int64_t RDEST, const int64_t CDEST );

// Recv
template <typename T>
detail::enable_if_blacs_supported_t<T> 
  gerv2d( const int64_t ICONTXT, const int64_t M, const int64_t N,
          T* A, const int64_t LDA, const int64_t RSRC,
          const int64_t CSRC );

template <typename T>
detail::enable_if_blacs_supported_t<T> 
  trrv2d( const int64_t ICONTXT, const char* UPLO, const char* DIAG, 
          const int64_t M, const int64_t N, T* A, const int64_t LDA, 
          const int64_t RSRC, const int64_t CSRC );

}
}
