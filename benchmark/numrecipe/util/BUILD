cc_binary(
    name = "util",
    srcs = glob([
        "*.cc",
        "*.h",
    ]),
    copts = [
        "-std=c++11",
    ],
    linkstatic = 1,
    deps = [
        "//numrecipe/util",
        "@benchmark",
    ],
)
