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
#include <vector>

namespace blacspp {

bool Grid::is_valid() const {
  if( ! context_ ) return false;
  else             return context_->mpi.comm() != MPI_COMM_NULL;
}


void Grid::barrier( Scope scope ) const noexcept {
  auto SCOPE = char( scope );
  wrappers::barrier( context(), &SCOPE );
}



Grid::Grid() : Grid( MPI_COMM_NULL, 0, 0 ){ }

Grid::Grid( MPI_Comm c, int64_t npr, int64_t npc, GridOrder order ) :
  context_( std::make_shared<detail::Context>( c ) ) {

  if( is_valid() ) {

    if( npr * npc != context_->mpi.size() )
      throw std::runtime_error("NPC * NPR != NPROCS");
    
    // Greate blacs grid
    const char order_char = char(order);
    context_->blacs_handle = 
      wrappers::grid_init( context_->system_handle, &order_char, npr, npc );

    // Grab the grid info
    grid_dim_ = wrappers::grid_info( context_->blacs_handle );

  }

}

Grid::Grid( MPI_Comm c, int64_t npr, int64_t npc, int64_t* map, int64_t ldmap ) :
  context_( std::make_shared<detail::Context>( c ) ) {

  if( is_valid() ) {

    // TODO check that the map is sane
    // TODO check that ldmap >= npr

    // Create a BLACS grid given the process map
    context_->blacs_handle = 
      wrappers::grid_map( context_->system_handle, map, ldmap, npr, npc );

    // Grab the grid info
    grid_dim_ = wrappers::grid_info( context_->blacs_handle );

  }

}


#if 0
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
    if( context_ >= 0 ) wrappers::grid_exit( context_ );
    wrappers::free_sys_handle( system_handle_ );
  }

}
#else

namespace detail {

Context::Context(MPI_Comm comm) : mpi(comm) {
  if( comm != MPI_COMM_NULL )
    system_handle = wrappers::blacs_from_sys( comm );
}

Context::~Context() noexcept {
  if( blacs_handle  >= 0 ) wrappers::grid_exit( blacs_handle );
  if( mpi.comm() != MPI_COMM_NULL ) wrappers::free_sys_handle( system_handle );
}

std::shared_ptr<Context> Context::clone() const {

  auto ptr = std::make_shared<Context>(mpi.comm());

  if( blacs_handle >= 0 ) {

    auto grid_dim = wrappers::grid_info( blacs_handle );
    std::vector<int64_t> pmap( grid_dim.np_row*grid_dim.np_col );
    for( int64_t pc = 0; pc < grid_dim.np_col; ++pc )
    for( int64_t pr = 0; pr < grid_dim.np_row; ++pr ) {
      pmap[ pr + pc*grid_dim.np_row ] = wrappers::pnum( blacs_handle, pr, pc );
    }
    ptr->blacs_handle = 
      wrappers::grid_map( ptr->system_handle, pmap.data(), grid_dim.np_row, 
                          grid_dim.np_row, grid_dim.np_col );

  } else ptr->blacs_handle = -1;

  return ptr;

}

}


Grid::Grid( const Grid& )     = default;
Grid::Grid( Grid&& ) noexcept = default;
Grid::~Grid() noexcept        = default;
Grid::Grid( std::shared_ptr<detail::Context> _context ) : context_(_context) { 

  if( is_valid() ) {
    // Grab the grid info
    grid_dim_ = wrappers::grid_info( context_->blacs_handle );
  }

}

Grid Grid::clone() const { 
  return Grid( context_->clone() );
}
#endif





Grid Grid::square_grid( const MPI_Comm& comm, GridOrder order ) {

  mpi_info info(comm);
 
  int64_t npr = std::sqrt( info.size() );
  int64_t npc = info.size() / npr; 

  while( npr * npc != info.size() ) {
    npr--;
    npc = info.size() / npr;
  }

  return Grid( comm, npr, npc, order );

}

}
