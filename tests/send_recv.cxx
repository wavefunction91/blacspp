/**
 *  This file is a part of blacspp (see LICENSE)
 *
 *  Copyright (c) 2019-2020 David Williams-Young
 *  All rights reserved
 */
#include <catch2/catch.hpp>
#include <blacspp/send_recv.hpp>
#include <blacspp/information.hpp>
#include <vector>

#define BLACSPP_TEMPLATE_TEST_CASE(NAME, CAT)\
TEMPLATE_TEST_CASE(NAME,CAT,blacspp::internal::blacs_int, float, double, blacspp::internal::scomplex, blacspp::internal::dcomplex)


BLACSPP_TEMPLATE_TEST_CASE( "General 2D Send-Recv", "[send-recv]" ) {

  blacspp::Grid grid = blacspp::Grid::square_grid( MPI_COMM_WORLD );

  blacspp::mpi_info mpi( MPI_COMM_WORLD );

  const int64_t M(4), N(4);

  std::vector< TestType > data_send( M*N, TestType(mpi.rank()) );
  std::vector< TestType > data_recv( M*N, TestType(-1) );

  auto check = [&]() {
    // Check that send data is unchanged
    for( auto x : data_send ) CHECK( x == TestType(mpi.rank()) );

    // Get the rank for the first column
    int rank_col = blacspp::coordinate_rank( grid, grid.ipr(), 0 );

    // Check that recv data is correct
    if( grid.ipc() == 0 )
      for( auto x : data_recv ) CHECK( x == TestType(-1)       );
    else
      for( auto x : data_recv ) CHECK( x == TestType(rank_col) );
  };


  SECTION( "Pointer Interface" ) {

    if( grid.ipc() == 0) 
      for( int i = 1; i < grid.npc(); ++i )
        blacspp::gesd2d( grid, M, N, data_send.data(), M, 
          grid.ipr(), i );
    else
      blacspp::gerv2d(grid, M, N, data_recv.data(), M, 
        grid.ipr(), 0 );
  
    check();

  }

  SECTION( "Container Interface" ) {

    if( grid.ipc() == 0) 
      for( int i = 1; i < grid.npc(); ++i )
        blacspp::gesd2d( grid, M, N, data_send, M, 
          grid.ipr(), i );
    else
      blacspp::gerv2d(grid, M, N, data_recv, M, 
        grid.ipr(), 0 );
  
    check();

  }

  SECTION( "Abbreviated Container Interface" ) {

    if( grid.ipc() == 0) 
      for( int i = 1; i < grid.npc(); ++i )
        blacspp::gesd2d( grid, data_send, grid.ipr(), i );
    else
      blacspp::gerv2d(grid, data_recv, grid.ipr(), 0 );
  
    check();

  }

}


BLACSPP_TEMPLATE_TEST_CASE( "Triangular 2D Send-Recv", "[send-recv]" ) {

  blacspp::Grid grid = blacspp::Grid::square_grid( MPI_COMM_WORLD );

  blacspp::mpi_info mpi( MPI_COMM_WORLD );

  const int64_t M(4), N(4);

  std::vector< TestType > data_send( M*N, TestType(mpi.rank()) );
  std::vector< TestType > data_recv( M*N, TestType(-1) );

  auto check = [&](blacspp::Triangle triangle, blacspp::Diagonal diag) {
    // Check that send data is unchanged
    for( auto x : data_send ) CHECK( x == TestType(mpi.rank()) );

    // Get the rank for the first column
    int rank_col = blacspp::coordinate_rank( grid, grid.ipr(), 0 );

    // Check that recv data is correct
    if( grid.ipc() == 0 )
      for( auto x : data_recv ) CHECK( x == TestType(-1) );
    else
      for( auto i = 0; i < M; ++i )
      for( auto j = 0; j < N; ++j ) {
        auto x = data_recv[ i + M*j ];
        if( diag == blacspp::Diagonal::Unit and i == j )
          CHECK( x == TestType(-1) ); // unchanged

        else if( triangle == blacspp::Triangle::Upper and j >= i ) 
          CHECK( x == TestType(rank_col) );

        else if( triangle == blacspp::Triangle::Lower and i >= j ) 
          CHECK( x == TestType(rank_col) );

        else
          CHECK( x == TestType(-1) ); // unchanged
      }
  };

  std::array< blacspp::Triangle, 2 > tris  = { blacspp::Triangle::Upper, blacspp::Triangle::Lower   };
  std::array< blacspp::Diagonal, 2 > diags = { blacspp::Diagonal::Unit,  blacspp::Diagonal::NonUnit };


  SECTION( "Pointer Interface" ) {

    for( auto tri  : tris  )
    for( auto diag : diags ) {
      if( grid.ipc() == 0) 
        for( int i = 1; i < grid.npc(); ++i )
          blacspp::trsd2d( grid, tri, diag, M, N, data_send.data(), M, 
            grid.ipr(), i );
      else
        blacspp::trrv2d(grid, tri, diag, M, N, data_recv.data(), M, 
          grid.ipr(), 0 );
  
      check(tri, diag);
      std::fill( data_recv.begin(), data_recv.end(), TestType(-1) );
    }

  }

  SECTION( "Container Interface" ) {

    for( auto tri  : tris  )
    for( auto diag : diags ) {
      if( grid.ipc() == 0) 
        for( int i = 1; i < grid.npc(); ++i )
          blacspp::trsd2d( grid, tri, diag, M, N, data_send, M, 
            grid.ipr(), i );
      else
        blacspp::trrv2d(grid, tri, diag, M, N, data_recv, M, 
          grid.ipr(), 0 );
  
      check(tri, diag);
      std::fill( data_recv.begin(), data_recv.end(), TestType(-1) );
    }

  }

}
