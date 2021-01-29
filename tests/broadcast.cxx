/**
 *  This file is a part of blacspp (see LICENSE)
 *
 *  Copyright (c) 2019-2020 David Williams-Young
 *  All rights reserved
 */
#include <catch2/catch.hpp>
#include <blacspp/broadcast.hpp>
#include <blacspp/information.hpp>
#include <vector>

#define BLACSPP_TEMPLATE_TEST_CASE(NAME, CAT)\
TEMPLATE_TEST_CASE(NAME,CAT,blacspp::internal::blacs_int, float, double, blacspp::internal::scomplex, blacspp::internal::dcomplex)








BLACSPP_TEMPLATE_TEST_CASE( "General 2D Broadcast", "[broadcast]" ) {

  blacspp::Grid grid = blacspp::Grid::square_grid( MPI_COMM_WORLD );
  auto row_rank = blacspp::coordinate_rank( grid, 0, grid.ipc() );
  auto col_rank = blacspp::coordinate_rank( grid, grid.ipr(), 0 );

  blacspp::mpi_info mpi( MPI_COMM_WORLD );

  const int64_t M(4), N(4);

  std::vector< TestType > data_send( M*N, TestType(mpi.rank()) );
  std::vector< TestType > data_recv( M*N, TestType(-1) );

  SECTION( "Pointer Interface" ) {


    SECTION( "All" ) {

      if( grid.ipc() == 0 and grid.ipr() == 0 ) {
        blacspp::gebs2d( grid, blacspp::Scope::All, blacspp::Topology::IRing, M, N, data_send.data(), M );
        for( auto x : data_recv ) CHECK( x == TestType(-1) );
      } else {
        blacspp::gebr2d( grid, blacspp::Scope::All, blacspp::Topology::IRing, M, N, data_recv.data(), M );
        for( auto x : data_recv ) CHECK( x == TestType(0) );
      }

    }

    SECTION( "Row" ) {

      if( grid.ipc() == 0 ) {
        blacspp::gebs2d( grid, blacspp::Scope::Row, blacspp::Topology::IRing, M, N, data_send.data(), M );
        for( auto x : data_recv ) CHECK( x == TestType(-1) );
      } else {
        blacspp::gebr2d( grid, blacspp::Scope::Row, blacspp::Topology::IRing, M, N, data_recv.data(), M );
        for( auto x : data_recv ) CHECK( x == TestType(col_rank) );
      }

    }

    SECTION( "Column" ) {

      if( grid.ipr() == 0 ) {
        blacspp::gebs2d( grid, blacspp::Scope::Column, blacspp::Topology::IRing, M, N, data_send.data(), M );
        for( auto x : data_recv ) CHECK( x == TestType(-1) );
      } else {
        blacspp::gebr2d( grid, blacspp::Scope::Column, blacspp::Topology::IRing, M, N, data_recv.data(), M );
        for( auto x : data_recv ) CHECK( x == TestType(row_rank) );
      }

    }

  }







  SECTION( "Container Interface" ) {

    // Row and Col checks are redundant

    if( grid.ipc() == 0 and grid.ipr() == 0 ) {
      blacspp::gebs2d( grid, blacspp::Scope::All, blacspp::Topology::IRing, M, N, data_send, M );
      for( auto x : data_recv ) CHECK( x == TestType(-1) );
    } else {
      blacspp::gebr2d( grid, blacspp::Scope::All, blacspp::Topology::IRing, M, N, data_recv, M );
      for( auto x : data_recv ) CHECK( x == TestType(0) );
    }

  }

  SECTION( "Abbreviated Container Interface" ) {

    // Row and Col checks are redundant

    if( grid.ipc() == 0 and grid.ipr() == 0 ) {
      blacspp::gebs2d( grid, blacspp::Scope::All, blacspp::Topology::IRing, data_send );
      for( auto x : data_recv ) CHECK( x == TestType(-1) );
    } else {
      blacspp::gebr2d( grid, blacspp::Scope::All, blacspp::Topology::IRing, data_recv );
      for( auto x : data_recv ) CHECK( x == TestType(0) );
    }

  }


  for( auto x : data_send ) CHECK( x == TestType(mpi.rank()) );

}






BLACSPP_TEMPLATE_TEST_CASE( "Triangular 2D Broadcast", "[broadcast]" ) {

  blacspp::Grid grid = blacspp::Grid::square_grid( MPI_COMM_WORLD );
  auto row_rank = blacspp::coordinate_rank( grid, 0, grid.ipc() );
  auto col_rank = blacspp::coordinate_rank( grid, grid.ipr(), 0 );

  blacspp::mpi_info mpi( MPI_COMM_WORLD );

  const int64_t M(4), N(4);

  std::vector< TestType > data_send( M*N, TestType(mpi.rank()) );
  std::vector< TestType > data_recv( M*N, TestType(-1) );

  auto check_triangle = 
    [&]( blacspp::Uplo tri, blacspp::Diag diag, const auto& data, const TestType val ) {
      for( auto i = 0; i < M; ++i )
      for( auto j = 0; j < N; ++j ) {
        auto x = data[ i + j * M ];
        if( diag == blacspp::Diag::Unit and i == j )      CHECK( x == TestType(-1) );
        else if( tri == blacspp::Uplo::Upper and j >= i ) CHECK( x == val );
        else if( tri == blacspp::Uplo::Lower and i >= j ) CHECK( x == val );
        else                                                  CHECK( x == TestType(-1) ); 
      }
    }; 

  std::array< blacspp::Uplo, 2 > tris  = { blacspp::Uplo::Upper, blacspp::Uplo::Lower   };
  std::array< blacspp::Diag, 2 > diags = { blacspp::Diag::Unit,  blacspp::Diag::NonUnit };

  SECTION( "Pointer Interface" ) {


    SECTION( "All" ) {

      for( auto tri  : tris  )
      for( auto diag : diags ) {

        if( grid.ipc() == 0 and grid.ipr() == 0 ) {
          blacspp::trbs2d( grid, blacspp::Scope::All, blacspp::Topology::IRing, tri, diag, M, N, data_send.data(), M );
          for( auto x : data_recv ) CHECK( x == TestType(-1) );
        } else {
          blacspp::trbr2d( grid, blacspp::Scope::All, blacspp::Topology::IRing, tri, diag, M, N, data_recv.data(), M );
          check_triangle( tri, diag, data_recv, 0 );
        }

        std::fill( data_recv.begin(), data_recv.end(), TestType(-1) );
      }

    }

    SECTION( "Row" ) {

      for( auto tri  : tris  )
      for( auto diag : diags ) {

        if( grid.ipc() == 0 ) {
          blacspp::trbs2d( grid, blacspp::Scope::Row, blacspp::Topology::IRing, tri, diag, M, N, data_send.data(), M );
          for( auto x : data_recv ) CHECK( x == TestType(-1) );
        } else {
          blacspp::trbr2d( grid, blacspp::Scope::Row, blacspp::Topology::IRing, tri, diag, M, N, data_recv.data(), M );
          check_triangle( tri, diag, data_recv, col_rank );
        }

        std::fill( data_recv.begin(), data_recv.end(), TestType(-1) );

      }

    }

    SECTION( "Column" ) {

      for( auto tri  : tris  )
      for( auto diag : diags ) {

        if( grid.ipr() == 0 ) {
          blacspp::trbs2d( grid, blacspp::Scope::Column, blacspp::Topology::IRing, tri, diag, M, N, data_send.data(), M );
          for( auto x : data_recv ) CHECK( x == TestType(-1) );
        } else {
          blacspp::trbr2d( grid, blacspp::Scope::Column, blacspp::Topology::IRing, tri, diag, M, N, data_recv.data(), M );
          check_triangle( tri, diag, data_recv, row_rank );
        }

        std::fill( data_recv.begin(), data_recv.end(), TestType(-1) );

      }

    }

  }

  SECTION( "Container Interface" ) {

    // Row and Col checks are redundant 

    for( auto tri  : tris  )
    for( auto diag : diags ) {

      if( grid.ipc() == 0 and grid.ipr() == 0 ) {
        blacspp::trbs2d( grid, blacspp::Scope::All, blacspp::Topology::IRing, tri, diag, M, N, data_send, M );
        for( auto x : data_recv ) CHECK( x == TestType(-1) );
      } else {
        blacspp::trbr2d( grid, blacspp::Scope::All, blacspp::Topology::IRing, tri, diag, M, N, data_recv, M );
        check_triangle( tri, diag, data_recv, 0 );
      }

      std::fill( data_recv.begin(), data_recv.end(), TestType(-1) );
    }

  }

  for( auto x : data_send ) CHECK( x == TestType(mpi.rank()) );

}
