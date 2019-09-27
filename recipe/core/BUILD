package(default_visibility = ["//visibility:public"])

cc_library(
    name = "core",
    srcs = glob(
        ["*.cc"],
        exclude = ["*_test.cc"],
    ),
    hdrs = glob(["*.h"]),
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
        ":core",
        "//recipe/test_util",
        "@gtest",
    ],
)
