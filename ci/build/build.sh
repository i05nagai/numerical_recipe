#!/bin/bash

bazel \
  --output_base=$HOME/.cache/bazel \
  build \
  "//recipe/..."
bazel \
  --output_base=$HOME/.cache/bazel \
  test \
  "//recipe/..."
