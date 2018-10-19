#!/bin/bash

if [[ ! -z ${RECIPE_DEBUG+x} ]]; then
  set -x
fi

PATH_TO_CI=$(cd $(dirname ${0});cd ..;pwd)
source ${PATH_TO_CI}/_lib/common_option.sh

if [[ ${_use_sudo} -eq 1 ]]; then
  SUDO="sudo"
fi

if [[ ${_do_update} -eq 1 ]]; then
  ${SUDO} apt-get update
fi

${SUDO} apt-get install -y curl
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
