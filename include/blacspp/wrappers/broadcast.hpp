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
  gebs2d( const int64_t ICONTXT, const char* SCOPE, const char* TOP, 
          const int64_t M, const int64_t N, const T* A, const int64_t LDA );

template <typename T>
detail::enable_if_blacs_supported_t<T> 
  trbs2d( const int64_t ICONTXT, const char* SCOPE, const char* TOP,
          const char* UPLO, const char* DIAG, const int64_t M, const int64_t N, 
          const T* A, const int64_t LDA ); 

// Recv
template <typename T>
detail::enable_if_blacs_supported_t<T> 
  gebr2d( const int64_t ICONTXT, const char* SCOPE, const char* TOP,
          const int64_t M, const int64_t N, T* A, const int64_t LDA );

template <typename T>
detail::enable_if_blacs_supported_t<T> 
  trbr2d( const int64_t ICONTXT, const char* SCOPE, const char* TOP,
          const char* UPLO, const char* DIAG, const int64_t M, const int64_t N, 
          T* A, const int64_t LDA ); 

}
}
