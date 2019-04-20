#!/bin/bash

set -e
if [[ ! -z ${RECIPE_DEBUG+x} ]]; then
  set -x
fi

PATH_TO_CI=$(cd $(dirname ${0});cd ..;pwd)
source ${PATH_TO_CI}/_lib/install_buildifier.sh

_use_sudo=${_use_sudo} _do_update=${_do_update} install_buildifier_linux
