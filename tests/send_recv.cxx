#include <gtest/gtest.h>
#include <blacspp/send_recv.hpp>

#include <vector>

template <typename T>
void ge_send_recv_test() {

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
      for( auto x : data_recv ) EXPECT_EQ( x, T(-1)       );
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



template <typename T>
void tr_send_recv_test() {

  blacspp::Grid grid = blacspp::Grid::square_grid( MPI_COMM_WORLD );

  blacspp::mpi_info mpi( MPI_COMM_WORLD );
  std::vector< T > data_send( 16, T(mpi.rank()) );
  std::vector< T > data_recv( 16, T(-1) );

  auto check = [&](char triangle, char diag) {
    // Check that send data is unchanged
    for( auto x : data_send ) EXPECT_EQ( x, T(mpi.rank()) );

    // Get the rank for the first column
    int rank_col = mpi.size() / grid.npc();

    // Check that recv data is correct
    if( grid.ipc() == 0 )
      for( auto x : data_recv ) EXPECT_EQ( x, T(-1) );
    else
      for( auto i = 0; i < 4; ++i )
      for( auto j = 0; j < 4; ++j ) {
        auto x = data_recv[ i + 4*j ];
        if( diag == 'U' and i == j ){ 
          std::cout << "HERE " << x << std::boolalpha << (x == 1) << std::endl;
          EXPECT_EQ( -1, 1 );
          EXPECT_EQ( x, T(1000000000) ); // unchanged
        }else if( triangle == 'U' and j >= i ) 
          EXPECT_EQ( x, T(rank_col) );
        else if( triangle == 'L' and i >= j ) 
          EXPECT_EQ( x, T(rank_col) );
        else
          EXPECT_EQ( x, T(-1) ); // unchanged
      }
      
  };

  auto reset = [&]() {
    std::fill( data_recv.begin(), data_recv.end(), T(-1) );
  };


  // Pointer Interface

  std::array<char,2> tris  = { 'U', 'L' };
  std::array<char,2> diags = { 'U', 'N' };
  for( auto tri  : tris  )
  for( auto diag : diags ) {

    if( grid.ipc() == 0) 
      for( int i = 1; i < grid.npc(); ++i )
        blacspp::trsd2d( grid, &tri, &diag, 4, 4, data_send.data(), 4, 
          grid.ipr(), i );
    else
      blacspp::trrv2d(grid, &tri, &diag, 4, 4, data_recv.data(), 4, 
        grid.ipr(), 0 );

    check(tri, diag);
    reset();
  }


/*
  // Container Interface
  
  if( grid.ipc() == 0) 
    for( int i = 1; i < grid.npc(); ++i )
      blacspp::trsd2d( grid, 4, 4, data_send, 4, grid.ipr(), i );
  else
    blacspp::trrv2d(grid, 4, 4, data_recv, 4, grid.ipr(), 0 );

  check();
*/



}

TEST( SEND_RECV, full_blacs_int ) {
  ge_send_recv_test< blacspp::blacs_int >();
  tr_send_recv_test< blacspp::blacs_int >();
}
TEST( SEND_RECV, full_float ) {
  ge_send_recv_test< float >();
}
TEST( SEND_RECV, full_double ) {
  ge_send_recv_test< double >();
}
TEST( SEND_RECV, full_scomplex ) {
  ge_send_recv_test< blacspp::scomplex >();
}
TEST( SEND_RECV, full_dcomplex ) {
  ge_send_recv_test< blacspp::dcomplex >();
}
