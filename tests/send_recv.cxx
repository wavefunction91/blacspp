#include <gtest/gtest.h>
#include <blacspp/send_recv.hpp>

#include <vector>

template <typename T>
void send_recv_test() {

  blacspp::Grid grid = blacspp::Grid::square_grid( MPI_COMM_WORLD );

  blacspp::mpi_info mpi( MPI_COMM_WORLD );
  std::vector< T > data_send( 16, T(mpi.rank()) );
  std::vector< T > data_recv( 16, T(-1) );

  auto check = [&]() {
    // Check that send data is unchanged
    for( auto x : data_send ) EXPECT_EQ( x, T(mpi.rank()) );

    // Get the rank for the first column
    int rank_col = mpi.size() / grid.npc();

    // Check that recv data is correct
    if( grid.ipc() == 0 )
      for( auto x : data_recv ) EXPECT_EQ( x, T(0)       );
    else
      for( auto x : data_recv ) EXPECT_EQ( x, T(rank_col) );
  };


  // Pointer Interface

  if( grid.ipc() == 0) 
    for( int i = 1; i < grid.npc(); ++i )
      blacspp::gesd2d( grid, 4, 4, data_send.data(), 4, 
        grid.ipr(), i );
  else
    blacspp::gerv2d(grid, 4, 4, data_recv.data(), 4, 
      grid.ipr(), 0 );

  check();

  // Reset
  std::fill( data_recv.begin(), data_recv.end(), T(-1) );

  // Container Interface
  
  if( grid.ipc() == 0) 
    for( int i = 1; i < grid.npc(); ++i )
      blacspp::gesd2d( grid, 4, 4, data_send, 4, grid.ipr(), i );
  else
    blacspp::gerv2d(grid, 4, 4, data_recv, 4, grid.ipr(), 0 );

  check();



  // Reset
  std::fill( data_recv.begin(), data_recv.end(), T(-1) );

  // Appreviated Container Interface
  
  if( grid.ipc() == 0) 
    for( int i = 1; i < grid.npc(); ++i )
      blacspp::gesd2d( grid, data_send, grid.ipr(), i );
  else
    blacspp::gerv2d(grid, data_recv, grid.ipr(), 0 );

  check();
}

TEST( SEND_RECV, full_int32_t ) {
  send_recv_test< int32_t >();
}
