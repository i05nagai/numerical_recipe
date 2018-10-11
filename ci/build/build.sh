#!/bin/bash

bazel \
  --output_base=$HOME/.cache/bazel \
  build \
  "//recipe/..."
bazel \
  --output_base=$HOME/.cache/bazel \
  test \
  --test_output=errors \
  "//recipe/..."
