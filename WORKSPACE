#
# glog
#
git_repository(
    name   = "com_github_gflags_gflags",
    commit = "f8a0efe03aa69b3336d8e228b37d4ccb17324b88",
    remote = "https://github.com/gflags/gflags.git",
)
# the glog files.
# bazel build @glog//:glog
new_git_repository(
    name   = "glog",
    build_file = "//ci/bazel:BUILD.glog",
    remote = "https://github.com/google/glog.git",
    tag = "v0.3.5",
)

#
# gtest
# bazel build @gtest//:gtest
#
new_http_archive(
    name = "gtest",
    url = "https://github.com/google/googletest/archive/release-1.8.0.zip",
    build_file = "//ci/bazel:BUILD.gtest",
    strip_prefix = "googletest-release-1.8.0/googletest",
)

#
# google/benchmark
#
new_http_archive(
    name = "benchmark",
    build_file = "//ci/bazel:BUILD.benchmark",
    sha256 = "f8e525db3c42efc9c7f3bc5176a8fa893a9a9920bbd08cef30fb56a51854d60d",
    strip_prefix = "benchmark-1.4.1",
    urls = [
        "https://github.com/google/benchmark/archive/v1.4.1.tar.gz",
    ],
)
