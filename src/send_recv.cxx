/**
 *  This file is a part of blacspp (see LICENSE)
 *
 *  Copyright (c) 2019-2020 David Williams-Young
 *  All rights reserved
 */
#include <blacspp/wrappers/send_recv.hpp>
#include <blacspp/util/type_conversions.hpp>

using blacspp::internal::blacs_int;
using blacspp::internal::scomplex;
using blacspp::internal::dcomplex;

// Prototypes
extern "C" {

// Send
void Cigesd2d( const blacs_int ICONTXT, const blacs_int M, const blacs_int N,
               const blacs_int* A, const blacs_int LDA, const blacs_int RDEST,
               const blacs_int CDEST );
void Csgesd2d( const blacs_int ICONTXT, const blacs_int M, const blacs_int N,
               const float* A, const blacs_int LDA, const blacs_int RDEST,
               const blacs_int CDEST );
void Cdgesd2d( const blacs_int ICONTXT, const blacs_int M, const blacs_int N,
               const double* A, const blacs_int LDA, const blacs_int RDEST,
               const blacs_int CDEST );
void Ccgesd2d( const blacs_int ICONTXT, const blacs_int M, const blacs_int N,
               const scomplex* A, const blacs_int LDA, const blacs_int RDEST,
               const blacs_int CDEST );
void Czgesd2d( const blacs_int ICONTXT, const blacs_int M, const blacs_int N,
               const dcomplex* A, const blacs_int LDA, const blacs_int RDEST,
               const blacs_int CDEST );

void Citrsd2d( const blacs_int ICONTXT, const char* UPLO, const char* DIAG, 
               const blacs_int M, const blacs_int N, const blacs_int* A, 
               const blacs_int LDA, const blacs_int RDEST, const blacs_int CDEST );
void Cstrsd2d( const blacs_int ICONTXT, const char* UPLO, const char* DIAG, 
               const blacs_int M, const blacs_int N, const float* A, 
               const blacs_int LDA, const blacs_int RDEST, const blacs_int CDEST );
void Cdtrsd2d( const blacs_int ICONTXT, const char* UPLO, const char* DIAG, 
               const blacs_int M, const blacs_int N, const double* A, 
               const blacs_int LDA, const blacs_int RDEST, const blacs_int CDEST );
void Cctrsd2d( const blacs_int ICONTXT, const char* UPLO, const char* DIAG, 
               const blacs_int M, const blacs_int N, const scomplex* A, 
               const blacs_int LDA, const blacs_int RDEST, const blacs_int CDEST );
void Cztrsd2d( const blacs_int ICONTXT, const char* UPLO, const char* DIAG, 
               const blacs_int M, const blacs_int N, const dcomplex* A, 
               const blacs_int LDA, const blacs_int RDEST, const blacs_int CDEST );




// Recv
void Cigerv2d( const blacs_int ICONTXT, const blacs_int M, const blacs_int N,
               blacs_int* A, const blacs_int LDA, const blacs_int RSRC,
               const blacs_int CSRC );
void Csgerv2d( const blacs_int ICONTXT, const blacs_int M, const blacs_int N,
               float* A, const blacs_int LDA, const blacs_int RSRC,
               const blacs_int CSRC );
void Cdgerv2d( const blacs_int ICONTXT, const blacs_int M, const blacs_int N,
               double* A, const blacs_int LDA, const blacs_int RSRC,
               const blacs_int CSRC );
void Ccgerv2d( const blacs_int ICONTXT, const blacs_int M, const blacs_int N,
               scomplex* A, const blacs_int LDA, const blacs_int RSRC,
               const blacs_int CSRC );
void Czgerv2d( const blacs_int ICONTXT, const blacs_int M, const blacs_int N,
               dcomplex* A, const blacs_int LDA, const blacs_int RSRC,
               const blacs_int CSRC );

void Citrrv2d( const blacs_int ICONTXT, const char* UPLO, const char* DIAG, 
               const blacs_int M, const blacs_int N, blacs_int* A, 
               const blacs_int LDA, const blacs_int RSRC, const blacs_int CSRC );
void Cstrrv2d( const blacs_int ICONTXT, const char* UPLO, const char* DIAG, 
               const blacs_int M, const blacs_int N, float* A, const blacs_int LDA, 
               const blacs_int RSRC, const blacs_int CSRC );
void Cdtrrv2d( const blacs_int ICONTXT, const char* UPLO, const char* DIAG, 
               const blacs_int M, const blacs_int N, double* A, const blacs_int LDA, 
               const blacs_int RSRC, const blacs_int CSRC );
void Cctrrv2d( const blacs_int ICONTXT, const char* UPLO, const char* DIAG, 
               const blacs_int M, const blacs_int N, scomplex* A, 
               const blacs_int LDA, const blacs_int RSRC, const blacs_int CSRC );
void Cztrrv2d( const blacs_int ICONTXT, const char* UPLO, const char* DIAG, 
               const blacs_int M, const blacs_int N, dcomplex* A, 
               const blacs_int LDA, const blacs_int RSRC, const blacs_int CSRC );
}



namespace blacspp {
namespace wrappers {

// Send



// GESD2D
#define gesd2d_impl( fname, type )\
template <>                                                \
void gesd2d<type>(                                         \
  const int64_t ICONTXT, const int64_t M, const int64_t N, \
  const type* A, const int64_t LDA, const int64_t RDEST,   \
  const int64_t CDEST ) {                                  \
                                                           \
  auto _M   = detail::to_blacs_int( M   );                 \
  auto _N   = detail::to_blacs_int( N   );                 \
  auto _LDA = detail::to_blacs_int( LDA );                 \
  auto _RDEST = detail::to_blacs_int( RDEST );             \
  auto _CDEST = detail::to_blacs_int( CDEST );             \
                                                           \
  fname( ICONTXT, _M, _N, A, _LDA, _RDEST, _CDEST );       \
                                                           \
}

gesd2d_impl( Cigesd2d, blacs_int );
gesd2d_impl( Csgesd2d, float     );
gesd2d_impl( Cdgesd2d, double    );
gesd2d_impl( Ccgesd2d, scomplex  );
gesd2d_impl( Czgesd2d, dcomplex  );


// TRSD2D
#define trsd2d_impl( fname, type )\
template <>                                                           \
void trsd2d<type>(                                                    \
  const int64_t ICONTXT, const char* UPLO, const char* DIAG,          \
  const int64_t M, const int64_t N, const type* A, const int64_t LDA, \
  const int64_t RDEST, const int64_t CDEST ) {                        \
                                                                      \
  auto _M   = detail::to_blacs_int( M   );                            \
  auto _N   = detail::to_blacs_int( N   );                            \
  auto _LDA = detail::to_blacs_int( LDA );                            \
  auto _RDEST = detail::to_blacs_int( RDEST );                        \
  auto _CDEST = detail::to_blacs_int( CDEST );                        \
                                                                      \
  fname( ICONTXT, UPLO, DIAG, _M, _N, A, _LDA, _RDEST, _CDEST );      \
                                                                      \
}

trsd2d_impl( Citrsd2d, blacs_int );
trsd2d_impl( Cstrsd2d, float     );
trsd2d_impl( Cdtrsd2d, double    );
trsd2d_impl( Cctrsd2d, scomplex  );
trsd2d_impl( Cztrsd2d, dcomplex  );







// RECV

// GERV2D
#define gerv2d_impl( fname, type )\
template <>                                                \
void gerv2d<type>(                                         \
  const int64_t ICONTXT, const int64_t M, const int64_t N, \
  type* A, const int64_t LDA, const int64_t RSRC,          \
  const int64_t CSRC ) {                                   \
                                                           \
  auto _M   = detail::to_blacs_int( M   );                 \
  auto _N   = detail::to_blacs_int( N   );                 \
  auto _LDA = detail::to_blacs_int( LDA );                 \
  auto _RSRC = detail::to_blacs_int( RSRC );               \
  auto _CSRC = detail::to_blacs_int( CSRC );               \
                                                           \
  fname( ICONTXT, _M, _N, A, _LDA, _RSRC, _CSRC );         \
                                                           \
}

gerv2d_impl( Cigerv2d, blacs_int );
gerv2d_impl( Csgerv2d, float     );
gerv2d_impl( Cdgerv2d, double    );
gerv2d_impl( Ccgerv2d, scomplex  );
gerv2d_impl( Czgerv2d, dcomplex  );


// TRRV2D
#define trrv2d_impl( fname, type )\
template <>                                                     \
void trrv2d<type>(                                              \
  const int64_t ICONTXT, const char* UPLO, const char* DIAG,    \
  const int64_t M, const int64_t N, type* A, const int64_t LDA, \
  const int64_t RSRC, const int64_t CSRC ) {                    \
                                                                \
  auto _M   = detail::to_blacs_int( M   );                      \
  auto _N   = detail::to_blacs_int( N   );                      \
  auto _LDA = detail::to_blacs_int( LDA );                      \
  auto _RSRC = detail::to_blacs_int( RSRC );                    \
  auto _CSRC = detail::to_blacs_int( CSRC );                    \
                                                                \
  fname( ICONTXT, UPLO, DIAG, _M, _N, A, _LDA, _RSRC, _CSRC );  \
                                                                \
}

trrv2d_impl( Citrrv2d, blacs_int );
trrv2d_impl( Cstrrv2d, float     );
trrv2d_impl( Cdtrrv2d, double    );
trrv2d_impl( Cctrrv2d, scomplex  );
trrv2d_impl( Cztrrv2d, dcomplex  );

}
}
