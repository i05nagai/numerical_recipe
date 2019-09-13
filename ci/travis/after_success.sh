#!/bin/bash

set -e
set -o pipefail
if [[ ! -z ${RECIPE_DEBUG+x} ]]; then
  set -x
fi

PATH_REPOSITORY=$(cd $(dirname ${0})/../..;pwd)

if [[ `echo "${BUILD_TARGET}" | grep -E '(Coverage$|Coverage,)'` && "${TRAVIS_OS_NAME}" == "linux" ]]; then
  echo "$(pwd)"
  gcov --version
  lcov --version
  ls -la

  path_coverage_file="${PATH_REPOSITORY}/coverage.dat"
  coverage_files=$(find ${PATH_REPOSITORY}/bazel-testlogs/recipe -name "coverage.dat" -a -not -empty)
  #
  # combine lcov capture files
  #
  lcov_args=$(echo "${coverage_files}" | awk '{print "-a " $0 }' | xargs)
  echo "lcov ${lcov_args} --output-file ${path_coverage_file}"
  lcov ${lcov_args} --output-file ${path_coverage_file}
  #
  # send report to coverall
  # be sure to export COVERALLS_REPO_TOKEN env variable
  #
  coveralls \
    --lcov-file ${path_coverage_file}
fi

# RECIPE_DEPLOY    true/false
if [[ "${RECIPE_DEPLOY}" = "true" ]]; then
  ${PATH_REPOSITORY}/ci/travis/deployment.sh ${PATH_REPOSITORY}
fi
