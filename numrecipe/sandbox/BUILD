package(default_visibility = ["//visibility:public"])

cc_library(
    name = "sandbox",
    srcs = glob(
        ["*.cc"],
        exclude = ["*_test.cc"],
    ),
    hdrs = glob(["*.h"]),
    copts = [
        "-std=c++11",
        "-Iexternal/eigen3",
    ],
    deps = [
        "@eigen3",
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
        ":sandbox",
        "@gtest",
    ],
)
