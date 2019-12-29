package(default_visibility = ["//visibility:private"])

load("//:recipe.bzl", "transitive_hdrs")

transitive_hdrs(
    name = "included_headers",
    deps = [
        "//recipe/core",
        "//recipe/quadrature",
        "//recipe/util",
        "@eigen3",
    ],
)

COMMON_PIP_DEPS = [
    "MANIFEST.in",
    "README.md",
    "setup.py",
    ":included_headers",
    "//recipe/python:recipepy",
]

sh_binary(
    name = "build_pip_package",
    srcs = ["build_pip_package.sh"],
    data = COMMON_PIP_DEPS
)
