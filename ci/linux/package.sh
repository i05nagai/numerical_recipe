#!/bin/bash

cat /etc/group
cat /etc/passwd
id

set -e
if [ ! -z "${RECIPE_DEBUG}" ]; then
  set -x
fi

UPLOAD_FLAG=$1

PATH_TO_REPOSITORY=$(cd $(dirname ${0});cd ../..;pwd)

cd ${PATH_TO_REPOSITORY}

bazel build //tools/pip_package:build_pip_package
./tools/pip_package/build_pip_package.sh dist

PYPI_REPOSITORY="--repository-url https://test.pypi.org/legacy/"
TWINE_USERNAME="__token__" 
if [[ "${UPLOAD_FLAG}" = "--no-test" ]]; then
  PYPI_REPOSITORY=""
fi

export TWINE_USERNAME

for WHL_PATH in $(ls dist/*dev*linux*.whl); do

  WHL_DIR=$(dirname "${WHL_PATH}")
  WHL_BASE_NAME=$(basename "${WHL_PATH}")
  AUDITED_WHL_NAME="${WHL_DIR}"/$(echo "${WHL_BASE_NAME//linux/manylinux2010}")

  # Copy and rename for gpu manylinux as we do not want auditwheel to package in libcudart.so
  WHL_PATH=${AUDITED_WHL_NAME}
  cp "${WHL_DIR}"/"${WHL_BASE_NAME}" "${WHL_PATH}"
  echo "Copied manylinux2010 wheel file at: ${WHL_PATH}"

  echo "Uploading package: ${AUDITED_WHL_NAME}"
  twine upload ${PYPI_REPOSITORY} "${AUDITED_WHL_NAME}"
done
