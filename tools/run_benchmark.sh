#!/bin/bash

set -e

PATH_TO_REPOSITORY=$(cd $(dirname ${0});cd ..;pwd)
cd $PATH_TO_REPOSITORY

run_benchmark()
{
  local subpackage="$1"
  bazel run --compilation_mode=opt "//benchmark/recipe/${subpackage}"
}

run_benchmark integrate
run_benchmark sandbox
run_benchmark util
