#!/bin/bash

set -e

#
# install clang-format
#
if [[ "$TRAVIS_OS_NAME" == "osx" ]]; then
  brew install clang-format
fi

#
# install clang-format
#
if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
  sudo apt-get install -y clang-format
fi
