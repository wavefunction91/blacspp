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

namespace blacspp {

  /// Integer type for BLACS operations
  using blacs_int = int32_t;

  /// Type for single precision complex floating point numbers
  using scomplex  = std::complex< float >;

  /// Type for double precision complex floating point numbers
  using dcomplex  = std::complex< double >;


  using process_coordinate = std::pair< blacs_int, blacs_int >;

  /**
   *  \brief A struct to manage basic BLACS grid information
   */
  struct blacs_grid_dim {
    blacs_int np_row; ///< Number of rows in process grid
    blacs_int np_col; ///< Number of columns in process grid
    blacs_int my_row; ///< Row coordinate of current process in process grid
    blacs_int my_col; ///< Column coordinate of currend process in process grid
  };


  /**
   *  \brief A struct to manage basic MPI information
   */
  class mpi_info {

    MPI_Comm  comm_; ///< MPI Communicator which defines MPI context
    blacs_int rank_; ///< Rank of current process in specified MPI context
    blacs_int size_; ///< Size of specified MPI context

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
    blacs_int rank() const;

    /**
     *  \brief Get size ofthe internal MPI context
     *  \returns the size of the MPI context
     */
    blacs_int size() const;

  };



  enum Triangle {
    Upper,
    Lower
  };

  enum Diagonal {
    Unit,
    NonUnit
  };

  enum Scope {
    All,
    Row,
    Column
  };

  enum Topology {
    IRing
  };

}
