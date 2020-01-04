# Shared libraries have different name pattern on different platforms,
# but cc_binary cannot output correct artifact name yet,
# so we generate multiple cc_binary targets with all name patterns when necessary.
SHARED_LIBRARY_NAME_PATTERNS = [
    "lib%s.so%s",  # On Linux, shared libraries are usually named as libfoo.so
    "lib%s%s.dylib",  # On macos, shared libraries are usually named as libfoo.dylib
    "%s%s.dll",  # On Windows, shared libraries are usually named as foo.dll
]


def cc_shared_object(
        name,
        srcs = [],
        deps = [],
        data = [],
        linkopts = [],
        framework_so = [],
        soversion = None,
        kernels = [],
        per_os_targets = False,  # Generate targets with SHARED_LIBRARY_NAME_PATTERNS
        visibility = None,
        **kwargs):
    """Configure the shared object (.so) file for TensorFlow."""
    if soversion != None:
        suffix = "." + str(soversion).split(".")[0]
        longsuffix = "." + str(soversion)
    else:
        suffix = ""
        longsuffix = ""

    if per_os_targets:
        names = [
            (
                pattern % (name, ""),
                pattern % (name, suffix),
                pattern % (name, longsuffix),
            )
            for pattern in SHARED_LIBRARY_NAME_PATTERNS
        ]
    else:
        names = [(
            name,
            name + suffix,
            name + longsuffix,
        )]

    for name_os, name_os_major, name_os_full in names:
        # Windows DLLs cant be versioned
        if name_os.endswith(".dll"):
            name_os_major = name_os
            name_os_full = name_os

        if name_os != name_os_major:
            native.genrule(
                name = name_os + "_sym",
                outs = [name_os],
                srcs = [name_os_major],
                output_to_bindir = 1,
                cmd = "ln -sf $$(basename $<) $@",
            )
            native.genrule(
                name = name_os_major + "_sym",
                outs = [name_os_major],
                srcs = [name_os_full],
                output_to_bindir = 1,
                cmd = "ln -sf $$(basename $<) $@",
            )

        soname = name_os_major.split("/")[-1]

        data_extra = []
        if framework_so != []:
            data_extra = []

        native.cc_binary(
            name = name_os_full,
            srcs = srcs + framework_so,
            deps = deps,
            linkshared = 1,
            data = data + data_extra,
            linkopts = linkopts,
            visibility = visibility,
            **kwargs
        )

    flat_names = [item for sublist in names for item in sublist]
    if name not in flat_names:
        native.filegroup(
            name = name,
            srcs = select({
                "//conditions:default": [":lib%s.so%s" % (name, longsuffix)],
            }),
            visibility = visibility,
        )


def _get_repository_roots(ctx, files):
    """Returns abnormal root directories under which files reside.
      When running a ctx.action, source files within the main repository are all
      relative to the current directory; however, files that are generated or exist
      in remote repositories will have their root directory be a subdirectory,
      e.g. bazel-out/local-fastbuild/genfiles/external/jpeg_archive. This function
      returns the set of these devious directories, ranked and sorted by popularity
      in order to hopefully minimize the number of I/O system calls within the
      compiler, because includes have quadratic complexity.
      """
    result = {}
    for f in files.to_list():
        root = f.root.path
        if root:
            if root not in result:
                result[root] = 0
            result[root] -= 1
        work = f.owner.workspace_root
        if work:
            if root:
                root += "/"
            root += work
        if root:
            if root not in result:
                result[root] = 0
            result[root] -= 1
    return [k for v, k in sorted([(v, k) for k, v in result.items()])]


def _get_transitive_headers(hdrs, deps):
    """Obtain the header files for a target and its transitive dependencies.
      Args:
        hdrs: a list of header files
        deps: a list of targets that are direct dependencies
      Returns:
        a collection of the transitive headers
      """
    return depset(
        hdrs,
        transitive = [dep[CcInfo].compilation_context.headers for dep in deps],
    )


# Bazel rules for building swig files.
def _py_wrap_cc_impl(ctx):
    srcs = ctx.files.srcs
    if len(srcs) != 1:
        fail("Exactly one SWIG source file label must be specified.", "srcs")
    module_name = ctx.attr.module_name
    src = ctx.files.srcs[0]
    inputs = _get_transitive_headers([src] + ctx.files.swig_includes, ctx.attr.deps)
    inputs = depset(ctx.files._swiglib, transitive = [inputs])
    inputs = depset(ctx.files.toolchain_deps, transitive = [inputs])
    swig_include_dirs = depset(_get_repository_roots(ctx, inputs))
    swig_include_dirs = depset(sorted([f.dirname for f in ctx.files._swiglib]), transitive = [swig_include_dirs])
    args = [
        "-c++",
        "-python",
        "-module",
        module_name,
        "-o",
        ctx.outputs.cc_out.path,
        "-outdir",
        ctx.outputs.py_out.dirname,
    ]
    args += ["-l" + f.path for f in ctx.files.swig_includes]
    args += ["-I" + i for i in swig_include_dirs.to_list()]
    args += [src.path]
    outputs = [ctx.outputs.cc_out, ctx.outputs.py_out]
    ctx.actions.run(
        executable = ctx.executable._swig,
        arguments = args,
        inputs = inputs.to_list(),
        outputs = outputs,
        mnemonic = "PythonSwig",
        progress_message = "SWIGing " + src.path,
    )
    return struct(files = depset(outputs))


_py_wrap_cc = rule(
    attrs = {
        "srcs": attr.label_list(
            mandatory = True,
            allow_files = True,
        ),
        "swig_includes": attr.label_list(
            allow_files = True,
        ),
        "deps": attr.label_list(
            allow_files = True,
            providers = [CcInfo],
        ),
        "toolchain_deps": attr.label_list(
            allow_files = True,
        ),
        "module_name": attr.string(mandatory = True),
        "py_module_name": attr.string(mandatory = True),
        "_swig": attr.label(
            default = Label("@swig//:swig"),
            executable = True,
            cfg = "host",
        ),
        "_swiglib": attr.label(
            default = Label("@swig//:templates"),
            allow_files = True,
        ),
    },
    outputs = {
        "cc_out": "%{module_name}.cc",
        "py_out": "%{py_module_name}.py",
    },
    implementation = _py_wrap_cc_impl,
)


def py_wrap_cc(
        name,
        srcs,
        swig_includes = [],
        deps = [],
        copts = [],
        **kwargs):
    """Builds a Python extension module."""
    module_name = name
    cc_library_base = "_" + module_name

    # shouldn't be passing a name qualified with .so here.
    cc_library_name = cc_library_base + ".so"
    cc_library_pyd_name = cc_library_base + ".pyd"
    extra_deps = []
    _py_wrap_cc(
        name = name + "_py_wrap",
        srcs = srcs,
        module_name = module_name,
        py_module_name = name,
        toolchain_deps = ["@bazel_tools//tools/cpp:current_cc_toolchain"],
        swig_includes = swig_includes,
        deps = deps + extra_deps,
    )

    cc_shared_object(
        name = cc_library_name,
        srcs = [module_name + ".cc"],
        copts = copts + [
            "-Wno-self-assign",
            "-Wno-sign-compare",
            "-Wno-write-strings",
        ],
        linkstatic = 1,
        deps = deps + extra_deps,
        **kwargs
    )

    # When a non-versioned .so is added as a 'src' to a bazel target, it uses
    # -l%(so_name) instead of -l:%(so_file) during linking.  When -l%(so_name)
    # is passed to ld, it will look for an associated file with the schema
    # lib%(so_name).so.  Since pywrap_tensorflow is not explicitly versioned
    # and is not prefixed with lib_, we add a rule for the creation of an .so
    # file with the canonical lib schema (e.g. libNAME.so), so that
    # -l%(so_name) is resolved during linking.
    #
    # See: https://github.com/bazelbuild/bazel/blob/7a6808260a733d50983c1adf0cf5a7493472267f/src/main/java/com/google/devtools/build/lib/rules/cpp/LibrariesToLinkCollector.java#L319
    for pattern in SHARED_LIBRARY_NAME_PATTERNS:
        name_os = pattern % (cc_library_base, "")
        native.genrule(
            name = name_os + "_rule",
            srcs = [":" + cc_library_name],
            outs = [name_os],
            cmd = "cp $< $@",
        )

    native.genrule(
        name = "gen_" + cc_library_pyd_name,
        srcs = [":" + cc_library_name],
        outs = [cc_library_pyd_name],
        cmd = "cp $< $@",
    )
    native.py_library(
        name = name,
        srcs = [":" + name + ".py"],
        srcs_version = "PY3ONLY",
        data = select({
            "//conditions:default": [":" + cc_library_name],
        }),
    )
