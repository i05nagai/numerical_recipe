#!/bin/bash

set -e
set -o pipefail
set -o nounset

if [[ `echo "${BUILD_TARGET}" | grep -E '(Coverage$|Coverage,)'` && "${TRAVIS_OS_NAME}" == "linux" ]]; then
  # -g
  pwd;
  coveralls \
    --verbose \
    --include recipe \
    --gcov-options '\-lp' \
    --root . \
    --build-root bazel-out/darwin-dbg/bin/recipe
fi
