#!/bin/bash

do_buildifier(){
  BUILD_FILES=$(find . -name 'BUILD*')
  NUM_BUILD_FILES=$(echo ${BUILD_FILES} | wc -w)

  echo "Running do_buildifier on ${NUM_BUILD_FILES} files"
  echo ""

  BUILDIFIER_START_TIME=$(date +'%s')
  BUILDIFIER_OUTPUT_FILE="$(mktemp)_buildifier_output.log"

  rm -rf ${BUILDIFIER_OUTPUT_FILE}

  buildifier -showlog -v -mode=check \
    ${BUILD_FILES} 2>&1 | tee ${BUILDIFIER_OUTPUT_FILE}
  BUILDIFIER_END_TIME=$(date +'%s')

  echo ""
  echo "buildifier took $((BUILDIFIER_END_TIME - BUILDIFIER_START_TIME)) s"
  echo ""

  if [[ -s ${BUILDIFIER_OUTPUT_FILE} ]]; then
    echo "FAIL: buildifier found errors and/or warnings in above BUILD files."
    echo "buildifier suggested the following changes:"
    buildifier -showlog -v -mode=diff ${BUILD_FILES}
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
    find recipe -name '*.h' -o -name '*.cc'
  fi
}

do_clang_format_check() {
  if [[ $# != "0" ]] && [[ $# != "1" ]]; then
    echo "Invalid syntax when invoking do_clang_format_check"
    echo "Usage: do_clang_format_check [--incremental]"
    return 1
  fi

  if [[ "$1" == "--incremental" ]]; then
    CLANG_SRC_FILES=$(get_clang_files_to_check --incremental)

    if [[ -z "${CLANG_SRC_FILES}" ]]; then
      echo "do_clang_format_check will NOT run due to --incremental flag and "\
"due to the absence of .h or .cc code changes in the last commit."
      return 0
    fi
  elif [[ -z "$1" ]]; then
    # TODO (yongtang): Always pass --incremental until all files have
    # been sanitized gradually. Then this --incremental could be removed.
    CLANG_SRC_FILES=$(get_clang_files_to_check --incremental)
  else
    echo "Invalid syntax for invoking do_clang_format_check"
    echo "Usage: do_clang_format_check [--incremental]"
    return 1
  fi

  CLANG_FORMAT=${CLANG_FORMAT:-clang-format}

  success=1
  for filename in $CLANG_SRC_FILES; do
    $CLANG_FORMAT --style=google $filename | diff $filename - > /dev/null
    if [ ! $? -eq 0 ]; then
      success=0
      echo File $filename is not properly formatted with "clang-format "\
"--style=google"
    fi
  done

  if [ $success == 0 ]; then
    echo Clang format check fails.
    exit 1
  fi
  echo Clang format check success.
}

do_buildifier
do_clang_format_check
