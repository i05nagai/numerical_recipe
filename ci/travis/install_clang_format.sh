#!/bin/bash

set -e
if [[ ! -z ${RECIPE_DEBUG+x} ]]; then
  set -x
fi

PATH_TO_CI=$(cd $(dirname ${0});cd ..;pwd)
source ${PATH_TO_CI}/_lib/install_clang_format.sh

PATH_TO_CI=$(cd $(dirname ${0});cd ..;pwd)
if [[ "$TRAVIS_OS_NAME" == "" ]]; then
  echo '$TRAVIS_OS_NAME is not set.'
  exit 1
fi

if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
  _use_sudo=1 install_clang_format_linux
fi

if [[ "$TRAVIS_OS_NAME" == "osx" ]]; then
  install_clang_format_osx
fi
