#!/bin/bash

if [[ ! -z ${RECIPE_DEBUG+x} ]]; then
  set -x
fi

PATH_TO_SCRIPT=$( cd ${0%/*} && pwd -P )
PATH_TO_ROOT=$( cd "$PATH_TO_SCRIPT/../.." && pwd -P )

echo $LANG
echo $LC_ALL
ls -la

if [[ "$TRAVIS_OS_NAME" == "osx" ]]; then
  brew --version
  # ignore auto-update failure
  brew update || true
  # disable auto-update
  export HOMEBREW_NO_AUTO_UPDATE=1
fi

#
# install
# sourcing is required to export some variables
#
source ${PATH_TO_ROOT}/ci/travis/install_bazel.sh
source ${PATH_TO_ROOT}/ci/travis/install_buildifier.sh
source ${PATH_TO_ROOT}/ci/travis/install_clang_format.sh
source ${PATH_TO_ROOT}/ci/travis/install_gcc.sh
source ${PATH_TO_ROOT}/ci/travis/install_python3.sh
# ${PATH_TO_ROOT}/ci/travis/install_valgrind.sh

#
# coverage report
# we only measure coverage on Linux
#
if [[ `echo "${BUILD_TARGET}" | grep -E '(Coverage$|Coverage,)'` && "${TRAVIS_OS_NAME}" == "linux" ]]; then
  export PATH=~/.local/bin:${PATH};
  # pip install --user --upgrade pip;
  # pip install --user cpp-coveralls;
  source ${PATH_TO_ROOT}/ci/travis/install_coveralls.sh
fi

echo ${PATH}
echo ${CXX}
${CXX} --version
${CXX} -v
