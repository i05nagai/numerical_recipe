package(default_visibility = ["//visibility:public"])

cc_library(
    name = "vector",
    srcs = ["vector.cc"],
    hdrs = ["vector.h"],
    copts = [
        "-std=c++11",
    ],
)

cc_library(
    name = "matrix",
    srcs = ["matrix.cc"],
    hdrs = ["matrix.h"],
    copts = [
        "-std=c++11",
    ],
)

cc_library(
    name = "lu_decomposition",
    srcs = ["lu_decomposition.cc"],
    hdrs = ["lu_decomposition.h"],
    deps = [
        ":vector",
        ":matrix",
        "@glog",
    ],
    copts = [
        "-std=c++11",
    ],
)

cc_test(
    name = "vector_test",
    srcs = ["vector_test.cc"],
    copts = [
        "-Iexternal/gtest/include",
        "-std=c++11",
    ],
    deps = [
        ":vector",
        "@gtest",
    ],
)

cc_test(
    name = "matrix_test",
    srcs = ["matrix_test.cc"],
    copts = [
        "-Iexternal/gtest/include",
        "-std=c++11",
    ],
    deps = [
        ":matrix",
        "@gtest",
    ],
)

cc_test(
    name = "lu_decomposition_test",
    srcs = ["lu_decomposition_test.cc"],
    copts = [
        "-Iexternal/gtest/include",
        "-std=c++11",
    ],
    deps = [
        ":lu_decomposition",
        "@gtest",
    ],
)
