package(default_visibility = ["//visibility:public"])

cc_library(
    name = "integrate",
    srcs = glob(
        ["*.cc"],
        exclude = ["*_test.cc"],
    ),
    hdrs = glob(["*.h"]),
    copts = [
        "-std=c++11",
    ],
    deps = [
        "//recipe/util",
    ],
)

cc_test(
    name = "test",
    size = "medium",
    srcs = glob(["*_test.cc"]),
    copts = [
        "-Iexternal/gtest/include",
        "-std=c++11",
    ],
    deps = [
        ":integrate",
        "@gtest",
    ],
)
