#!/bin/bash

PATH_TO_REPOSITORY=$(cd $(dirname ${0});cd ../../..;pwd)

# if no arguments are provided
args=$@
if [[ -z "${args}" ]]; then
  args=/bin/bash
fi

docker run \
    --rm \
    -it \
    --name gcc1404 \
    --volume ${PATH_TO_REPOSITORY}:/tmp/repository \
    --workdir /tmp/repository \
    recipe/gcc:4.9 \
    $args
