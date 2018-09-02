#!/bin/bash

set -e

if [[ "$TRAVIS_OS_NAME" == "osx" ]]; then
  brew cask install homebrew/cask-versions/java8
  brew install bazel
fi

if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
  sudo apt-get install -y --force-yes openjdk-8-jdk
  sudo add-apt-repository -y ppa:webupd8team/java
  sudo apt-get update
  sudo apt-get install -y oracle-java8-installer
  echo "deb [arch=amd64] http://storage.googleapis.com/bazel-apt stable jdk1.8" | sudo tee /etc/apt/sources.list.d/bazel.list
  curl https://bazel.build/bazel-release.pub.gpg | sudo apt-key add -
  sudo apt-get update
  sudo apt-get install -y bazel
fi
