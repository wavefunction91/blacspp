#include <blacspp/grid.hpp>
#include <blacspp/send_recv.hpp>

#include <vector>
#include <iostream>

int main () {

  MPI_Init(NULL,NULL);


  {
  blacspp::Grid grid = blacspp::Grid::square_grid(MPI_COMM_WORLD); 
  blacspp::Grid grid2( grid ); 
  blacspp::Grid grid3( grid2 );
  blacspp::Grid grid4( std::move(grid3) );

  if( grid.ipr() == 0 and grid.ipc() == 0 )
    std::cout << std::boolalpha << grid.is_valid() << ", " << grid2.is_valid() << ", " << grid3.is_valid() << ", " << grid4.is_valid() << std::endl;

/*
  blacspp::mpi_info mpi_world(MPI_COMM_WORLD);
  std::vector<int32_t> A_send = { mpi_world.rank() };

  std::vector<int32_t> A_recv( A_send.size(), -1 );

  if( grid.ipc() == 0 )
    blacspp::gesd2d( grid, A_send, grid.ipr(), 1 );
  else
    blacspp::gerv2d( grid, A_recv, grid.ipr(), 0 );

  printf("%d, %d, %d\n", mpi_world.rank(), A_send[0], A_recv[0] );
*/


  }


  MPI_Finalize();
}
