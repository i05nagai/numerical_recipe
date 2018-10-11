#!/bin/bash

PATH_TO_REPOSITORY=$(cd $(dirname ${0});cd ../../..;pwd)

docker run \
    --rm \
    -it \
    --volume ${PATH_TO_REPOSITORY}:/tmp/repository \
    --workdir /tmp/repository \
    recipe/gcc:4.9 \
    /bin/bash
