#pragma once
#include <blacspp/types.hpp>

namespace blacspp {

class Grid {

  blacs_grid_dim  grid_dim_;
  mpi_info        mpi_info_;

  blacs_int       system_handle_;
  blacs_int       context_;
  blacs_int       mb_;
  blacs_int       nb_;
  
public:

  Grid() = delete;
  Grid( MPI_Comm c, blacs_int mb, blacs_int nb, blacs_int npr, blacs_int npc );

  Grid( const Grid& );
  Grid( Grid&&      ) noexcept = delete;  

  ~Grid() noexcept;


};

}
