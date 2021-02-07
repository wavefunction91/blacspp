/**
 *  This file is a part of blacspp (see LICENSE)
 *
 *  Copyright (c) 2019-2020 David Williams-Young
 *  All rights reserved
 */
#include <catch2/catch.hpp>
#include <blacspp/grid.hpp>
#include <iostream>


TEST_CASE( "Default Constructor", "[constructor]" ) {

  blacspp::Grid grid;
  CHECK( not grid.is_valid() );
  CHECK( grid.context() == -1 );
  CHECK( grid.comm()    == MPI_COMM_NULL );

}

TEST_CASE( "Square Grid", "[constructor]" ) {

  blacspp::Grid grid = blacspp::Grid::square_grid(MPI_COMM_WORLD);

  blacspp::mpi_info mpi(MPI_COMM_WORLD);

  REQUIRE( grid.is_valid() );  
  CHECK( mpi.size() == (grid.npr() * grid.npc()) );
  CHECK( grid.context() >= 0 );

}

TEST_CASE( "Row Major Grid", "[constructor]" ) {

  blacspp::Grid grid = blacspp::Grid::square_grid(MPI_COMM_WORLD, blacspp::GridOrder::RowMajor);
  blacspp::mpi_info mpi(MPI_COMM_WORLD);

  auto npr = grid.npr();
  CHECK( grid.ipr() == (mpi.rank() / npr) );
  CHECK( grid.ipc() == (mpi.rank() % npr) );

}

TEST_CASE( "Col Major Grid", "[constructor]" ) {

  blacspp::Grid grid = blacspp::Grid::square_grid(MPI_COMM_WORLD, blacspp::GridOrder::ColMajor);
  blacspp::mpi_info mpi(MPI_COMM_WORLD);

  auto npr = grid.npr();
  CHECK( grid.ipr() == (mpi.rank() % npr) );
  CHECK( grid.ipc() == (mpi.rank() / npr) );

}

TEST_CASE( "Process Map", "[constructor]" ) {

  blacspp::mpi_info mpi(MPI_COMM_WORLD);

  if( mpi.size() > 1 ) {

    int64_t np_use = mpi.size() - 1;

    std::vector<int64_t> pmap(np_use);
    std::iota( pmap.begin(), pmap.end(), 0 );

    blacspp::Grid grid( MPI_COMM_WORLD, np_use, 1, pmap.data(), np_use );

    bool rank_participate = mpi.rank() < np_use;


    if( rank_participate ) {
      CHECK( grid.npr() == np_use     );
      CHECK( grid.npc() == 1          );
      CHECK( grid.ipr() == mpi.rank() );
      CHECK( grid.ipc() == 0          );
      CHECK( grid.context() >= 0 );
    } else {
      CHECK( grid.npr() == -1 );
      CHECK( grid.npc() == -1 );
      CHECK( grid.ipr() == -1 );
      CHECK( grid.ipc() == -1 );
      CHECK( grid.context() < 0 );
    }
    
  }

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

  CHECK( grid.context() == grid2.context() );

}

TEST_CASE( "Clone", "[constructor]" ) {

  blacspp::Grid grid = blacspp::Grid::square_grid( MPI_COMM_WORLD );
  blacspp::Grid grid2 = grid.clone();

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
