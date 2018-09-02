#!/bin/bash

set -e

#
# install gcc
# gcc does not exist on OSX by default
#
if [ "$TRAVIS_OS_NAME" == "osx" -a "$CXX" == "g++" ]; then
  gcc --version;
  g++ --version;
  brew update;
  brew install gcc@5 || brew link --overwrite gcc@5;
  gcc --version;
  g++ --version;
  export CXX="g++";
fi

#
# install g++4.9
#
if [[ "$TRAVIS_OS_NAME" == "linux" -a "$CXX" == "g++" ]]; then
  sudo apt-get update && sudo apt-get install -y gcc-4.9 g++-4.9
  export CXX="g++-4.9" CC="gcc-4.9";
fi
