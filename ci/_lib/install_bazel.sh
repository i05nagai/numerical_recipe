#!/bin/bash

set -e
if [[ ! -z ${RECIPE_DEBUG+x} ]]; then
  set -x
fi

#
# install_bazel.sh
#
# variables:
#   * _do_update=1
#   * _use_sudo=1
#   * _do_update=1
#
install_bazel_linux()
{

  if [[ ${_use_sudo} -eq 1 ]]; then
    local SUDO="sudo"
  fi

  if [[ ${_do_update} -eq 1 ]]; then
    ${SUDO} apt-get update
  fi

  # bazel's git_repository rule requires git
  # if you run bazel-coverage command, you need to install lcov and gcov
  ${SUDO} apt-get install -y \
    software-properties-common \
    git \
    lcov \
    curl

  # install JDK
  ${SUDO} add-apt-repository -y ppa:webupd8team/java
  ${SUDO} apt-get update
  # to automatically agree with license of openjdk
  echo debconf shared/accepted-oracle-license-v1-1 select true | \
    ${SUDO} debconf-set-selections
  echo debconf shared/accepted-oracle-license-v1-1 seen true | \
    ${SUDO} debconf-set-selections
  ${SUDO} apt-get install -y openjdk-8-jdk

  echo "deb [arch=amd64] http://storage.googleapis.com/bazel-apt stable jdk1.8" | ${SUDO} tee /etc/apt/sources.list.d/bazel.list
  curl https://bazel.build/bazel-release.pub.gpg | ${SUDO} apt-key add -
  ${SUDO} apt-get update
  ${SUDO} apt-get install -y bazel
}

#
# variables:
#   * _do_update=1
#
install_bazel_osx()
{
  if [[ ${_do_update} -eq 1 ]]; then
    brew update
  fi

  brew uninstall bazel
  # tap and install
  brew tap bazelbuild/tap
  brew tap-pin bazelbuild/tap
  brew install bazel
}
