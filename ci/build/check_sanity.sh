#!/bin/bash

do_buildifier(){
  local build_files=$(find . -type f -name BUILD -or -name 'BUILD.*' -or -name BUILD.bazel)
  local num_build_files=$(echo ${build_files} | wc -w)

  echo "Running do_buildifier on ${num_build_files} files"
  echo ""

  local buildifier_start_time=$(date +'%s')
  local buildifier_output_file="$(mktemp)_buildifier_output.log"

  rm -rf ${buildifier_output_file}

  buildifier -showlog -v -mode=check \
    ${build_files} 2>&1 | tee ${buildifier_output_file}
  local BUILDIFIER_END_TIME=$(date +'%s')

  echo ""
  echo "buildifier took $((BUILDIFIER_END_TIME - buildifier_start_time)) s"
  echo ""

  if [[ -s ${buildifier_output_file} ]]; then
    echo "FAIL: buildifier found errors and/or warnings in above BUILD files."
    echo "buildifier suggested the following changes:"
    buildifier -showlog -v -mode=diff ${build_files}
    echo "Please fix manually or run buildifier <file> to auto-fix."
    return 1
  else
    echo "PASS: No buildifier errors or warnings were found"
    return 0
  fi
}

# Get the hash of the last non-merge git commit on the current branch.
# Usage: get_last_non_merge_git_commit
get_last_non_merge_git_commit() {
  git rev-list --no-merges -n 1 HEAD
}

# List files changed (i.e., added, removed or revised) in the last non-merge
# git commit.
# Usage: get_changed_files_in_last_non_merge_git_commit
get_changed_files_in_last_non_merge_git_commit() {
  git diff-tree --no-commit-id --name-only -r $(get_last_non_merge_git_commit)
}

# List .h|.cc files changed in the last non-merge git commit that still exist,
# i.e., not removed.
# Usage: get_clang_files_to_check [--incremental]
get_clang_files_to_check() {
  if [[ "$1" == "--incremental" ]]; then
    CHANGED_CLANG_FILES=$(get_changed_files_in_last_non_merge_git_commit | \
                       grep '.*\.h$\|.*\.cc$')

    # Do not include files removed in the last non-merge commit.
    CLANG_FILES=""
    for CLANG_FILE in ${CHANGED_CLANG_FILES}; do
      if [[ -f "${CLANG_FILE}" ]]; then
        CLANG_FILES="${CLANG_FILES} ${CLANG_FILE}"
      fi
    done

    echo "${CLANG_FILES}"
  else
    find benchmark recipe -name '*.h' -o -name '*.cc'
  fi
}

do_clang_format_check() {
  if [[ $# != "0" ]] && [[ $# != "1" ]]; then
    echo "Invalid syntax when invoking do_clang_format_check"
    echo "Usage: do_clang_format_check [--incremental]"
    return 1
  fi

  local clang_src_files

  if [[ "$1" == "--incremental" ]]; then
    clang_src_files=$(get_clang_files_to_check --incremental)

    if [[ -z "${clang_src_files}" ]]; then
      echo "do_clang_format_check will NOT run due to --incremental flag and "\
"due to the absence of .h or .cc code changes in the last commit."
      return 0
    fi
  elif [[ -z "$1" ]]; then
    clang_src_files=$(get_clang_files_to_check)
  else
    echo "Invalid syntax for invoking do_clang_format_check"
    echo "Usage: do_clang_format_check [--incremental]"
    return 1
  fi

  CLANG_FORMAT=${CLANG_FORMAT:-clang-format}

  local success=1
  for filename in $clang_src_files; do
    local diff=$($CLANG_FORMAT $filename | diff $filename -)
    if [[ "$diff" != "" ]]; then
      success=0
      echo File $filename is not properly formatted with "clang-format"
    fi
  done

  if [[ $success == 0 ]]; then
    echo Clang format check fails.
    exit 1
  fi
  echo Clang format check success.
}

while [ $# -gt 0 ];
do
  case ${1} in
    --skip-clang-format|-c)
      shift || true  # in case of set -e
      skip_clang_format=1
    ;;

    *)
      echo "[ERROR] Invalid option '${1}'"
      exit 1
    ;;
  esac
  shift || true  # in case of set -e
done

do_buildifier

echo ""

if [[ -z ${skip_clang_format} ]]; then
  do_clang_format_check
fi
