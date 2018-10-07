#!/bin/bash

set -e

PATH_TO_REPOSITORY=$(cd $(dirname ${0});cd ..;pwd)
cd $PATH_TO_REPOSITORY

buildifier \
  -showlog \
  -mode=fix \
  $(find . -type f -name BUILD -or -name 'BUILD.*' -or -name BUILD.bazel)
