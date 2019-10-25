#pragma once
#include <blacspp/types.hpp>
#include <blacspp/util/sfinae.hpp>

namespace blacspp {
namespace wrappers {

// Send
template <typename T>
detail::enable_if_blacs_supported_t<T> 
  gebs2d( const blacs_int ICONTXT, const char* SCOPE, const char* TOP, 
          const blacs_int M, const blacs_int N, const T* A, const blacs_int LDA );

template <typename T>
detail::enable_if_blacs_supported_t<T> 
  trbs2d( const blacs_int ICONTXT, const char* SCOPE, const char* TOP,
          const char* UPLO, const char* DIAG, const blacs_int M, const blacs_int N, 
          const T* A, const blacs_int LDA ); 

// Recv
template <typename T>
detail::enable_if_blacs_supported_t<T> 
  gebr2d( const blacs_int ICONTXT, const char* SCOPE, const char* TOP,
          const blacs_int M, const blacs_int N, T* A, const blacs_int LDA );

template <typename T>
detail::enable_if_blacs_supported_t<T> 
  trbr2d( const blacs_int ICONTXT, const char* SCOPE, const char* TOP,
          const char* UPLO, const char* DIAG, const blacs_int M, const blacs_int N, 
          T* A, const blacs_int LDA ); 

}
}
