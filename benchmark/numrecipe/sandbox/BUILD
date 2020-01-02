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
    linkopts = [
        "-pthread",
    ],
    deps = [
        "//numrecipe/sandbox",
        "@benchmark",
    ],
)
