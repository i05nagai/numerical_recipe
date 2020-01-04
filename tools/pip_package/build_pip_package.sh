#!/bin/bash

set -e
set -x

function prepare_src() {
  if [ $# -lt 1 ] ; then
    echo "No destination dir provided"
    exit 1
  fi

  TMPDIR="${1%/}"
  mkdir -p "$TMPDIR"
  EXTERNAL_INCLUDES="${TMPDIR}/numrecipe/include/external"

  echo $(date) : "=== Preparing sources in dir: ${TMPDIR}"

  if [ ! -d bazel-bin/numrecipe ]; then
    echo "Could not find bazel-bin.  Did you run from the root of the build tree?"
    exit 1
  fi

  RUNFILES=bazel-bin/tools/pip_package/build_pip_package.runfiles/__main__

  # cp ${RUNFILES}/LICENSE ${TMPDIR}
  mkdir -p ${TMPDIR}/numrecipe
  cp -r -L ${RUNFILES}/numrecipe/python ${TMPDIR}/numrecipe
  touch ${TMPDIR}/numrecipe/__init__.py
  mkdir -p ${TMPDIR}/include
  cp -R -L ${RUNFILES}/numrecipe ${TMPDIR}/include
  cp -r -L ${RUNFILES}/external/eigen3/Eigen ${TMPDIR}/include
  cp -r -L ${RUNFILES}/external/eigen3/unsupported ${TMPDIR}/include

  cp tools/pip_package/MANIFEST.in ${TMPDIR}
  cp tools/pip_package/README.md ${TMPDIR}
  cp tools/pip_package/setup.py ${TMPDIR}
}

function build_wheel() {
  if [ $# -lt 2 ] ; then
    echo "No src and dest dir provided"
    exit 1
  fi

  local TMPDIR="$1"
  local DEST="$2"

  # Before we leave the top-level directory, make sure we know how to
  # call python.
  if [[ -e tools/python_bin_path.sh ]]; then
    source tools/python_bin_path.sh
  fi

  echo $(date) : "=== Building wheel"

  pushd ${TMPDIR}
  "${PYTHON_BIN_PATH:-python3}" setup.py bdist_wheel
  popd

  mkdir -p ${DEST}
  cp -f ${TEMPDIR}/dist/* ${DEST}

  echo $(date) : "=== Output wheel file is in: ${DEST}"
}

TEMPDIR="$(mktemp -d -t tmp.XXXXXXXXXX)"
prepare_src "$TEMPDIR"
build_wheel "$TEMPDIR" "$1"
