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
        "//recipe/core",
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
        "//recipe/test_util",
        "@gtest",
    ],
)
