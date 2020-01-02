#!/bin/bash

set -e
if [[ ! -z ${RECIPE_DEBUG+x} ]]; then
  set -x
fi

#
# _use_sudo=1
# _do_update=1
# _distribution="ubuntu1404"
#
install_python3_linux()
{
  if [[ ${_use_sudo} -eq 1 ]]; then
    local SUDO="sudo"
  fi

  if [[ ${_do_update} -eq 1 ]]; then
    ${SUDO} apt-get update
  fi

  ${SUDO} apt-get install -y \
      software-properties-common
  ${SUDO} add-apt-repository -y ppa:deadsnakes/ppa
  ${SUDO} apt-get update
  ${SUDO} apt-get install -y \
        python3.6 \
        python3.6-dev
  ${SUDO} apt-get purge -y python3
  ${SUDO} apt-get -y autoremove
  ${SUDO} ln -s -f /usr/bin/python3.6 /usr/bin/python3

  #
  # pip
  #
  curl https://bootstrap.pypa.io/get-pip.py -o /tmp/get-pip.py
  ${SUDO} python3 /tmp/get-pip.py

  cat <<EOF >> ~/.bashrc
  LC_ALL=C.UTF-8
  LANG=C.UTF-8
EOF
}

#
# _do_update=1
#
install_python3_osx()
{
  if [[ ${_do_update} -eq 1 ]]; then
    brew update
  fi

  brew install python
}
