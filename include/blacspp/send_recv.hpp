#pragma once
#include <blacspp/grid.hpp>
#include <blacspp/wrappers/send_recv.hpp>

namespace blacspp {

// Send

template <typename T>
detail::enable_if_blacs_supported_t<T>
  gesd2d( const Grid& grid, 
          const blacs_int M, const blacs_int N, const T* A, const blacs_int LDA,
          const blacs_int RDEST, const blacs_int CDEST ) {

  wrappers::gesd2d( grid.context(), M, N, A, LDA, RDEST, CDEST );

}

template <class Container>
std::enable_if_t< detail::has_data_member_v<Container> >
gesd2d( const Grid& grid, 
             const blacs_int M, const blacs_int N, const Container& A, 
             const blacs_int LDA, const blacs_int RDEST, const blacs_int CDEST ) {

  gesd2d( grid, M, N, A.data(), LDA, RDEST, CDEST );

}

template <class Container>
std::enable_if_t< detail::has_size_member_v<Container> >
gesd2d( const Grid& grid, const Container& A, 
             const blacs_int RDEST, const blacs_int CDEST ) {

  gesd2d( grid, A.size(), 1, A, A.size(), RDEST, CDEST );

}



template <typename T>
detail::enable_if_blacs_supported_t<T> 
  trsd2d( const Grid& grid, const char* UPLO, const char* DIAG, 
          const blacs_int M, const blacs_int N, const T* A, const blacs_int LDA, 
          const blacs_int RDEST, const blacs_int CDEST ) {

  wrappers::trsd2d( grid.context(), UPLO, DIAG, M, N, A, LDA, RDEST, CDEST );

}

template <class Container>
std::enable_if_t< detail::has_data_member_v<Container> >
trsd2d( const Grid& grid, const char* UPLO, const char* DIAG, 
             const blacs_int M, const blacs_int N, const Container& A, 
             const blacs_int LDA, const blacs_int RDEST, const blacs_int CDEST ) {

  trsd2d( grid, UPLO, DIAG, M, N, A.data(), LDA, RDEST, CDEST );

}


// Recv
  
template <typename T>
detail::enable_if_blacs_supported_t<T> 
  gerv2d( const Grid& grid, const blacs_int M, const blacs_int N,
          T* A, const blacs_int LDA, const blacs_int RSRC,
          const blacs_int CSRC ) {

  wrappers::gerv2d( grid.context(), M, N, A, LDA, RSRC, CSRC );

}

template <class Container>
std::enable_if_t< detail::has_data_member_v<Container> >
gerv2d( const Grid& grid, const blacs_int M, const blacs_int N,
             Container& A, const blacs_int LDA, const blacs_int RSRC,
             const blacs_int CSRC ) {

  gerv2d( grid, M, N, A.data(), LDA, RSRC, CSRC );

}

template <class Container>
std::enable_if_t< detail::has_size_member_v<Container> >
gerv2d( const Grid& grid, Container& A, 
             const blacs_int RSRC, const blacs_int CSRC ) {

  gerv2d( grid, A.size(), 1, A, A.size(), RSRC, CSRC );

}


template <typename T>
detail::enable_if_blacs_supported_t<T> 
  trrv2d( const Grid& grid, const char* UPLO, const char* DIAG, 
          const blacs_int M, const blacs_int N, T* A, const blacs_int LDA, 
          const blacs_int RSRC, const blacs_int CSRC ) {

  wrappers::trrv2d( grid.context(), UPLO, DIAG, M, N, A, LDA, RSRC, CSRC );

}

template <class Container>
std::enable_if_t< detail::has_data_member_v<Container> >
trrv2d( const Grid& grid, const char* UPLO, const char* DIAG, 
             const blacs_int M, const blacs_int N, Container& A, 
             const blacs_int LDA, const blacs_int RSRC, const blacs_int CSRC ) {

  trrv2d( grid, UPLO, DIAG, M, N, A.data(), LDA, RSRC, CSRC );

}


}
