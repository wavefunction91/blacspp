#pragma once
#include <blacspp/types.hpp>

namespace blacspp {

class Grid {

  blacs_grid_dim  grid_dim_;
  mpi_info        mpi_info_;

  blacs_int       system_handle_;
  blacs_int       context_;
  
public:

  Grid() = delete;
  Grid( MPI_Comm c, blacs_int npr, blacs_int npc );

  Grid( const Grid& );
  Grid( Grid&&      ) noexcept = delete;  

  ~Grid() noexcept;

  inline blacs_int context() const { return context_;         }
  inline blacs_int npr()     const { return grid_dim_.np_row; }
  inline blacs_int npc()     const { return grid_dim_.np_col; }
  inline blacs_int ipr()     const { return grid_dim_.my_row; }
  inline blacs_int ipc()     const { return grid_dim_.my_col; }

};

}
