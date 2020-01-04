package(default_visibility = ["//visibility:public"])

filegroup(
    name = "srcfile",
    srcs = glob([
        "*.cc",
        "*.h",
        ],
        exclude = ["*_test.cc"],
    ),
)

filegroup(
    name = "testfile",
    srcs = glob([
        "*_test.cc",
    ]),
)

cc_library(
    name = "quadrature",
    srcs = [
        ":srcfile"
    ],
    hdrs = glob(["*.h"]),
    copts = [
        "-std=c++11",
    ],
    deps = [
        "//numrecipe/core",
    ],
)

cc_test(
    name = "test",
    srcs = [
        ":testfile"
    ],
    copts = [
        "-Iexternal/gtest/include",
        "-std=c++11",
    ],
    deps = [
        ":quadrature",
        "//numrecipe/test_util",
        "@gtest",
    ],
)
