/**
 *  This file is a part of blacspp (see LICENSE)
 *
 *  Copyright (c) 2019-2020 David Williams-Young
 *  All rights reserved
 */
#include <blacspp/wrappers/support.hpp>
#include <blacspp/util/type_conversions.hpp>

#include <vector>
#include <type_traits>

using blacspp::internal::blacs_int;

// Prototypes
extern "C" {

// Initialization
void Cblacs_pinfo( blacs_int* IAM, blacs_int* NPROCS );
void Cblacs_set( const blacs_int ICONTXT, const blacs_int WHAT, const blacs_int* VAL );
void Cblacs_get( const blacs_int ICONTXT, const blacs_int WHAT, blacs_int* VAL );
    
void Cblacs_gridinit( blacs_int* ICONTXT, const char* ORDER, const blacs_int NPROW,
                      const blacs_int NPCOL );
    
void Cblacs_gridmap( blacs_int* ICONTXT, const blacs_int* USERMAP, 
                     const blacs_int LDUMAP, const blacs_int NPROW, 
                     const blacs_int NPCOL ); 

// Destruction
void Cblacs_gridexit( const blacs_int ICONTXT );
void Cblacs_exit( const blacs_int CONTINUE );
void Cblacs_abort( const blacs_int ICONTXT, const blacs_int ERRORNUM );
void Cblacs_freebuff( const blacs_int ICONTXT, const blacs_int WAIT );

// Informational
void Cblacs_gridinfo( const blacs_int ICONTXT, blacs_int* NPR, blacs_int* NPC,
                      blacs_int* MYR, blacs_int* MYC );
blacs_int Cblacs_pnum( const blacs_int ICONTXT, const blacs_int PR, 
                       const blacs_int PC );
void Cblacs_pcoord( const blacs_int ICONTXT, const blacs_int PNUM, 
                    blacs_int* PR, blacs_int* PC );

// Misc
void Cblacs_barrier( const blacs_int ICONTXT, const char* SCOPE );
blacs_int Csys2blacs_handle( MPI_Comm c );
void Cfree_blacs_system_handle( const blacs_int handle );
};


namespace blacspp {
namespace wrappers {


// Initialization
void pinfo( int64_t& IAM, int64_t& NPROCS ) {

  blacs_int _IAM, _NPROCS;

  Cblacs_pinfo( &_IAM, &_NPROCS );

  IAM    = _IAM;
  NPROCS = _NPROCS;

}


void set( const int64_t ICONTXT, const int64_t WHAT, const int64_t* VAL ) {

  blacs_int _ICONTXT = detail::to_blacs_int( ICONTXT );
  blacs_int _WHAT    = detail::to_blacs_int( WHAT );
  blacs_int _VAL[2];

  _VAL[0] = VAL[0];
  if( WHAT == 1 )
    _VAL[1] = VAL[1];

  Cblacs_set( _ICONTXT, _WHAT, _VAL );

  
}


void get( const int64_t ICONTXT, const int64_t WHAT, int64_t* VAL ) {

  blacs_int _ICONTXT = detail::to_blacs_int( ICONTXT );
  blacs_int _WHAT    = detail::to_blacs_int( WHAT );
  blacs_int _VAL;

  Cblacs_get( _ICONTXT, _WHAT, &_VAL );

  *VAL = _VAL;

}

int64_t grid_init( int64_t ICONTXT, const char* ORDER, const int64_t NPROW,
                   const int64_t NPCOL ) {

  blacs_int _ICONTXT = detail::to_blacs_int( ICONTXT );
  blacs_int _NPROW   = detail::to_blacs_int( NPROW );
  blacs_int _NPCOL   = detail::to_blacs_int( NPCOL );

  Cblacs_gridinit( &_ICONTXT, ORDER, _NPROW, _NPCOL );

  return _ICONTXT;

}

int64_t grid_map( int64_t ICONTXT, const int64_t* USERMAP, 
                  const int64_t LDUMAP, const int64_t NPROW, 
                  const int64_t NPCOL ) {

  blacs_int _ICONTXT = detail::to_blacs_int( ICONTXT );
  blacs_int _NPROW   = detail::to_blacs_int( NPROW );
  blacs_int _NPCOL   = detail::to_blacs_int( NPCOL );


  if constexpr ( not std::is_same_v<blacs_int,int64_t> ) {

    std::vector<blacs_int> _USERMAP( NPROW * NPCOL );
    for( int64_t j = 0; j < NPCOL; ++j )
    for( int64_t i = 0; i < NPROW; ++i )
      _USERMAP[i + j*NPROW] = USERMAP[i + j*LDUMAP];
    auto _LDUMAP = _NPROW;

    Cblacs_gridmap( &_ICONTXT, _USERMAP.data(), _LDUMAP, _NPROW, _NPCOL );
    
  } else {

    Cblacs_gridmap( &_ICONTXT, USERMAP, LDUMAP, _NPROW, _NPCOL );

  }

  return _ICONTXT;

}




// Destruction
void grid_exit( const int64_t ICONTXT ) {
  Cblacs_gridexit( detail::to_blacs_int(ICONTXT) );
}
void exit( const int64_t CONTINUE ) {
  Cblacs_exit( detail::to_blacs_int(CONTINUE) );
}
void abort( const int64_t ICONTXT, const int64_t ERRORNUM ) {
  Cblacs_abort( detail::to_blacs_int(ICONTXT), 
                detail::to_blacs_int(ERRORNUM) );
}
void freebuff( const int64_t ICONTXT, const int64_t WAIT ) {
  Cblacs_freebuff( detail::to_blacs_int(ICONTXT), 
                   detail::to_blacs_int(WAIT) );
}






// Infortmational
blacs_grid_dim  grid_info( const int64_t ICONTXT ) {

  blacs_grid_dim info;
  Cblacs_gridinfo( ICONTXT, &info.np_row, &info.np_col, &info.my_row, &info.my_col );
  return info;

}

int64_t pnum( const int64_t ICONTXT, const int64_t PROW, 
                const int64_t PCOL ) {

  return Cblacs_pnum( ICONTXT, PROW, PCOL );

}

std::pair< int64_t, int64_t > pcoord( const int64_t ICONTXT, 
                                          const int64_t  PNUM ) {

  std::pair< int64_t, int64_t > coord;
  Cblacs_pcoord( ICONTXT, PNUM, &coord.first, &coord.second );
  return coord;

}


// Misc
void barrier( const int64_t ICONTXT, const char* SCOPE ) {
  Cblacs_barrier( ICONTXT, SCOPE );
}

int64_t blacs_from_sys( MPI_Comm c ) {

  return Csys2blacs_handle( c );

}

void free_sys_handle( const int64_t handle ) {
  Cfree_blacs_system_handle( handle );
}


}
}
