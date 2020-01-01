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

cc_library(
    name = "core",
    srcs = [":srcfile"],
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
        "//numrecipe/test_util",
        "@gtest",
    ],
)
