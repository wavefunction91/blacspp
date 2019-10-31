#include <catch2/catch.hpp>
#include <blacspp/broadcast.hpp>
#include <vector>
#include <blacspp/wrappers/support.hpp>

#define BLACSPP_TEMPLATE_TEST_CASE(NAME, CAT)\
TEMPLATE_TEST_CASE(NAME,CAT,blacspp::blacs_int, float, double, blacspp::scomplex, blacspp::dcomplex)








BLACSPP_TEMPLATE_TEST_CASE( "General 2D Broadcast", "[broadcast]" ) {

  blacspp::Grid grid = blacspp::Grid::square_grid( MPI_COMM_WORLD );
  auto row_rank = blacspp::wrappers::pnum( grid.context(), 0, grid.ipc() );
  auto col_rank = blacspp::wrappers::pnum( grid.context(), grid.ipr(), 0 );

  blacspp::mpi_info mpi( MPI_COMM_WORLD );

  const blacspp::blacs_int M(4), N(4);

  std::vector< TestType > data_send( M*N, TestType(mpi.rank()) );
  std::vector< TestType > data_recv( M*N, TestType(-1) );

  SECTION( "Pointer Interface" ) {


    SECTION( "All" ) {

      if( grid.ipc() == 0 and grid.ipr() == 0 ) {
        blacspp::gebs2d( grid, "All", "i-ring", M, N, data_send.data(), M );
        for( auto x : data_recv ) CHECK( x == TestType(-1) );
      } else {
        blacspp::gebr2d( grid, "All", "i-ring", M, N, data_recv.data(), M );
        for( auto x : data_recv ) CHECK( x == TestType(0) );
      }

    }

    SECTION( "Row" ) {

      if( grid.ipc() == 0 ) {
        blacspp::gebs2d( grid, "Row", "i-ring", M, N, data_send.data(), M );
        for( auto x : data_recv ) CHECK( x == TestType(-1) );
      } else {
        blacspp::gebr2d( grid, "Row", "i-ring", M, N, data_recv.data(), M );
        for( auto x : data_recv ) CHECK( x == TestType(col_rank) );
      }

    }

    SECTION( "Column" ) {

      if( grid.ipr() == 0 ) {
        blacspp::gebs2d( grid, "Column", "i-ring", M, N, data_send.data(), M );
        for( auto x : data_recv ) CHECK( x == TestType(-1) );
      } else {
        blacspp::gebr2d( grid, "Column", "i-ring", M, N, data_recv.data(), M );
        for( auto x : data_recv ) CHECK( x == TestType(row_rank) );
      }

    }

  }







  SECTION( "Container Interface" ) {

    // Row and Col checks are redundant

    if( grid.ipc() == 0 and grid.ipr() == 0 ) {
      blacspp::gebs2d( grid, "All", "i-ring", M, N, data_send, M );
      for( auto x : data_recv ) CHECK( x == TestType(-1) );
    } else {
      blacspp::gebr2d( grid, "All", "i-ring", M, N, data_recv, M );
      for( auto x : data_recv ) CHECK( x == TestType(0) );
    }

  }

  SECTION( "Abbreviated Container Interface" ) {

    // Row and Col checks are redundant

    if( grid.ipc() == 0 and grid.ipr() == 0 ) {
      blacspp::gebs2d( grid, "All", "i-ring", data_send );
      for( auto x : data_recv ) CHECK( x == TestType(-1) );
    } else {
      blacspp::gebr2d( grid, "All", "i-ring", data_recv );
      for( auto x : data_recv ) CHECK( x == TestType(0) );
    }

  }


  for( auto x : data_send ) CHECK( x == TestType(mpi.rank()) );

}






BLACSPP_TEMPLATE_TEST_CASE( "Triangular 2D Broadcast", "[broadcast]" ) {

  blacspp::Grid grid = blacspp::Grid::square_grid( MPI_COMM_WORLD );
  auto row_rank = blacspp::wrappers::pnum( grid.context(), 0, grid.ipc() );
  auto col_rank = blacspp::wrappers::pnum( grid.context(), grid.ipr(), 0 );

  blacspp::mpi_info mpi( MPI_COMM_WORLD );

  const blacspp::blacs_int M(4), N(4);

  std::vector< TestType > data_send( M*N, TestType(mpi.rank()) );
  std::vector< TestType > data_recv( M*N, TestType(-1) );

  auto check_triangle = 
    [&]( const char tri, const char diag, const auto& data, const TestType val ) {
      for( auto i = 0; i < M; ++i )
      for( auto j = 0; j < N; ++j ) {
        auto x = data[ i + j * M ];
        if( diag == 'U' and i == j )     CHECK( x == TestType(-1) );
        else if( tri == 'U' and j >= i ) CHECK( x == val );
        else if( tri == 'L' and i >= j ) CHECK( x == val );
        else                             CHECK( x == TestType(-1) ); 
      }
    }; 

  std::array<char,2> tris  = { 'U', 'L' };
  std::array<char,2> diags = { 'U', 'N' };

  SECTION( "Pointer Interface" ) {


    SECTION( "All" ) {

      for( auto tri  : tris  )
      for( auto diag : diags ) {

        if( grid.ipc() == 0 and grid.ipr() == 0 ) {
          blacspp::trbs2d( grid, "All", "i-ring", &tri, &diag, M, N, data_send.data(), M );
          for( auto x : data_recv ) CHECK( x == TestType(-1) );
        } else {
          blacspp::trbr2d( grid, "All", "i-ring", &tri, &diag, M, N, data_recv.data(), M );
          check_triangle( tri, diag, data_recv, 0 );
        }

        std::fill( data_recv.begin(), data_recv.end(), TestType(-1) );
      }

    }

    SECTION( "Row" ) {

      for( auto tri  : tris  )
      for( auto diag : diags ) {

        if( grid.ipc() == 0 ) {
          blacspp::trbs2d( grid, "Row", "i-ring", &tri, &diag, M, N, data_send.data(), M );
          for( auto x : data_recv ) CHECK( x == TestType(-1) );
        } else {
          blacspp::trbr2d( grid, "Row", "i-ring", &tri, &diag, M, N, data_recv.data(), M );
          check_triangle( tri, diag, data_recv, col_rank );
        }

        std::fill( data_recv.begin(), data_recv.end(), TestType(-1) );

      }

    }

    SECTION( "Column" ) {

      for( auto tri  : tris  )
      for( auto diag : diags ) {

        if( grid.ipr() == 0 ) {
          blacspp::trbs2d( grid, "Column", "i-ring", &tri, &diag, M, N, data_send.data(), M );
          for( auto x : data_recv ) CHECK( x == TestType(-1) );
        } else {
          blacspp::trbr2d( grid, "Column", "i-ring", &tri, &diag, M, N, data_recv.data(), M );
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
        blacspp::trbs2d( grid, "All", "i-ring", &tri, &diag, M, N, data_send, M );
        for( auto x : data_recv ) CHECK( x == TestType(-1) );
      } else {
        blacspp::trbr2d( grid, "All", "i-ring", &tri, &diag, M, N, data_recv, M );
        check_triangle( tri, diag, data_recv, 0 );
      }

      std::fill( data_recv.begin(), data_recv.end(), TestType(-1) );
    }

  }

  for( auto x : data_send ) CHECK( x == TestType(mpi.rank()) );

}
