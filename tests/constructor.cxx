#include <gtest/gtest.h>
#include <blacspp/grid.hpp>


TEST( CONSTRUCTOR, Default ) {

  blacspp::Grid grid;
  EXPECT_FALSE( grid.is_valid() );

}

TEST( CONSTRUCTOR, SquareGrid ) {

  blacspp::Grid grid = blacspp::Grid::square_grid(MPI_COMM_WORLD);

  blacspp::mpi_info mpi(MPI_COMM_WORLD);

  EXPECT_TRUE( grid.is_valid() );  
  EXPECT_EQ( mpi.size(), grid.npr() * grid.npc() );

  auto npr = grid.npr();
  EXPECT_EQ( grid.ipr(), mpi.rank() % npr );
  EXPECT_EQ( grid.ipc(), mpi.rank() / npr );

}


TEST( CONSTRUCTOR, Copy ) {

  blacspp::Grid grid = blacspp::Grid::square_grid( MPI_COMM_WORLD );
  blacspp::Grid grid2( grid );

  EXPECT_EQ( grid.npr(), grid2.npr() );
  EXPECT_EQ( grid.npc(), grid2.npc() );
  EXPECT_EQ( grid.ipr(), grid2.ipr() );
  EXPECT_EQ( grid.ipc(), grid2.ipc() );
  EXPECT_EQ( grid.comm(), grid2.comm() );

  EXPECT_NE( grid.context(), grid2.context() );

  EXPECT_TRUE( grid.is_valid() );
  EXPECT_TRUE( grid2.is_valid() );
}


TEST( CONSTRUCTOR, Move ) {

  blacspp::Grid grid = blacspp::Grid::square_grid( MPI_COMM_WORLD );

  auto npr  = grid.npr();
  auto npc  = grid.npc();
  auto ipr  = grid.ipr();
  auto ipc  = grid.ipc();
  auto comm = grid.comm();
  auto context = grid.context();

  blacspp::Grid grid2( std::move(grid) );

  EXPECT_EQ( npr, grid2.npr() );
  EXPECT_EQ( npc, grid2.npc() );
  EXPECT_EQ( ipr, grid2.ipr() );
  EXPECT_EQ( ipc, grid2.ipc() );
  EXPECT_EQ( comm, grid2.comm() );
  EXPECT_EQ( context, grid2.context() );

  EXPECT_FALSE( grid.is_valid() );  
  EXPECT_TRUE( grid2.is_valid() );  

}
