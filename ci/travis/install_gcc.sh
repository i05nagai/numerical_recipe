#!/bin/bash

#
# The script export CXX and CC, so you need to source the script
#
# Usage:
# source install_gcc.sh
#

set -e
if [[ ! -z ${RECIPE_DEBUG+x} ]]; then
  set -x
fi

PATH_TO_CI=$(cd $(dirname ${0});cd ..;pwd)
source ${PATH_TO_CI}/_lib/install_gcc.sh

if [[ "$TRAVIS_OS_NAME" == "" ]]; then
  echo '$TRAVIS_OS_NAME is not set.'
  exit 1
fi

#
# install gcc
# gcc does not exist on OSX by default
#
if [[ "$TRAVIS_OS_NAME" == "osx" && "$CXX" == "g++" ]]; then
  install_gcc49_osx
  export CXX="g++";
fi

#
# install g++4.9
#
if [[ "$TRAVIS_OS_NAME" == "linux" && "$CXX" == "g++" ]]; then
  _use_sudo=1 _distribution="ubuntu1404" install_gcc49_linux
  export CXX="g++-4.9"
  export CC="gcc-4.9"
fi
