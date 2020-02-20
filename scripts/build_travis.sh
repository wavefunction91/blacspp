#!/bin/sh

echo $PWD

cmake -H. -B$BUILD_PREFIX -DCMAKE_TOOLCHAIN_FILE=$PWD/scripts/travis-toolchain.cmake -DCMAKE_INSTALL_PREFIX=$INSTALL_PREFIX
