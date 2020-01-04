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

for WHL_PATH in $(ls dist/*dev*osx*.whl); do
  twine upload ${PYPI_REPOSITORY} "${AUDITED_WHL_NAME}"
done
