#!/bin/bash

if [[ "${BUILD_TYPE}" == "Coverage" -a "${TRAVIS_OS_NAME}" == "linux" ]]; then
  pwd;
  coveralls \
    --verbose \
    --include recipe \
    --exclude submodule \
    --gcov-options '\-lp' \
    --root . \
    --build-root build;
fi
