#!/bin/bash

set -e
if [[ ! -z ${RECIPE_DEBUG+x} ]]; then
  set -x
fi

PATH_TO_CI=$(cd $(dirname ${0});cd ..;pwd)

if [[ "$TRAVIS_OS_NAME" == "" ]]; then
  echo '$TRAVIS_OS_NAME is not set.'
  exit 1
fi

#
# Install valgrind
# valgrind does not work in osx, so we only run tests with valgrind on linux
#
if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
  ${PATH_TO_CI}/${TRAVIS_OS_NAME}/install_valgrind.sh --use-sudo
fi
