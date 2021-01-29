/**
 *  This file is a part of blacspp (see LICENSE)
 *
 *  Copyright (c) 2019-2020 David Williams-Young
 *  All rights reserved
 */
#pragma once

#include <complex>
#include <mpi.h>
#include <utility>

#include <blacspp/config.hpp>

namespace blacspp {

namespace internal {

  /// Integer type for BLACS operations
  #ifdef SCALAPACK_IS_ILP64
  using blacs_int = int64_t;
  #else
  using blacs_int = int32_t;
  #endif

  /// Type for single precision complex floating point numbers
  using scomplex  = std::complex< float >;

  /// Type for double precision complex floating point numbers
  using dcomplex  = std::complex< double >;


  using mpi_int = int32_t; // TODO: handle 64-bit MPI

}


  using process_coordinate = std::pair< int64_t, int64_t >;

  /**
   *  \brief A struct to manage basic BLACS grid information
   */
  struct blacs_grid_dim {
    int64_t np_row; ///< Number of rows in process grid
    int64_t np_col; ///< Number of columns in process grid
    int64_t my_row; ///< Row coordinate of current process in process grid
    int64_t my_col; ///< Column coordinate of currend process in process grid
  };


  /**
   *  \brief A struct to manage basic MPI information
   */
  class mpi_info {

    MPI_Comm  comm_; ///< MPI Communicator which defines MPI context
    int64_t rank_; ///< Rank of current process in specified MPI context
    int64_t size_; ///< Size of specified MPI context

  public:

    /**
     *  \brief Construct an mpi_info object
     *
     *   Cache basic MPI information for specified MPI context
     *
     *   @param[in] c MPI Communicator which defines the MPI context
     */
    mpi_info( MPI_Comm c = MPI_COMM_WORLD );


    /**
     *  \brief Get internal MPI communicator
     *  @returns the internal MPI communicator
     */
    MPI_Comm  comm() const;

    /**
     *  \brief Get rank of current process in the internal MPI context
     *  \returns the rank of current MPI process
     */
    int64_t rank() const;

    /**
     *  \brief Get size ofthe internal MPI context
     *  \returns the size of the MPI context
     */
    int64_t size() const;

  };



  enum class Uplo : char {
    Upper = 'U',
    Lower = 'L'
  };

  enum class Diag : char {
    Unit    = 'U',
    NonUnit = 'N'
  };

  enum class Scope : char {
    All     = 'A',
    Row     = 'R',
    Column  = 'C'
  };

  enum class Topology : char {
    IRing = 'I'
  };

  enum class GridOrder : char {
    RowMajor = 'R',
    ColMajor = 'C'
  };

}
