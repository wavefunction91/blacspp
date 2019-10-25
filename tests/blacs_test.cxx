#include <blacspp/grid.hpp>

int main () {

  MPI_Init(NULL,NULL);


  {
  blacspp::Grid grid (MPI_COMM_WORLD, 2, 2, 2, 2); 
  blacspp::Grid grid2( grid ); 
  }


  MPI_Finalize();
}
