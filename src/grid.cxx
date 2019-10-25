#include <blacspp/grid.hpp>
#include <blacspp/wrappers/support.hpp>

#include <cstdio>

namespace blacspp {

Grid::Grid( MPI_Comm c, blacs_int mb, blacs_int nb, blacs_int npr, blacs_int npc ) :
  mpi_info_( c ), mb_( mb ), nb_( nb ) {

  if( not (npc and npr) ) 
    throw std::runtime_error("NPC * NPR == 0");

  if( npr * npc > mpi_info_.size() )
    throw std::runtime_error("NPC * NPR > NPROCS");

  // Create system handle
  system_handle_ = wrappers::blacs_from_sys( c );
  
  // Greate blacs grid
  context_ = wrappers::grid_init( system_handle_, "row-major", npr, npc );

  printf("%d, %d\n", system_handle_, context_ );

  // Grab the grid info
  grid_dim_ = wrappers::grid_info( context_ );

}


Grid::Grid( const Grid& other ) :
  Grid( other.mpi_info_.comm(), other.mb_, other.nb_, 
        other.grid_dim_.np_row, other.grid_dim_.np_col ){ }


Grid::~Grid() noexcept {

  wrappers::grid_exit( context_ );
  wrappers::free_sys_handle( system_handle_ );

}


}
