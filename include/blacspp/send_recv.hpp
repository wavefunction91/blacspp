/**
 *  This file is a part of blacspp (see LICENSE)
 *
 *  Copyright (c) 2019-2020 David Williams-Young
 *  All rights reserved
 */
#pragma once
#include <blacspp/grid.hpp>
#include <blacspp/wrappers/send_recv.hpp>
#include <blacspp/util/type_conversions.hpp>

namespace blacspp {


/**
 *  \brief General point-to-point 2D send.
 *
 *  Performs a general (rectangular) point-to-point 2D send on a BLACS grid.
 *  Sends a 2D buffer (col-major) to a specified process coordinate on the BLACS
 *  grid.
 *
 *  @tparam T Type of buffer to send. Must be BLACS enabled.
 *
 *  @param[in] grid  (local) BLACS grid which defined the communication context.
 *  @param[in] M     (local) Number of rows of the buffer to send
 *  @param[in] N     (local) Number of columns of the buffer to send
 *  @param[in] A     (local) Pointer of buffer to send
 *  @param[in] LDA   (local) Leading dimension of the buffer to send
 *  @param[in] RDEST (local) Process row coordinate of destination process
 *  @param[in] CDEST (local) Process column coordinate of desination process
 *
 */
template <typename T>
detail::enable_if_blacs_supported_t<T>
  gesd2d( const Grid& grid, 
          const int64_t M, const int64_t N, const T* A, const int64_t LDA,
          const int64_t RDEST, const int64_t CDEST ) {

  wrappers::gesd2d( grid.context(), M, N, A, LDA, RDEST, CDEST );

}


/**
 *  \brief General point-to-point 2D send.
 *
 *  Performs a general (rectangular) point-to-point 2D send on a BLACS grid.
 *  Sends a 2D buffer (col-major) to a specified process coordinate on the BLACS
 *  grid.
 *
 *  Sends a buffer which is managed by a C++ container.
 *
 *  @tparam Container Type of container which manages the memory of the buffer.
 *                    Must have Container::data() -> pointer member function.
 *
 *  @param[in] grid  (local) BLACS grid which defined the communication context.
 *  @param[in] M     (local) Number of rows of the buffer to send
 *  @param[in] N     (local) Number of columns of the buffer to send
 *  @param[in] A     (local) Buffer to send (managed by some container)
 *  @param[in] LDA   (local) Leading dimension of the buffer to send
 *  @param[in] RDEST (local) Process row coordinate of destination process
 *  @param[in] CDEST (local) Process column coordinate of desination process
 *
 */
template <class Container>
detail::enable_if_t< detail::has_data_member<Container>::value >
  gesd2d( const Grid& grid, 
          const int64_t M, const int64_t N, const Container& A, 
          const int64_t LDA, const int64_t RDEST, const int64_t CDEST ) {

  gesd2d( grid, M, N, A.data(), LDA, RDEST, CDEST );

}

/**
 *  \brief General point-to-point 2D send.
 *
 *  Performs a general (rectangular) point-to-point 2D send on a BLACS grid.
 *  Sends a 2D buffer (col-major) to a specified process coordinate on the BLACS
 *  grid.
 *
 *  Sends a buffer which is managed by a C++ container. Size of buffer deduced 
 *  from Container::size().
 *
 *  @tparam Container Type of container which manages the memory of the buffer.
 *                    Must have Container::data() -> pointer member function and
 *                    Container::size() -> std::size_t member function.
 *
 *  @param[in] grid  (local) BLACS grid which defined the communication context.
 *  @param[in] A     (local) Buffer to send (managed by some container)
 *  @param[in] RDEST (local) Process row coordinate of destination process
 *  @param[in] CDEST (local) Process column coordinate of desination process
 *
 */
template <class Container>
detail::enable_if_t< detail::has_size_member<Container>::value >
  gesd2d( const Grid& grid, const Container& A, 
          const int64_t RDEST, const int64_t CDEST ) {

  gesd2d( grid, A.size(), 1, A, A.size(), RDEST, CDEST );

}



/**
 *  \brief Triangular point-to-point 2D send.
 *
 *  Performs a triangular (upper/lower) point-to-point 2D send on a BLACS grid.
 *  Sends the specified triangular portion of a  2D buffer (col-major) to a specified 
 *  process coordinate on the BLACS grid.
 *
 *  @tparam T Type of buffer to send. Must be BLACS enabled.
 *
 *  @param[in] grid  (local) BLACS grid which defined the communication context.
 *  @param[in] UPLO  (local) Which triangle of the buffer to send (upper/lower)
 *  @param[in] DIAG  (local) Whether to imply that the diagonal of the buffer is unit.
 *  @param[in] M     (local) Number of rows of the buffer to send
 *  @param[in] N     (local) Number of columns of the buffer to send
 *  @param[in] A     (local) Pointer of buffer to send
 *  @param[in] LDA   (local) Leading dimension of the buffer to send
 *  @param[in] RDEST (local) Process row coordinate of destination process
 *  @param[in] CDEST (local) Process column coordinate of desination process
 *
 */
template <typename T>
detail::enable_if_blacs_supported_t<T> 
  trsd2d( const Grid& grid, const Uplo uplo, const Diag diag, 
          const int64_t M, const int64_t N, const T* A, const int64_t LDA, 
          const int64_t RDEST, const int64_t CDEST ) {

  auto UPLO = char( uplo );
  auto DIAG = char( diag );

  wrappers::trsd2d( grid.context(), &UPLO, &DIAG, M, N, A, LDA, RDEST, CDEST );

}

/**
 *  \brief Triangular point-to-point 2D send.
 *
 *  Performs a triangular (upper/lower) point-to-point 2D send on a BLACS grid.
 *  Sends the specified triangular portion of a  2D buffer (col-major) to a specified 
 *  process coordinate on the BLACS grid.
 *
 *  Sends a buffer which is managed by a C++ container.
 *
 *  @tparam Container Type of container which manages the memory of the buffer.
 *                    Must have Container::data() -> pointer member function.
 *
 *  @param[in] grid  (local) BLACS grid which defined the communication context.
 *  @param[in] UPLO  (local) Which triangle of the buffer to send (upper/lower)
 *  @param[in] DIAG  (local) Whether to imply that the diagonal of the buffer is unit.
 *  @param[in] M     (local) Number of rows of the buffer to send
 *  @param[in] N     (local) Number of columns of the buffer to send
 *  @param[in] A     (local) Buffer to send (managed by some container)
 *  @param[in] LDA   (local) Leading dimension of the buffer to send
 *  @param[in] RDEST (local) Process row coordinate of destination process
 *  @param[in] CDEST (local) Process column coordinate of desination process
 *
 */
template <class Container>
detail::enable_if_t< detail::has_data_member<Container>::value >
  trsd2d( const Grid& grid, const Uplo uplo, const Diag diag, 
          const int64_t M, const int64_t N, const Container& A, 
          const int64_t LDA, const int64_t RDEST, const int64_t CDEST ) {

  trsd2d( grid, uplo, diag, M, N, A.data(), LDA, RDEST, CDEST );

}














  
/**
 *  \brief General point-to-point 2D recieve.
 *
 *  Performs a general (rectangular) point-to-point 2D recieve on a BLACS grid.
 *  Recieves a 2D buffer (col-major) from a specified source process coordinate on the BLACS
 *  grid.
 *
 *  @tparam T Type of buffer to recieve. Must be BLACS enabled.
 *
 *  @param[in]     grid  (local) BLACS grid which defined the communication context.
 *  @param[in]     M     (local) Number of rows of the buffer to recieve
 *  @param[in]     N     (local) Number of columns of the buffer to recieve
 *  @param[in/out] A     (local) Pointer of buffer to store recieved data
 *  @param[in]     LDA   (local) Leading dimension of the buffer to store recieved data.
 *  @param[in]     RSRC  (local) Process row coordinate of source process
 *  @param[in]     CSRC  (local) Process column coordinate of source process
 *
 */
template <typename T>
detail::enable_if_blacs_supported_t<T> 
  gerv2d( const Grid& grid, const int64_t M, const int64_t N,
          T* A, const int64_t LDA, const int64_t RSRC,
          const int64_t CSRC ) {

  wrappers::gerv2d( grid.context(), M, N, A, LDA, RSRC, CSRC );

}

/**
 *  \brief General point-to-point 2D recieve.
 *
 *  Performs a general (rectangular) point-to-point 2D recieve on a BLACS grid.
 *  Recieves a 2D buffer (col-major) from a specified source process coordinate on the BLACS
 *  grid.
 *
 *  Recieve buffer managed by C++ container
 *
 *  @tparam Container Type of container which manages the memory of the revieve buffer.
 *                    Must have Container::data() -> pointer member function.
 *
 *  @param[in]     grid  (local) BLACS grid which defined the communication context.
 *  @param[in]     M     (local) Number of rows of the buffer to recieve
 *  @param[in]     N     (local) Number of columns of the buffer to recieve
 *  @param[in/out] A     (local) Recieve buffer (managed by some container)
 *  @param[in]     LDA   (local) Leading dimension of the buffer to store recieved data.
 *  @param[in]     RSRC  (local) Process row coordinate of source process
 *  @param[in]     CSRC  (local) Process column coordinate of source process
 *
 */
template <class Container>
detail::enable_if_t< detail::has_data_member<Container>::value >
  gerv2d( const Grid& grid, const int64_t M, const int64_t N,
          Container& A, const int64_t LDA, const int64_t RSRC,
          const int64_t CSRC ) {

  gerv2d( grid, M, N, A.data(), LDA, RSRC, CSRC );

}

/**
 *  \brief General point-to-point 2D recieve.
 *
 *  Performs a general (rectangular) point-to-point 2D recieve on a BLACS grid.
 *  Recieves a 2D buffer (col-major) from a specified source process coordinate on the BLACS
 *  grid.
 *
 *  Recieve buffer managed by C++ container. Size of buffer deduced from Container::size()
 *
 *  @tparam Container Type of container which manages the memory of the revieve buffer.
 *                    Must have Container::data() -> pointer member function and
 *                    Container::size() -> std::size_t member function.
 *
 *  @param[in]     grid  (local) BLACS grid which defined the communication context.
 *  @param[in/out] A     (local) Recieve buffer (managed by some container)
 *  @param[in]     RSRC  (local) Process row coordinate of source process
 *  @param[in]     CSRC  (local) Process column coordinate of source process
 *
 */
template <class Container>
detail::enable_if_t< detail::has_size_member<Container>::value >
  gerv2d( const Grid& grid, Container& A, 
          const int64_t RSRC, const int64_t CSRC ) {

  gerv2d( grid, A.size(), 1, A, A.size(), RSRC, CSRC );

}


/**
 *  \brief Triangular point-to-point 2D recieve.
 *
 *  Performs a triangular (upper/lower) point-to-point 2D recieve on a BLACS grid.
 *  Recieves the specified triangular portin of a 2D buffer (col-major) from a 
 *  specified source process coordinate on the BLACS grid.
 *
 *  @tparam T Type of buffer to recieve. Must be BLACS enabled.
 *
 *  @param[in]     grid  (local) BLACS grid which defined the communication context.
 *  @param[in]     UPLO  (local) Which triangle of the buffer to recieve (upper/lower)
 *  @param[in]     DIAG  (local) Whether to imply that the diagonal of the buffer is unit.
 *  @param[in]     M     (local) Number of rows of the buffer to recieve
 *  @param[in]     N     (local) Number of columns of the buffer to recieve
 *  @param[in/out] A     (local) Pointer of buffer to store recieved data
 *  @param[in]     LDA   (local) Leading dimension of the buffer to store recieved data.
 *  @param[in]     RSRC  (local) Process row coordinate of source process
 *  @param[in]     CSRC  (local) Process column coordinate of source process
 *
 */
template <typename T>
detail::enable_if_blacs_supported_t<T> 
  trrv2d( const Grid& grid, const Uplo uplo, const Diag diag, 
          const int64_t M, const int64_t N, T* A, const int64_t LDA, 
          const int64_t RSRC, const int64_t CSRC ) {

  auto UPLO = char( uplo );
  auto DIAG = char( diag );

  wrappers::trrv2d( grid.context(), &UPLO, &DIAG, M, N, A, LDA, RSRC, CSRC );

}

/**
 *  \brief Triangular point-to-point 2D recieve.
 *
 *  Performs a triangular (upper/lower) point-to-point 2D recieve on a BLACS grid.
 *  Recieves the specified triangular portin of a 2D buffer (col-major) from a 
 *  specified source process coordinate on the BLACS grid.
 *
 *  Recieve buffer managed by C++ container
 *
 *  @tparam Container Type of container which manages the memory of the revieve buffer.
 *                    Must have Container::data() -> pointer member function.
 *
 *  @param[in]     grid  (local) BLACS grid which defined the communication context.
 *  @param[in]     UPLO  (local) Which triangle of the buffer to recieve (upper/lower)
 *  @param[in]     DIAG  (local) Whether to imply that the diagonal of the buffer is unit.
 *  @param[in]     M     (local) Number of rows of the buffer to recieve
 *  @param[in]     N     (local) Number of columns of the buffer to recieve
 *  @param[in/out] A     (local) Recieve buffer (managed by some container)
 *  @param[in]     LDA   (local) Leading dimension of the buffer to store recieved data.
 *  @param[in]     RSRC  (local) Process row coordinate of source process
 *  @param[in]     CSRC  (local) Process column coordinate of source process
 *
 */
template <class Container>
detail::enable_if_t< detail::has_data_member<Container>::value >
  trrv2d( const Grid& grid,  const Uplo uplo, const Diag diag,
          const int64_t M, const int64_t N, Container& A, 
          const int64_t LDA, const int64_t RSRC, const int64_t CSRC ) {

  trrv2d( grid, uplo, diag, M, N, A.data(), LDA, RSRC, CSRC );

}


}
