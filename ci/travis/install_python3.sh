#!/bin/bash

set -e

if [[ ! -z ${RECIPE_DEBUG+x} ]]; then
  set -x
fi

PATH_TO_CI=$(cd $(dirname ${0});cd ..;pwd)
source ${PATH_TO_CI}/_lib/install_python3.sh

if [[ "$TRAVIS_OS_NAME" == "" ]]; then
  echo "\$TRAVIS_OS_NAME is not set."
  exit 1
fi

if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
  _use_sudo=1 install_python3_linux
fi

if [[ "$TRAVIS_OS_NAME" == "osx" ]]; then
  echo "Skip installing python3: $(python3 --version)"
  # 3.7.5 is installed as of 2020-01-02
  # install_python3_osx
fi
