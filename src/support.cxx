#include <blacspp/wrappers/support.hpp>

using blacspp::blacs_int;

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
void pinfo( blacs_int& IAM, blacs_int& NPROCS ) {

  Cblacs_pinfo( &IAM, &NPROCS );

}


void set( const blacs_int ICONTXT, const blacs_int WHAT, const blacs_int* VAL ) {

  Cblacs_set( ICONTXT, WHAT, VAL );

}


void get( const blacs_int ICONTXT, const blacs_int WHAT, blacs_int* VAL ) {

  Cblacs_get( ICONTXT, WHAT, VAL );

}

blacs_int grid_init( blacs_int ICONTXT, const char* ORDER, const blacs_int NPROW,
                     const blacs_int NPCOL ) {

  Cblacs_gridinit( &ICONTXT, ORDER, NPROW, NPCOL );
  return ICONTXT;

}

blacs_int grid_map( blacs_int ICONTXT, const blacs_int* USERMAP, 
                    const blacs_int LDUMAP, const blacs_int NPROW, 
                    const blacs_int NPCOL ) {


  Cblacs_gridmap( &ICONTXT, USERMAP, LDUMAP, NPROW, NPCOL );
  return ICONTXT;

}




// Destruction
void grid_exit( const blacs_int ICONTXT ) {
  Cblacs_gridexit( ICONTXT );
}
void exit( const blacs_int CONTINUE ) {
  Cblacs_exit( CONTINUE );
}
void abort( const blacs_int ICONTXT, const blacs_int ERRORNUM ) {
  Cblacs_abort( ICONTXT, ERRORNUM );
}
void freebuff( const blacs_int ICONTXT, const blacs_int WAIT ) {
  Cblacs_freebuff( ICONTXT, WAIT );
}






// Infortmational
blacs_grid_dim  grid_info( const blacs_int ICONTXT ) {

  blacs_grid_dim info;
  Cblacs_gridinfo( ICONTXT, &info.np_row, &info.np_col, &info.my_row, &info.my_col );
  return info;

}

blacs_int pnum( const blacs_int ICONTXT, const blacs_int PROW, 
                const blacs_int PCOL ) {

  return Cblacs_pnum( ICONTXT, PROW, PCOL );

}

std::pair< blacs_int, blacs_int > pcoord( const blacs_int ICONTXT, 
                                          const blacs_int  PNUM ) {

  std::pair< blacs_int, blacs_int > coord;
  Cblacs_pcoord( ICONTXT, PNUM, &coord.first, &coord.second );
  return coord;

}


// Misc
void barrier( const blacs_int ICONTXT, const char* SCOPE ) {
  Cblacs_barrier( ICONTXT, SCOPE );
}

blacs_int blacs_from_sys( MPI_Comm c ) {

  return Csys2blacs_handle( c );

}

void free_sys_handle( const blacs_int handle ) {
  Cfree_blacs_system_handle( handle );
}


}
}
