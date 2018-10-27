#!/bin/bash

PATH_TO_REPOSITORY=$(cd $(dirname ${0});cd ../../../;pwd)
docker build \
  -t recipe/gcc:4.9 \
  -f ${PATH_TO_REPOSITORY}/tools/docker/gcc/ubuntu1404/Dockerfile \
  ${PATH_TO_REPOSITORY}
