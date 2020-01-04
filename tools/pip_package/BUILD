package(default_visibility = ["//visibility:private"])

load("//:numrecipe.bzl", "transitive_hdrs")

transitive_hdrs(
    name = "included_headers",
    deps = [
        "//numrecipe/core",
        "//numrecipe/quadrature",
        "//numrecipe/util",
        "@eigen3",
    ],
)

COMMON_PIP_DEPS = [
    "MANIFEST.in",
    "README.md",
    "setup.py",
    ":included_headers",
    "//numrecipe/python:numrecipepy",
]

sh_binary(
    name = "build_pip_package",
    srcs = ["build_pip_package.sh"],
    data = COMMON_PIP_DEPS
)
