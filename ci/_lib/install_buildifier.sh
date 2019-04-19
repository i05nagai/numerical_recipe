#!/bin/bash

set -e
if [[ ! -z ${RECIPE_DEBUG+x} ]]; then
  set -x
fi

#
# install_buildifier.sh
#
# variables:
#   * _do_update=1
#   * _use_sudo=1
#
install_buildifier_linux()
{

  if [[ ${_use_sudo} -eq 1 ]]; then
    local SUDO="sudo"
  fi

  if [[ ${_do_update} -eq 1 ]]; then
    ${SUDO} apt-get update
  fi

  #
  # install golang
  #
  # export GOPATH="/opt/local/golang"
  # export PATH="$PATH:/usr/lib/go-1.10/bin:$GOPATH/bin"
  # echo 'export GOPATH="'$GOPATH'"' | ${SUDO} tee -a ${HOME}/.bashrc
  # echo 'export PATH="'$PATH'"' | ${SUDO} tee -a ${HOME}/.bashrc

  # ${SUDO} apt-get install -y \
  #   software-properties-common \
  #   curl
  # ${SUDO} mkdir -p \
  #     $GOPATH/bin
  # ${SUDO} add-apt-repository ppa:gophers/archive < /dev/null
  # ${SUDO} apt-get update
  # ${SUDO} GOPATH="$GOPATH" PATH="$PATH" apt-get install -y \
  #       git \
  #       golang-1.10-go
  # ${SUDO} GOPATH="$GOPATH" PATH="$PATH" /usr/lib/go-1.10/bin/go get github.com/bazelbuild/buildtools/buildifier
}

#
# variables:
#   * _do_update=1
#
install_buildifier_osx()
{
  if [[ ${_do_update} -eq 1 ]]; then
    brew update
  fi

  brew install buildifier
}
