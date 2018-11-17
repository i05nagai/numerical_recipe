#!/bin/bash

set -x
set -e

readonly path_to_repository=$(cd $(dirname ${0});cd ../../../;pwd)
readonly repository_name=$(basename ${path_to_repository})
readonly path_to_repository_in_docker=/tmp/${repository_name}

command=$(cat << EOS
cd ${path_to_repository_in_docker};
doxygen ${path_to_repository_in_docker}/Doxyfile;
sphinx-build ${path_to_repository_in_docker}/docs ${path_to_repository_in_docker}/docs/_build;
EOS
)

docker run -it --rm \
  --volume ${path_to_repository}:${path_to_repository_in_docker} \
  recipe/sphinx:latest \
  /bin/bash -c "${command}"
