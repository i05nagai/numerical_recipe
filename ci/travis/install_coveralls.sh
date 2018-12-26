#!/bin/bash

set -e
if [[ ! -z ${RECIPE_DEBUG+x} ]]; then
  set -x
fi

PATH_TO_CI=$(cd $(dirname ${0});cd ..;pwd)
source ${PATH_TO_CI}/_lib/install_coverage_misc.sh

PATH_TO_CI=$(cd $(dirname ${0});cd ..;pwd)
if [[ "$TRAVIS_OS_NAME" == "" ]]; then
  echo '$TRAVIS_OS_NAME is not set.'
  exit 1
fi

if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
  _use_sudo=1 install_coverage_misc_linux
fi

if [[ "$TRAVIS_OS_NAME" == "osx" ]]; then
  echo "install_coveralls.sh for OSX is not supported"
  # install_coverage_misc_osx
fi
