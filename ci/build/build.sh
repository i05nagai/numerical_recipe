#!/bin/bash

cat /etc/group
cat /etc/passwd
id

set -e
if [ ! -z "${RECIPE_DEBUG}" ]; then
  set -x
fi

PATH_TO_REPOSITORY=$(cd $(dirname ${0});cd ../..;pwd)

run_build() {
  bazel \
    --output_base=$HOME/.cache/bazel \
    build \
    ${BAZEL_OPTION} \
    "//numrecipe/..."
}

run_test() {
  bazel \
    --output_base=$HOME/.cache/bazel \
    test \
    --test_output=errors \
    ${BAZEL_OPTION} \
    "//numrecipe/..."
}

run_coverage() {
  # py_test doesn't support coverage
  for target in $(ls numrecipe | grep -v python); do
    bazel \
      --output_base=$HOME/.cache/bazel \
      coverage \
      --test_output=errors \
      ${BAZEL_OPTION} \
      "//numrecipe/${target}/..."
  done
}

run_benchmark() {
  ${PATH_TO_REPOSITORY}/tools/run_benchmark.sh
}

is_covereage() {
  [[ `echo "${BUILD_TARGET}" | grep -E '(Coverage$|Coverage,)'` ]]
}

is_benchmark() {
  [[ `echo "${BUILD_TARGET}" | grep -E '(Benchmark$|Benchmark,)'` ]]
}


if [[ "${BUILD_TYPE}" == "Release" ]]; then
  BAZEL_OPTION="${BAZEL_OPTION} --compilation_mode=opt"
else
  # by default, debug build
  # but if we build benchmarks, we build it with optimization
  if is_benchmark; then
    echo "Warning! Force to compile with optimization because benchmarks are buiit"
    BAZEL_OPTION="${BAZEL_OPTION} --compilation_mode=opt"
  else
    BAZEL_OPTION="${BAZEL_OPTION} --compilation_mode=dbg"
  fi
fi

#
# build and test
#
run_build

if is_covereage; then
  run_test
  run_coverage
elif is_benchmark; then
  run_test
  run_benchmark
else
  run_test
fi
