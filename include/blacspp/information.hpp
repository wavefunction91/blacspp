/**
 *  This file is a part of blacspp (see LICENSE)
 *
 *  Copyright (c) 2019-2020 David Williams-Young
 *  All rights reserved
 */
#pragma once
#include <blacspp/grid.hpp>
#include <blacspp/wrappers/support.hpp>

namespace blacspp {

inline blacs_int coordinate_rank( const Grid& grid, blacs_int PROW, blacs_int PCOL ){
  return wrappers::pnum( grid.context(), PROW, PCOL );
}

inline blacs_int coordinate_rank( const Grid& grid, process_coordinate PCOORD ) {
  return coordinate_rank( grid, PCOORD.first, PCOORD.second );
}

inline process_coordinate rank_coordinate( const Grid& grid, blacs_int PNUM ) {
  return wrappers::pcoord( grid.context(), PNUM );
}

}
