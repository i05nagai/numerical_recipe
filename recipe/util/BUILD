package(default_visibility = ["//visibility:public"])

cc_library(
    name = "util",
    srcs = glob(
        ["*.cc"],
        exclude = ["*_test.cc"],
    ),
    hdrs = glob(["*.h"]),
    copts = [
        "-std=c++11",
    ],
    deps = [
        "@glog",
    ],
)

cc_test(
    name = "test",
    srcs = glob(["*_test.cc"]),
    copts = [
        "-Iexternal/gtest/include",
        "-std=c++11",
    ],
    deps = [
        ":util",
        "@gtest",
    ],
)
