#!/bin/bash

set -e
set -o pipefail
set -x

usage() {
  cat <<EOF
deployment.sh is a tool for generated documents.
Usage:
    deployment.sh <path-to-repository>
Environment variables:
- TRAVIS_PULL_REQUEST
- TRAVIS_BRANCH
- TRAVIS_COMMIT
- RECIPE_DOCS_DEPLOY_KEY
EOF
}

#
# validate arugments
#
path_to_repository=$1
if [[ -z ${path_to_repository} ]]; then
  usage
  exit 1
fi

# mafipy/master
test_branch="master"
# mafipy_benchmarks/master
target_branch="master"
# origin/master of mafipy_benchmarks
target_repository="origin"

# Generate documents
${path_to_repository}/tools/docker/sphinx/docker_run_generate_docs.sh

# Pull requests and commits to other branches shouldn't try to deploy, just build to verify
if [[ "$TRAVIS_PULL_REQUEST" != "false" -o "$TRAVIS_BRANCH" != "$test_branch" ]]; then
  echo "Skipping deploy; just doing a build."
  exit 0
fi

# Save some useful information from original repository
commit_sha1="$TRAVIS_COMMIT"

# move to submodule
cd ${path_to_repository}/docs/_build/
git config user.name "numerical_recipe"
git config user.email "numerical_recipe@example.com"

# If there are no changes (e.g. this is a README update) then just bail.
if [[ -z `git diff --exit-code` ]]; then
  echo "No changes to the spec on this push; exiting."
  exit 0
fi

# push benchmark results to mafipy_benchmarks
git remote set-url origin git@github.com:i05nagai/numerical_recipe_docs.git
git add .
git commit -m "Deploy to GitHub Pages: ${commit_sha1}"

# Force to hide the credential
set +x
ssh-agent bash -c "
  echo \"${RECIPE_DOCS_DEPLOY_KEY}\" | base64 -d | ssh-add -
  GIT_SSH_COMMAND='ssh -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no' git push $target_repository $target_branch
"
