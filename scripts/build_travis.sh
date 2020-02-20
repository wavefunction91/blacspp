#!/bin/sh

echo $PWD
mpicc  -v

dpkg -L libscalapack-mpich-dev 

/usr/bin/cmake -H. -B$BUILD_PREFIX -DCMAKE_TOOLCHAIN_FILE=$PWD/scripts/travis-toolchain.cmake -DCMAKE_INSTALL_PREFIX=$INSTALL_PREFIX
make -j4 -C $BUILD_PREFIX install
make test
