#!/bin/bash

set -e
if [[ ! -z ${RECIPE_DEBUG+x} ]]; then
  set -x
fi

PATH_TO_LIB=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd )
source ${PATH_TO_LIB}/util.sh

#
# _use_sudo=1
# _do_update=1
#
install_clang_format_linux()
{
  if [[ ${_use_sudo} -eq 1 ]]; then
    local SUDO="sudo"
  fi

  if [[ ${_do_update} -eq 1 ]]; then
    ${SUDO} apt-get update
  fi

  UBUNTU_VERSION=`get_ubuntu_version`
  if [[ "$UBUNTU_VERSION" == "14.04" ]]; then
    ${SUDO} apt-get install -y clang-format-3.9
  else
    ${SUDO} apt-get install -y clang-format
  fi
  clang-format --version
}

#
#
#
install_clang_format_osx()
{
  if [[ ${_do_update} -eq 1 ]]; then
    brew update
  fi

  brew install clang-format
}
