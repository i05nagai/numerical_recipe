## Build
To build the library, you need to run

```
bazel build //recipe/...
```

You can build only specific sub packages

```
bazel build //recipe/integrate:integrate
bazel build //recipe/sandbox:sandbox
bazel build //recipe/util:util
```

Debug build

```
bazel build //recipe --compilation_mode=dbg
```

## Test
We use gtest for testing. Take a look at official documents:

* [Google test primer](https://github.com/google/googletest/blob/master/googletest/docs/primer.md)
* [Gtest advanced document](https://github.com/google/googletest/blob/master/googletest/docs/advanced.md)

You can run all tests with command

```
bazel test "//recipe/..."
```

Executing tests for specific subpackages is also possible

```
bazel test //recipe/integrate:test
bazel build //recipe/sandbox:sandbox
bazel test //recipe/util:test
```

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
./tools/formatter.sh
```

### bazel
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

## TODO

* [x] lint
    * [x] C++ format check
        * [ClangFormat — Clang 8 documentation](https://clang.llvm.org/docs/ClangFormat.html)
    * [x] bazel format check
        * [buildtools/buildifier at master · bazelbuild/buildtools](https://github.com/bazelbuild/buildtools/tree/master/buildifier)
* build with cmake
    * [ ] library
    * [ ] examples
    * [ ] benchmarks
* build with bazel
    * [x] library
    * [ ] examples
    * [ ] benchmarks
* [x] run unit tests
    * [google/googletest: Google Test](https://github.com/google/googletest)
* [ ] coverage report
    * coveralls/codecov
* [ ] documentation
    * sphinx
* [ ] API document
    * doxygen + sphinx
* [x] benchmarking
    * [google/benchmark: A microbenchmark support library](https://github.com/google/benchmark)
* [ ] checking memory leak
    * valgrind
* [x] logging
    * [google/glog: C\+\+ implementation of the Google logging module](https://github.com/google/glog)
* [ ] packaging
* CI
    * Travis CI
        * [x] check code format
        * [x] build libary, examples and benchmarks
        * [x] run unittests
        * [x] notify to Slack
    * [ ] Circle CI
* templates
    * [ ] issue templates
    * [ ] pull requests templates
