#!/bin/bash

set -e

PATH_TO_REPOSITORY=$(cd $(dirname ${0});cd ..;pwd)
cd $PATH_TO_REPOSITORY

for filename in $(find recipe -name '*.h' -o -name '*.cc'); do
  clang-format -i $filename
  # clang-format --style=google $filename | diff $filename - > /dev/null
done
