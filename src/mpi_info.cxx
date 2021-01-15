/**
 *  This file is a part of blacspp (see LICENSE)
 *
 *  Copyright (c) 2019-2020 David Williams-Young
 *  All rights reserved
 */
#include <blacspp/types.hpp>

namespace blacspp {

mpi_info::mpi_info( MPI_Comm c ) : comm_(c) {


  // Check if MPI has been initialized
  int flag;
  MPI_Initialized(&flag);
  if( not flag ) {
    throw std::runtime_error("MPI Environment Not Initialized!");
  }

  if( c == MPI_COMM_NULL ) {

    rank_ = -1;
    size_ = 0;

  } else {

    MPI_Comm_rank( c, &rank_ );
    MPI_Comm_size( c, &size_ );

  }
}

MPI_Comm  mpi_info::comm() const { return comm_; };
mpi_int mpi_info::rank() const { return rank_; };
mpi_int mpi_info::size() const { return size_; };


}
