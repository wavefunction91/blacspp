#include <catch2/catch.hpp>
#include <blacspp/grid.hpp>


TEST_CASE( "Default Constructor", "[constructor]" ) {

  blacspp::Grid grid;
  CHECK( not grid.is_valid() );

}

TEST_CASE( "Square Grid", "[constructor]" ) {

  blacspp::Grid grid = blacspp::Grid::square_grid(MPI_COMM_WORLD);

  blacspp::mpi_info mpi(MPI_COMM_WORLD);

  REQUIRE( grid.is_valid() );  
  CHECK( mpi.size() == (grid.npr() * grid.npc()) );

  auto npr = grid.npr();
  CHECK( grid.ipr() == (mpi.rank() / npr) );
  CHECK( grid.ipc() == (mpi.rank() % npr) );

}


TEST_CASE( "Copy Constructor", "[constructor]" ) {

  blacspp::Grid grid = blacspp::Grid::square_grid( MPI_COMM_WORLD );
  blacspp::Grid grid2( grid );

  REQUIRE( grid.is_valid()  );
  REQUIRE( grid2.is_valid() );

  CHECK( grid.npr()  == grid2.npr()  );
  CHECK( grid.npc()  == grid2.npc()  );
  CHECK( grid.ipr()  == grid2.ipr()  );
  CHECK( grid.ipc()  == grid2.ipc()  );
  CHECK( grid.comm() == grid2.comm() );

  CHECK( grid.context() != grid2.context() );

}

TEST_CASE( "Move Constructor", "[constructor]" ) {

  blacspp::Grid grid = blacspp::Grid::square_grid( MPI_COMM_WORLD );

  auto npr  = grid.npr();
  auto npc  = grid.npc();
  auto ipr  = grid.ipr();
  auto ipc  = grid.ipc();
  auto comm = grid.comm();
  auto context = grid.context();

  blacspp::Grid grid2( std::move(grid) );

  REQUIRE( grid2.is_valid() );  
  CHECK( not grid.is_valid() );  

  CHECK( npr     == grid2.npr()     );
  CHECK( npc     == grid2.npc()     );
  CHECK( ipr     == grid2.ipr()     );
  CHECK( ipc     == grid2.ipc()     );
  CHECK( comm    == grid2.comm()    );
  CHECK( context == grid2.context() );

}
