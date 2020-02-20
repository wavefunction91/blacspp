#!/bin/sh

echo $PWD
mpicc  -v

ls /usr/lib
ls /usr/lib64
ls /usr/local/lib
ls /usr/local/lib64

/usr/bin/cmake -H. -B$BUILD_PREFIX -DCMAKE_TOOLCHAIN_FILE=$PWD/scripts/travis-toolchain.cmake -DCMAKE_INSTALL_PREFIX=$INSTALL_PREFIX
