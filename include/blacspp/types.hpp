#pragma once

#include <complex>

namespace blacspp {

  using blacs_int = int32_t;
  using scomplex  = std::complex< float >;
  using dcomplex  = std::complex< double >;

  struct blacs_grid_info {
    blacs_int np_row;
    blacs_int np_col;
    blacs_int my_row;
    blacs_int my_col;
  };

}
