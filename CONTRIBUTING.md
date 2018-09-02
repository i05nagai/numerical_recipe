## Build
To build the library, you need to run

```
bazel build //recipe/integrate:integrate
bazel build //recipe/util:util
```

## Test
Run all tests

```
bazel test "//recipe/..."
```

```
bazel test //recipe/integrate:test
bazel test //recipe/util:test
```

## Formatter/Linter

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
buildifier -showlog -mode=check $(find . -type f \( -iname BUILD -or -iname BUILD.bazel \))
```

Fix format error in-place

```
buildifier -showlog -mode=fix $(find . -type f \( -iname BUILD -or -iname BUILD.bazel \))
```

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
* [ ] benchmarking
        * [google/benchmark: A microbenchmark support library](https://github.com/google/benchmark)
* [ ] checking memory leak
    * valgrind
* [ ] logging
    * [google/glog: C\+\+ implementation of the Google logging module](https://github.com/google/glog)
* [ ] packaging
* CI
    * Travis CI
        * [x] check code format
        * [x] build libary, examples and benchmarks
        * [x] run unittests
    * [ ] Circle CI
* templates
    * [ ] issue templates
    * [ ] pull requests templates
