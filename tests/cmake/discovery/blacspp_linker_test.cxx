#include <blacspp/grid.hpp>

int main() {
  MPI_Init( NULL, NULL );
  {
    blacspp::Grid grid = blacspp::Grid::square_grid( MPI_COMM_WORLD );
  }
  MPI_Finalize();
}
