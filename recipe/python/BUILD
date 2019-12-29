package(default_visibility = ["//visibility:public"])

load(":recipe.bzl", "py_wrap_cc")
load("@recipepy_deps//:requirements.bzl", "requirement")

py_wrap_cc(
    name = "pywrap_recipe",
    srcs = ["pywrap_recipe.i"],
    swig_includes = [
        "core/core_wrap.i",
        "quadrature/quadrature_wrap.i",
    ],
    deps = [
        "//third_party/python_runtime:headers",
        "//recipe/core",
        "//recipe/quadrature",
    ],
    copts = [],
)

py_library(
    name = "recipepy",
    srcs = glob([
        "__init__.py",
        "core/**/*.py",
        "quadrature/**/*.py",
    ]),
    srcs_version = "PY3",
    deps = [
        ":pywrap_recipe",
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
        ":pywrap_recipe",
        ":recipepy",
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
