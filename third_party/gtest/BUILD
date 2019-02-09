# https://github.com/google/googletest

licenses([
    "notice",  # BSD 3-Clause "New" or "Revised" License
])

exports_files(["LICENSE"])

cc_library(
    name = "gtest",
    srcs = glob(
        [
            "src/*.cc",
            "src/*.h",
        ],
        exclude = ["src/gtest-all.cc"],
    ),
    hdrs = glob([
        "include/**/*.h",
        "**/*.h",
    ]),
    copts = [
        "-Iexternal/gtest/include",
        "-Iexternal/gtest",
    ],
    linkopts = ["-pthread"],
    visibility = ["//visibility:public"],
)
