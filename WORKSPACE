#
# from bazel 0.20.0, the following rules are deprecated,
# so explicit load is required
#
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "new_git_repository")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

#
# gflags
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
    build_file = "//third_party/glog:BUILD",
    remote = "https://github.com/google/glog.git",
    tag = "v0.3.5",
)

#
# gtest
# bazel build @gtest//:gtest
# Since 1.8.1, gtest contains BUILD.bazel in the archive
#
http_archive( name = "gtest", url = "https://github.com/abseil/googletest/archive/release-1.8.0.zip",
    strip_prefix = "googletest-release-1.8.0/googletest",
    build_file = "//third_party/gtest:BUILD",
)

#
# google/benchmark
# bazel build @benchmark//:benchmark
#
http_archive(
    name = "benchmark",
    build_file = "//third_party/benchmark:BUILD",
    sha256 = "f8e525db3c42efc9c7f3bc5176a8fa893a9a9920bbd08cef30fb56a51854d60d",
    strip_prefix = "benchmark-1.4.1",
    urls = [
        "https://github.com/google/benchmark/archive/v1.4.1.tar.gz",
    ],
)

#
# eigen
# bazel build @eigen3//:eigen3
#
http_archive(
    name = "eigen3",
    build_file = "//third_party/eigen3:BUILD",
    sha256 = "aae7a680d141c978301dfae2c7945c06039f65849fcf64269595a9cdbba82638",
    strip_prefix = "eigen-eigen-729d33d11c81",
    urls = [
        "https://mirror.bazel.build/bitbucket.org/eigen/eigen/get/729d33d11c81.tar.gz",
        "https://bitbucket.org/eigen/eigen/get/729d33d11c81.tar.gz",
    ],
)
