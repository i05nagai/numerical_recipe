FROM ubuntu:16.04

#
# run on the top of repository
#
COPY ci /tmp/ci

RUN \
    apt-get update \
    && /tmp/ci/linux/install_bazel.sh \
    && /tmp/ci/linux/install_clang_format.sh \
    && /tmp/ci/linux/install_gcc.sh \
    && rm -rf /var/lib/apt/lists/* \
    && rm -rf /tmp/ci

ENV \
  CXX="g++-4.9" \
  CC="gcc-4.9"

