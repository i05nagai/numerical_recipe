package(default_visibility = ["//visibility:public"])

cc_library(
    name = "linear_algebra",
    srcs = glob(
        ["*.cc"],
        exclude = ["*_test.cc"],
    ),
    hdrs = glob(["**/*.h"]),
    copts = [
        "-std=c++11",
    ],
    deps = [
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
        ":linear_algebra",
        "//numrecipe/test_util",
        "@gtest",
    ],
)
