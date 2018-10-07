cc_binary(
    name = "integrate",
    srcs = glob([
        "*.cc",
        "*.h",
    ]),
    copts = [
        "-std=c++11",
    ],
    linkstatic = 1,
    deps = [
        "//recipe/integrate",
        "@benchmark",
    ],
)
