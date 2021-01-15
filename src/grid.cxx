/**
 *  This file is a part of blacspp (see LICENSE)
 *
 *  Copyright (c) 2019-2020 David Williams-Young
 *  All rights reserved
 */
#include <blacspp/grid.hpp>
#include <blacspp/wrappers/support.hpp>
#include <blacspp/util/type_conversions.hpp>

#include <cstdio>

namespace blacspp {

bool Grid::is_valid() const {
  return mpi_info_.comm() != MPI_COMM_NULL;
}


void Grid::barrier( Scope scope ) const noexcept {
  auto SCOPE = detail::type_string( scope );
  wrappers::barrier( context(), SCOPE.c_str() );
}



Grid::Grid() : Grid( MPI_COMM_NULL, 0, 0 ){ }

Grid::Grid( MPI_Comm c, int64_t npr, int64_t npc ) : mpi_info_( c ) {

  if( is_valid() ) {

    if( npr * npc != mpi_info_.size() )
      throw std::runtime_error("NPC * NPR != NPROCS");

    // Create system handle
    system_handle_ = wrappers::blacs_from_sys( c );
    
    // Greate blacs grid
    context_ = wrappers::grid_init( system_handle_, "row-major", npr, npc );

    // Grab the grid info
    grid_dim_ = wrappers::grid_info( context_ );

  }

}

Grid::Grid( blacs_grid_dim dim, mpi_info mpi, int64_t handle, int64_t context ) :
  grid_dim_(dim), mpi_info_(mpi), system_handle_(handle), context_(context){ }

Grid::Grid( const Grid& other ) :
  Grid( other.mpi_info_.comm(), other.grid_dim_.np_row, other.grid_dim_.np_col ){ }

Grid::Grid( Grid&& other ) noexcept :
  Grid( other.grid_dim_, other.mpi_info_, other.system_handle_, other.context_ ) {

  other.mpi_info_ = mpi_info( MPI_COMM_NULL );

}


Grid::~Grid() noexcept {

  if( is_valid() ) {
    wrappers::grid_exit( context_ );
    wrappers::free_sys_handle( system_handle_ );
  }

}



Grid Grid::square_grid( const MPI_Comm& comm ) {

  mpi_info info(comm);
 
  int64_t npr = std::sqrt( info.size() );
  int64_t npc = info.size() / npr; 

  while( npr * npc != info.size() ) {
    npr--;
    npc = info.size() / npr;
  }

  return Grid( comm, npr, npc );

}

}
