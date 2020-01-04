#!/bin/bash

set -e

formatting() {
  local directory_name="$1"
  for filename in $(find ${directory_name} -name '*.h' -o -name '*.cc'); do
    clang-format -i $filename
    # clang-format --style=google $filename | diff $filename - > /dev/null
  done
}

PATH_TO_REPOSITORY=$(cd $(dirname ${0});cd ..;pwd)
cd $PATH_TO_REPOSITORY

#
# under recipe/
#
formatting numrecipe

#
# under benchmark/
#
formatting benchmark
