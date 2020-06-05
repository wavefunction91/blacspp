/**
 *  This file is a part of blacspp (see LICENSE)
 *
 *  Copyright (c) 2019-2020 David Williams-Young
 *  All rights reserved
 */
#pragma once
#include <blacspp/types.hpp>

namespace blacspp {
namespace wrappers {


// Initialization
void pinfo( blacs_int& IAM, blacs_int& NPROCS );
void set( const blacs_int ICONTXT, const blacs_int WHAT, const blacs_int* VAL );
void get( const blacs_int ICONTXT, const blacs_int WHAT, blacs_int* VAL );

blacs_int grid_init( blacs_int ICONTXT, const char* ORDER, const blacs_int NPROW,
                     const blacs_int NPCOL );

blacs_int grid_map( blacs_int ICONTXT, const blacs_int* USERMAP, 
                    const blacs_int LDUMAP, const blacs_int NPROW, 
                    const blacs_int NPCOL ); 

// Destruction
void grid_exit( const blacs_int ICONTXT );
void exit( const blacs_int CONTINUE );
void abort( const blacs_int ICONTXT, const blacs_int ERRORNUM );
void freebuff( const blacs_int ICONTXT, const blacs_int WAIT );


// Infortmational
blacs_grid_dim  grid_info( const blacs_int ICONTXT );
blacs_int        pnum( const blacs_int ICONTXT, const blacs_int PROW, 
                       const blacs_int PCOL );

std::pair< blacs_int, blacs_int > pcoord( const blacs_int ICONTXT, 
                                          const blacs_int  PNUM );

// Misc
void barrier( const blacs_int ICONTXT, const char* SCOPE );
blacs_int blacs_from_sys( MPI_Comm c );
void free_sys_handle( const blacs_int handle );


}
}
