#!/bin/bash

set -e

#
# Install valgrind
# valgrind does not work in osx, so we only run tests with valgrind on linux
#
if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
  sudo apt-get install -y curl
  export BASEPATH=`pwd`;
  mkdir -p ${BASEPATH}/usr ;
  export PATH="${BASEPATH}/usr/bin:$PATH" ;
  export LD_LIBRARY_PATH="${BASEPATH}/usr/lib:$LD_LIBRARY_PATH";
  curl -L -O http://valgrind.org/downloads/valgrind-3.12.0.tar.bz2 ;
  tar xjf valgrind-3.12.0.tar.bz2 ;
  cd valgrind-3.12.0 ;
  ./configure --prefix=${BASEPATH}/usr > /dev/null ;
  make -j3 > /dev/null ;
  make install > /dev/null ;
  cd .. ;
  valgrind --version;
fi
