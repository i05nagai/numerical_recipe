#!/bin/bash

set -e

function prepare_src() {
  if [ $# -lt 1 ] ; then
    echo "No destination dir provided"
    exit 1
  fi

  TMPDIR="${1%/}"
  mkdir -p "$TMPDIR"
  EXTERNAL_INCLUDES="${TMPDIR}/recipe/include/external"

  echo $(date) : "=== Preparing sources in dir: ${TMPDIR}"

  if [ ! -d bazel-bin/recipe ]; then
    echo "Could not find bazel-bin.  Did you run from the root of the build tree?"
    exit 1
  fi

  RUNFILES=bazel-bin/tools/pip_package/build_pip_package.runfiles/__main__

  # cp ${RUNFILES}/LICENSE ${TMPDIR}
  mkdir -p ${TMPDIR}/recipe
  mv ${RUNFILES}/recipe/python ${TMPDIR}/recipe
  touch ${TMPDIR}/recipe/__init__.py
  mkdir -p ${TMPDIR}/include
  cp -R -L ${RUNFILES}/recipe ${TMPDIR}/include
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

  TMPDIR="$1"
  DEST="$2"

  # Before we leave the top-level directory, make sure we know how to
  # call python.
  if [[ -e tools/python_bin_path.sh ]]; then
    source tools/python_bin_path.sh
  fi

  pushd ${TMPDIR}

  echo $(date) : "=== Building wheel"
  "${PYTHON_BIN_PATH:-python3}" setup.py bdist_wheel
  mkdir -p ${DEST}
  cp dist/* ${DEST}
  popd
  echo $(date) : "=== Output wheel file is in: ${DEST}"
}

TEMPDIR="$(mktemp -d -t tmp.XXXXXXXXXX)"
prepare_src "$TEMPDIR"
build_wheel "$TEMPDIR" "$1"
