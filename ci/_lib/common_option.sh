#!/bin/bash

if [[ ! -z ${RECIPE_DEBUG+x} ]]; then
  set -x
fi

#
# usage:
#   contain_element "${array_var[@]}" <value_of_element>
#
contain_element () {
  local e match="$1"
  shift
  for e; do
    [[ "$e" == "$match" ]] && return 0
  done
  return 1
}

while [[ $# -gt 0 ]]
do
  case ${1} in
    --debug|-d)
      set -x
    ;;

    --do-update|-s)
      # update package managers before installing
      readonly _do_update=1
    ;;

    --use-sudo|-S)
      # use sudo command to install packages
      readonly _use_sudo=1
    ;;

    --distribution|-d)
      readonly _distribution="$2"
      # valid values are
      valid_distributions=("ubuntu1404" "ubuntu1604")
      if contain_element "${valid_values[@]}" "${_distribution}" ; then
        echo "[ERROR] Invalid option '${1} ${2}'"
        exit 1
      fi
      shift || true
    ;;

    *)
      echo "[ERROR] Invalid option '${1}'"
      exit 1
    ;;
  esac
  shift || true  # in case of set -e
done
