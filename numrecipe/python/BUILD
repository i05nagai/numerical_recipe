package(default_visibility = ["//visibility:public"])

load(":numrecipe.bzl", "py_wrap_cc")
load("@numrecipepy_deps//:requirements.bzl", "requirement")

py_wrap_cc(
    name = "pywrap_numrecipe",
    srcs = ["pywrap_numrecipe.i"],
    swig_includes = [
        "core/core_wrap.i",
        "quadrature/quadrature_wrap.i",
    ],
    deps = [
        "//third_party/python_runtime:headers",
        "//numrecipe/core",
        "//numrecipe/quadrature",
    ],
    copts = [],
)

py_library(
    name = "numrecipepy",
    srcs = glob([
        "__init__.py",
        "core/**/*.py",
        "quadrature/**/*.py",
    ]),
    srcs_version = "PY3",
    deps = [
        ":pywrap_numrecipe",
    ],
)

py_test(
    name = "test",
    main = "run_pytest.py",
    srcs = glob([
        "run_pytest.py",
        "*_test.py",
    ]),
    python_version = "PY3",
    srcs_version = "PY3",
    data = [
        "pytest.ini",
    ],
    deps = [
        ":pywrap_numrecipe",
        ":numrecipepy",
        requirement("attrs"),
        requirement("atomicwrites"),
        requirement("importlib_metadata"),
        requirement("more_itertools"),
        requirement("packaging"),
        requirement("pluggy"),
        requirement("py"),
        requirement("pyparsing"),
        requirement("pytest"),
        requirement("six"),
        requirement("wcwidth"),
        requirement("zipp"),
    ],
)
