/**
 *  This file is a part of blacspp (see LICENSE)
 *
 *  Copyright (c) 2019-2020 David Williams-Young
 *  All rights reserved
 */
#pragma once
#include <blacspp/types.hpp>
#include <memory>

namespace blacspp {

namespace detail {

struct Context {

  mpi_info mpi; ///< MPI information for underlying MPI communicator

  int64_t system_handle = -1;
  int64_t blacs_handle  = -1;

  Context(MPI_Comm comm);
  ~Context() noexcept;

  std::shared_ptr<Context> clone() const;

};

}

/**
 *  \brief A class which provides a C++ wrapper for a BLACS Grid.
 *
 *  Manages the lifetime and information pertaining to a BLACS grid.
 */
class Grid {

  blacs_grid_dim  grid_dim_; ///< Grid information of constructed grid

  //int64_t       system_handle_; ///< BLACS representation of the MPI communicator (system handle)
  //int64_t       context_;       ///< BLACS context representation of the BLACS grid
  std::shared_ptr<detail::Context> context_ = nullptr; ///< BLACS Context
  

#if 0
  /**
   *  \brief Construct a BLACS grid given preconstructed parameters.
   *
   *  Does not actually construct a BLACS grid, assumes passed information
   *  already represents a constructed BLACS grid.
   *
   *  Only used as a part of the move constructor to simplify the logic.
   *
   *  @param[in] dim      BLACS Grid information
   *  @param[in] info     MPI information
   *  @param[in] handle   BLACS system handle (must refer to already constructed BLACS handle)
   *  @param[in] context  BLACS context (must refer to an already constructed BLACS grid)
   *
   */
  Grid( blacs_grid_dim dim, mpi_info info, int64_t handle, int64_t context );
#endif

  Grid( std::shared_ptr<detail::Context> _context );

public:

  /**
   *  \brief Construct an invalid BLACS grid (MPI_COMM_NULL)
   *
   *  Not a valid BLACS grid, place holder for temporary contexts
   */
  Grid();

  /**
   *  \brief Construct a BLACS grid.
   *
   *  Constructs a BLACS grid from an MPI communicator.
   *  npr * npc must be equal to size of MPI communicator
   *
   *  @param[in]  c    MPI Communicator
   *  @param[in]  npr  Number of process rows
   *  @param[in]  npc  Number of process columns
   */
  Grid( MPI_Comm c, int64_t npr, int64_t npc, GridOrder order = GridOrder::RowMajor );


  /**
   *  \brief Construct a BLACS grid from a predefined process map
   *
   *  Constructs a BLACS grid from a predefined process map over an MPI 
   *  communicator.
   */
  Grid( MPI_Comm c, int64_t npr, int64_t npc, int64_t* map, int64_t ldmap );

  /**
   *  \brief Copy constructor.
   *
   *  Creates a clone of the passed grid with a distinct
   *  BLACS context.
   *
   *  @param[in] other BLACS grid to clone
   */
  Grid( const Grid& other );

  /**
   *  \brief Move constructor
   *
   *  Shallow copy of BLACS grid metadata from passed
   *  grid. Passes ownership of the passed BLACS context 
   *  and leaves passed grid in an invalid state (MPI_COMM_NULL).
   *
   *  @param[in] other BLACS grid to move
   */
  Grid( Grid&& other ) noexcept;  

  /**
   *  \brief Destory BLACS grid.
   *
   *  Trivial if grid is invalid.
   */
  ~Grid() noexcept;

  /**
   *  \brief Check if grid is valid.
   *
   *  @returns Whether the grid is valid
   */
  bool is_valid() const ;

  /**
   *  \brief Returns BLACS context.
   *  @returns BLACS context handle
   */
  inline int64_t context() const noexcept { 
    if(context_) return context_->blacs_handle; 
    else         return -1;
  }

  /**
   *  \brief Returns the number of rows in the BLACS grid.
   *  @returns Number of process rows
   */
  inline int64_t npr()     const noexcept { return grid_dim_.np_row; }

  /**
   *  \brief Returns the number of columns in the BLACS grid.
   *  @returns Number of process columns
   */
  inline int64_t npc()     const noexcept { return grid_dim_.np_col; }

  /**
   *  \brief Returns process row of this MPI rank
   *  @returns Process row corresponding to the current MPI rank
   */
  inline int64_t ipr()     const noexcept { return grid_dim_.my_row; }

  /**
   *  \brief Returns process column of this MPI rank
   *  @returns Process column corresponding to the current MPI rank
   */
  inline int64_t ipc()     const noexcept { return grid_dim_.my_col; }

  /**
   *  \brief Returns MPI communicator corresponding on which the BLACS grid has been constructed.
   *  @returns MPI communicator for the BLACS grid.
   */
  inline MPI_Comm  comm()    const noexcept { 
    if( is_valid() ) return context_->mpi.comm(); 
    else             return MPI_COMM_NULL;
  }





  void barrier( Scope ) const noexcept;



  Grid clone() const;



  /**
   *  \brief Constuct a close-to-square BLACS Grid.
   *
   *  Constructs as close to a square BLACS grid as
   *  is possible from the processes which constute
   *  the passed MPI communicator.
   *
   *  @param[in] comm MPI Communicator from which the BLACS grid will be constructed.
   *  @returns        Square BLACS grid.
   */
  static Grid square_grid( const MPI_Comm& comm, GridOrder order = GridOrder::RowMajor );
};

}
