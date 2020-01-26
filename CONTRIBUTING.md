## Build
To build the library, you need to run

```
bazel build //numrecipe/...
```

You can build only specific sub packages

```
bazel build //numrecipe/integrate:integrate
bazel build //numrecipe/sandbox:sandbox
bazel build //numrecipe/util:util
```

Debug build

```
bazel build //numrecipe --compilation_mode=dbg
```

## Test
We use gtest for testing. Take a look at official documents:

* [Google test primer](https://github.com/google/googletest/blob/master/googletest/docs/primer.md)
* [Gtest advanced document](https://github.com/google/googletest/blob/master/googletest/docs/advanced.md)

You can run all tests with command

```
bazel test --test_output=errors "//numrecipe/..."
```

Executing tests for specific subpackages is also possible

```
bazel test --test_output=errors //numrecipe/quadrature:test
bazel test --test_output=errors //numrecipe/sandbox:test
bazel test --test_output=errors //numrecipe/util:test
```

## Documentation
To generate documetns, run the following command:

```
./tools/docker/sphinx/docker_run_generate_docs.sh
```

The documents are generated under `docs/_build/`.
To see the documents, you need to open `docs/_build/index.html` with your browser.

## Benchmark
Run benchmarks with debug build options

```
bazel run --compilation_mode=dbg "//benchmark/..."
```

Run benchmarks with optimized(release) build options

```
bazel run --compilation_mode=opt "//benchmark/..."
```

If you want to run all benchmarks,

```
./tools/run_benchmark.sh
```

## Formatter/Linter
We follow [Google C\+\+ Style Guide](https://google.github.io/styleguide/cppguide.html).

### C++
We use `clang-format` for formatting code.
Make sure `clang-format` is installed.

For OSX, you can install the following command:

```
brew install clang-format
```

For ubuntu 16.04,

```
apt-get install -y clang-tidy
```

You can check a C/C++ file by doing:

```
clang-format <my_cc_file> --style=google > /tmp/my_cc_file.cc
diff <my_cc_file> /tmp/my_cc_file.cc
```

To format all of code in the repository, you can run the script on the root of the repository by executing the command:

```
# Build docker images for formatter. Behaviour of formatter depends on the version of formatter.
./tools/docker/gcc/docker_build_ubuntu1604.sh
# Run formatter with docker images
./tools/docker_run_formatter.sh
```

### bazel
For OSX,

```
brew install buildifier
```

Check whether format error exists or not

```
buildifier -showlog -mode=check $(find . -type f -name BUILD -or -name 'BUILD.*' -or -name BUILD.bazel)
```

Fix format error in-place

```
buildifier -showlog -mode=fix $(find . -type f -name BUILD -or -name 'BUILD.*' -or -name BUILD.bazel)
```

## Logging
We use [google/glog](https://github.com/google/glog) for logging. See [documentation](http://rpg.ifi.uzh.ch/docs/glog.html).
The log message will be logged to `/tmp/<program name>.<hostname>.<user name>.log.<severity level>.<date>.<time>.<pid>`. (e.g., "/tmp/hello_world.example.com.hamaji.log.INFO.20080709-222411.10474")

## Debugging
We support the `gcc` compiler and `clang` compiler now so that we run all tests with both compilers in CI environments.
Running multiple compilers in the same machine is sometimes annoying developers because of their dependency.
For debugging in another compiler, we provide docker images.
See `tools/docker/gcc` for the GCC compiler.

## Coverage
You need to install `gcov` and `lcov` to measure test coverages.
We recommend to use the docker image.

```
./tools/docker/gcc/docker_build_ubuntu1604.sh
./tools/docker/gcc/docker_run_ubuntu1604.sh
bazel coverage //numrecipe/... --compilation_mode=dbg
```

There is no visualization of the result of the test coverage for now.

## TODO

* [x] lint
    * [x] C++ format check
        * [ClangFormat — Clang 8 documentation](https://clang.llvm.org/docs/ClangFormat.html)
        * Using clnag-fromat version 5.0
    * [x] bazel format check
        * [buildtools/buildifier at master · bazelbuild/buildtools](https://github.com/bazelbuild/buildtools/tree/master/buildifier)
* build with cmake
    * [ ] library
    * [ ] examples
    * [ ] benchmarks
* build with bazel
    * [x] library
    * [x] examples
    * [x] benchmarks
* [x] run unit tests
    * [google/googletest: Google Test](https://github.com/google/googletest)
* [x] coverage report
    * coveralls
        * currently, codeclimate does not support C++ repository.
* [x] documentation
    * sphinx
* [x] API document
    * doxygen + sphinx + sphinx-breathe
* [x] benchmarking
    * [google/benchmark: A microbenchmark support library](https://github.com/google/benchmark)
* [ ] checking memory leak
    * Use valgrind
* [x] logging
    * [google/glog: C\+\+ implementation of the Google logging module](https://github.com/google/glog)
* [ ] packaging
* CI
    * Travis CI
        * [x] check code format
        * [x] build libary, examples and benchmarks
        * [ ] build examples
        * [x] run unittests
        * [x] notify to Slack
        * [x] push generated documents to 
    * [ ] Circle CI
* templates
    * [ ] issue templates
    * [ ] pull requests templates
