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

#
# swig
#
http_archive(
    name = "swig",
    build_file = "//third_party/swig:BUILD",
    sha256 = "58a475dbbd4a4d7075e5fe86d4e54c9edde39847cdb96a3053d87cb64a23a453",
    strip_prefix = "swig-3.0.8",
    urls = [
        "https://storage.googleapis.com/mirror.tensorflow.org/ufpr.dl.sourceforge.net/project/swig/swig/swig-3.0.8/swig-3.0.8.tar.gz",
        "http://ufpr.dl.sourceforge.net/project/swig/swig/swig-3.0.8/swig-3.0.8.tar.gz",
        "http://pilotfiber.dl.sourceforge.net/project/swig/swig/swig-3.0.8/swig-3.0.8.tar.gz",
    ],
)

#
# pcre
#
http_archive(
    name = "pcre",
    build_file = "//third_party/pcre:BUILD",
    sha256 = "69acbc2fbdefb955d42a4c606dfde800c2885711d2979e356c0636efde9ec3b5",
    strip_prefix = "pcre-8.42",
    urls = [
        "https://storage.googleapis.com/mirror.tensorflow.org/ftp.exim.org/pub/pcre/pcre-8.42.tar.gz",
        "http://ftp.exim.org/pub/pcre/pcre-8.42.tar.gz",
    ],
)

#
# python
#
load("//third_party/py:python_configure.bzl", "python_configure")
python_configure(name = "local_config_python")

#
# python dependnecies
#
# http_archive(
#     name = "rules_python",
#     url = "https://github.com/bazelbuild/rules_python/releases/download/0.0.1/rules_python-0.0.1.tar.gz",
#     sha256 = "aa96a691d3a8177f3215b14b0edc9641787abaaa30363a080165d06ab65e1161",
# )
git_repository(
    name = "rules_python",
    remote = "https://github.com/bazelbuild/rules_python.git",
    # NOT VALID: Replace with actual Git commit SHA.
    commit = "38f86fb55b698c51e8510c807489c9f4e047480e",
)
load("@rules_python//python:pip.bzl", "pip3_import")
pip3_import(
   name = "recipepy_deps",
   requirements = "//recipe/python:requirements.txt",
)
load("@recipepy_deps//:requirements.bzl", "pip_install")
pip_install()
