#pragma once

#include <complex>
#include <mpi.h>

namespace blacspp {

  using blacs_int = int32_t;
  using scomplex  = std::complex< float >;
  using dcomplex  = std::complex< double >;

  struct blacs_grid_dim {
    blacs_int np_row;
    blacs_int np_col;
    blacs_int my_row;
    blacs_int my_col;
  };


  class mpi_info {

    MPI_Comm  comm_;
    blacs_int rank_;
    blacs_int size_;

  public:

    mpi_info( MPI_Comm c = MPI_COMM_WORLD );


    MPI_Comm  comm() const;
    blacs_int rank() const;
    blacs_int size() const;

  };
}
