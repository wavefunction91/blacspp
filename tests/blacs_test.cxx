#include <blacspp/grid.hpp>
#include <blacspp/send_recv.hpp>

#include <vector>

int main () {

  MPI_Init(NULL,NULL);


  {
  blacspp::Grid grid (MPI_COMM_WORLD, 2, 2); 
  blacspp::Grid grid2( grid ); 


  blacspp::mpi_info mpi_world(MPI_COMM_WORLD);
  std::vector<int32_t> A_send = { mpi_world.rank() };

  std::vector<int32_t> A_recv( A_send.size(), -1 );

  if( grid.ipc() == 0 )
    blacspp::gesd2d( grid, A_send, grid.ipr(), 1 );
  else
    blacspp::gerv2d( grid, A_recv, grid.ipr(), 0 );

  printf("%d, %d, %d\n", mpi_world.rank(), A_send[0], A_recv[0] );


  }


  MPI_Finalize();
}
