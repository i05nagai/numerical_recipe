#!/bin/bash

set -e
if [[ ! -z ${RECIPE_DEBUG+x} ]]; then
  set -x
fi

#
#
#
install_coverage_misc_linux()
{
  if [[ ${_use_sudo} -eq 1 ]]; then
    local SUDO="sudo"
  fi

  if [[ ${_do_update} -eq 1 ]]; then
    ${SUDO} apt-get update
  fi

  # bazel-coverage command requires lcov and gcov
  ${SUDO} apt-get install -y \
    lcov \
    curl

  ${SUDO} curl https://bootstrap.pypa.io/get-pip.py -o $HOME/get-pip.py
  ${SUDO} python $HOME/get-pip.py
  ${SUDO} pip install cpp-coveralls
}

#
# variables:
#   * _do_update=1
#
install_coverage_misc_osx()
{
  if [[ ${_do_update} -eq 1 ]]; then
    brew update
  fi

  brew install gcov
  brew install lcov
}
