cc_binary(
    name = "sandbox",
    srcs = glob([
        "*.cc",
        "*.h",
    ]),
    copts = [
        "-std=c++11",
    ],
    linkstatic = 1,
    deps = [
        "//recipe/sandbox",
        "@benchmark",
    ],
)
