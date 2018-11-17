#!/bin/bash

PATH_TO_REPOSITORY=$(cd $(dirname ${0});cd ../../../;pwd)
docker build \
  -t recipe/sphinx:latest \
  -f ${PATH_TO_REPOSITORY}/tools/docker/sphinx/Dockerfile \
  ${PATH_TO_REPOSITORY}
