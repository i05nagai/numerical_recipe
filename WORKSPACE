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
