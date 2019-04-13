#!/bin/bash

PATH_TO_REPOSITORY=$(cd $(dirname ${0});cd ..;pwd)
cd $PATH_TO_REPOSITORY

./tools/docker/gcc/docker_run_ubuntu1604.sh ./tools/formatter.sh
