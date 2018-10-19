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
# _distribution="ubuntu1404"
#
install_gcc49_linux()
{
  if [[ ${_use_sudo} -eq 1 ]]; then
    local SUDO="sudo"
  fi

  if [[ ${_do_update} -eq 1 ]]; then
    ${SUDO} apt-get update
  fi

  local UBUNTU_VERSION=`get_ubuntu_version`
  if [[ ${UBUNTU_VERSION} == "14.04" ]]; then
    ${SUDO} add-apt-repository ppa:ubuntu-toolchain-r/test < /dev/null
    ${SUDO} apt-get update
  fi

  ${SUDO} apt-get install -y \
    gcc-4.9 \
    g++-4.9

  export CXX="g++-4.9"
  export CC="gcc-4.9"
}

#
# _do_update=1
#
install_gcc49_osx()
{
  if [[ ${_do_update} -eq 1 ]]; then
    brew update
  fi

  gcc --version
  g++ --version
  brew install gcc@5 || brew link --overwrite gcc@5
  gcc --version
  g++ --version
}
