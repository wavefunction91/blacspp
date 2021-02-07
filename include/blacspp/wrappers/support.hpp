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
void pinfo( int64_t& IAM, int64_t& NPROCS );
void set( const int64_t ICONTXT, const int64_t WHAT, const int64_t* VAL );
void get( const int64_t ICONTXT, const int64_t WHAT, int64_t* VAL );

int64_t grid_init( int64_t ICONTXT, const char* ORDER, const int64_t NPROW,
                     const int64_t NPCOL );

int64_t grid_map( int64_t ICONTXT, const int64_t* USERMAP, 
                    const int64_t LDUMAP, const int64_t NPROW, 
                    const int64_t NPCOL ); 

// Destruction
void grid_exit( const int64_t ICONTXT );
void exit( const int64_t CONTINUE );
void abort( const int64_t ICONTXT, const int64_t ERRORNUM );
void freebuff( const int64_t ICONTXT, const int64_t WAIT );


// Infortmational
blacs_grid_dim  grid_info( const int64_t ICONTXT );
int64_t        pnum( const int64_t ICONTXT, const int64_t PROW, 
                       const int64_t PCOL );

std::pair< int64_t, int64_t > pcoord( const int64_t ICONTXT, 
                                          const int64_t  PNUM );

// Misc
void barrier( const int64_t ICONTXT, const char* SCOPE );
int64_t blacs_from_sys( MPI_Comm c );
void free_sys_handle( const int64_t handle );


}
}
