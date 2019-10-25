#include <blacspp/wrappers/combine.hpp>

using blacspp::blacs_int;
using blacspp::scomplex;
using blacspp::dcomplex;

// Prototypes
extern "C" {

// Element-wise sum
void Cigsum2d( const blacs_int ICONTXT, const char* SCOPE, const char* TOP, 
               const blacs_int M, const blacs_int N, blacs_int* A, 
               const blacs_int LDA, const blacs_int RDEST, const blacs_int CDEST );
void Csgsum2d( const blacs_int ICONTXT, const char* SCOPE, const char* TOP, 
               const blacs_int M, const blacs_int N, float* A, 
               const blacs_int LDA, const blacs_int RDEST, const blacs_int CDEST );
void Cdgsum2d( const blacs_int ICONTXT, const char* SCOPE, const char* TOP, 
               const blacs_int M, const blacs_int N, double* A, 
               const blacs_int LDA, const blacs_int RDEST, const blacs_int CDEST );
void Ccgsum2d( const blacs_int ICONTXT, const char* SCOPE, const char* TOP, 
               const blacs_int M, const blacs_int N, scomplex* A, 
               const blacs_int LDA, const blacs_int RDEST, const blacs_int CDEST );
void Czgsum2d( const blacs_int ICONTXT, const char* SCOPE, const char* TOP, 
               const blacs_int M, const blacs_int N, dcomplex* A, 
               const blacs_int LDA, const blacs_int RDEST, const blacs_int CDEST );

// Element-wise max
void Cigamx2d( const blacs_int ICONTXT, const char* SCOPE, const char* TOP, 
               const blacs_int M, const blacs_int N, blacs_int* A, 
               const blacs_int LDA, blacs_int* RA, blacs_int* CA, 
               const blacs_int RCFLAG, const blacs_int RDEST, 
               const blacs_int CDEST );
void Csgamx2d( const blacs_int ICONTXT, const char* SCOPE, const char* TOP, 
               const blacs_int M, const blacs_int N, float* A, 
               const blacs_int LDA, blacs_int* RA, blacs_int* CA, 
               const blacs_int RCFLAG, const blacs_int RDEST, 
               const blacs_int CDEST );
void Cdgamx2d( const blacs_int ICONTXT, const char* SCOPE, const char* TOP, 
               const blacs_int M, const blacs_int N, double* A, 
               const blacs_int LDA, blacs_int* RA, blacs_int* CA, 
               const blacs_int RCFLAG, const blacs_int RDEST, 
               const blacs_int CDEST );
void Ccgamx2d( const blacs_int ICONTXT, const char* SCOPE, const char* TOP, 
               const blacs_int M, const blacs_int N, scomplex* A, 
               const blacs_int LDA, blacs_int* RA, blacs_int* CA, 
               const blacs_int RCFLAG, const blacs_int RDEST, 
               const blacs_int CDEST );
void Czgamx2d( const blacs_int ICONTXT, const char* SCOPE, const char* TOP, 
               const blacs_int M, const blacs_int N, dcomplex* A, 
               const blacs_int LDA, blacs_int* RA, blacs_int* CA, 
               const blacs_int RCFLAG, const blacs_int RDEST, 
               const blacs_int CDEST );

// Element-wise min
void Cigamn2d( const blacs_int ICONTXT, const char* SCOPE, const char* TOP, 
               const blacs_int M, const blacs_int N, blacs_int* A, 
               const blacs_int LDA, blacs_int* RA, blacs_int* CA, 
               const blacs_int RCFLAG, const blacs_int RDEST, 
               const blacs_int CDEST );
void Csgamn2d( const blacs_int ICONTXT, const char* SCOPE, const char* TOP, 
               const blacs_int M, const blacs_int N, float* A, 
               const blacs_int LDA, blacs_int* RA, blacs_int* CA, 
               const blacs_int RCFLAG, const blacs_int RDEST, 
               const blacs_int CDEST );
void Cdgamn2d( const blacs_int ICONTXT, const char* SCOPE, const char* TOP, 
               const blacs_int M, const blacs_int N, double* A, 
               const blacs_int LDA, blacs_int* RA, blacs_int* CA, 
               const blacs_int RCFLAG, const blacs_int RDEST, 
               const blacs_int CDEST );
void Ccgamn2d( const blacs_int ICONTXT, const char* SCOPE, const char* TOP, 
               const blacs_int M, const blacs_int N, scomplex* A, 
               const blacs_int LDA, blacs_int* RA, blacs_int* CA, 
               const blacs_int RCFLAG, const blacs_int RDEST, 
               const blacs_int CDEST );
void Czgamn2d( const blacs_int ICONTXT, const char* SCOPE, const char* TOP, 
               const blacs_int M, const blacs_int N, dcomplex* A, 
               const blacs_int LDA, blacs_int* RA, blacs_int* CA, 
               const blacs_int RCFLAG, const blacs_int RDEST, 
               const blacs_int CDEST );

};




namespace blacspp {
namespace wrappers {

// Element-wise sum
#define gsum2d_impl( fname, type )\
template <>                                                           \
void gsum2d<type>(                                                    \
  const blacs_int ICONTXT, const char* SCOPE, const char* TOP,          \
  const blacs_int M, const blacs_int N, type* A, const blacs_int LDA, \
  const blacs_int RDEST, const blacs_int CDEST ) {                    \
                                                                      \
  fname( ICONTXT, SCOPE, TOP, M, N, A, LDA, RDEST, CDEST );           \
                                                                      \
}

gsum2d_impl( Cigsum2d, blacs_int );
gsum2d_impl( Csgsum2d, float     );
gsum2d_impl( Cdgsum2d, double    );
gsum2d_impl( Ccgsum2d, scomplex  );
gsum2d_impl( Czgsum2d, dcomplex  );

// Element-wise max
#define gamx2d_impl( fname, type )\
template <>                                                                 \
void gamx2d<type>(                                                          \
  const blacs_int ICONTXT, const char* SCOPE, const char* TOP,                \
  const blacs_int M, const blacs_int N, type* A, const blacs_int LDA,       \
  blacs_int* RA, blacs_int* CA, const blacs_int RCFLAG,                     \
  const blacs_int RDEST, const blacs_int CDEST ) {                          \
                                                                            \
  fname( ICONTXT, SCOPE, TOP, M, N, A, LDA, RA, CA, RCFLAG, RDEST, CDEST ); \
                                                                            \
}

gamx2d_impl( Cigamx2d, blacs_int );
gamx2d_impl( Csgamx2d, float     );
gamx2d_impl( Cdgamx2d, double    );
gamx2d_impl( Ccgamx2d, scomplex  );
gamx2d_impl( Czgamx2d, dcomplex  );

// Element-wise min
#define gamn2d_impl( fname, type )\
template <>                                                                 \
void gamn2d<type>(                                                          \
  const blacs_int ICONTXT, const char* SCOPE, const char* TOP,                \
  const blacs_int M, const blacs_int N, type* A, const blacs_int LDA,       \
  blacs_int* RA, blacs_int* CA, const blacs_int RCFLAG,                     \
  const blacs_int RDEST, const blacs_int CDEST ) {                          \
                                                                            \
  fname( ICONTXT, SCOPE, TOP, M, N, A, LDA, RA, CA, RCFLAG, RDEST, CDEST ); \
                                                                            \
}

gamn2d_impl( Cigamn2d, blacs_int );
gamn2d_impl( Csgamn2d, float     );
gamn2d_impl( Cdgamn2d, double    );
gamn2d_impl( Ccgamn2d, scomplex  );
gamn2d_impl( Czgamn2d, dcomplex  );

}
}
