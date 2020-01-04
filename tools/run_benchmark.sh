#!/bin/bash

set -e
if [ ! -z "${RECIPE_DEBUG}" ]; then
  set -x
fi

PATH_TO_REPOSITORY=$(cd $(dirname ${0});cd ..;pwd)
cd $PATH_TO_REPOSITORY

run_benchmark()
{
  local subpackage="$1"
  bazel \
    --output_base=$HOME/.cache/bazel \
    run \
    --compilation_mode=opt \
    "//benchmark/numrecipe/${subpackage}"
}

pwd
run_benchmark integrate
run_benchmark sandbox
run_benchmark util
