#!/bin/bash

PATH_TO_SCRIPT=$( cd ${0%/*} && pwd -P )
PATH_TO_ROOT=$( cd "$PATH_TO_SCRIPT/../.." && pwd -P )

echo $LANG
echo $LC_ALL
ls -la

#
# install
#
${PATH_TO_ROOT}/ci/travis/install_bazel.sh
${PATH_TO_ROOT}/ci/travis/install_gcc.sh
${PATH_TO_ROOT}/ci/travis/install_valgrind.sh

#
# coverage report
# we only measure coverage on Linux
#
if [[ "${BUILD_TYPE}" == "Coverage" && "${TRAVIS_OS_NAME}" == "linux" ]]; then
  PATH=~/.local/bin:${PATH};
  pip install --user --upgrade pip;
  pip install --user cpp-coveralls;
fi

echo ${PATH}
echo ${CXX}
${CXX} --version
${CXX} -v
