#!/bin/bash

set -e
set -x

readonly path_to_repository=$(cd $(dirname ${0});cd ../../../;pwd)
readonly repository_name=$(basename ${path_to_repository})
readonly path_to_repository_in_docker=/tmp/${repository_name}

docker run -it --rm \
  --volume ${path_to_repository}:${path_to_repository_in_docker} \
  recipe/sphinx:latest \
  doxygen -g ${path_to_repository_in_docker}/Doxyfile
