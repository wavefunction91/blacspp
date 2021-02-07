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

inline int64_t coordinate_rank( const Grid& grid, int64_t PROW, int64_t PCOL ){
  return wrappers::pnum( grid.context(), PROW, PCOL );
}

inline int64_t coordinate_rank( const Grid& grid, process_coordinate PCOORD ) {
  return coordinate_rank( grid, PCOORD.first, PCOORD.second );
}

inline process_coordinate rank_coordinate( const Grid& grid, int64_t PNUM ) {
  return wrappers::pcoord( grid.context(), PNUM );
}

}
