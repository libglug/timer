[![Build status](https://ci.appveyor.com/api/projects/status/ghixcg6sh3wtvsp4/branch/master?svg=true)](https://ci.appveyor.com/project/deewhiz/timer/branch/master)

# <a name="timer" />timer
TODO

# <a name="toc" />Table of Contents
* [glug_timer](#timer)
* [Table of Contents](#toc)
* [Usage](#usage)
* [Building](#building)
    * [Build Options](#buildoptions)
    * [Building Examples](#buildexamples)
    * [Development vs. Release Builds](#devvsrel)
* [Installation](#installation)
    * [Installing Examples](#installexamples)
    * [Installation Paths](#installpaths)
* [Tests](#tests)
    * [Running Specific Tests](#specifictests)

## <a name="usage" />Usage
TODO

## <a name="building" />Building
1. Install [Cmake](https://cmake.org/).
2. Fetch Dependencies
```
git submodule update --init --recursive
```
3. Start building
```
mkdir <build/dir> && cd <build/dir>
cmake [-G"<generator>"] <path/to/src>
cmake --build .
```

#### <a name="buildoptions" />Build Options
By default, the library is dynamic (.dll, .dylib, .so), but a static library can be generated (.lib, .a) by specifying `-DBUILD_STATIC=ON` during configuration.
```
cmake [-G"<generator>"] -DBUILD_STATIC=ON <path/to/src>
cmake -- build .
```

#### <a name="buildexamples" />Building Examples
Examples are only built when opted-in. The `examples` target will build all examples. Instead of builing all examples, individual example `targets` can be specified.
```
cmake [-G"<generator>"] <path/to/src>
cmake --build . --target [examples] [...targets]
```

#### <a name="devvsrel" />Development vs. Release Builds
Some generators don't use the `-DCMAKE_BUILD_TYPE=[build_type]` option during generation and therefore requires the `--config [build_type]` during build. I tend to use both just in case.
For example, to generate a release build, the release option should be added to the configure command and/or the config should be added to build command.
```
cmake [-G"<generator>"] -DCMAKE_BUILD_TYPE=[build_type] <path/to/src>
cmake --build . --config [build_type]
```

Available config types according to [CMake](https://cmake.org/cmake/help/latest/variable/CMAKE_BUILD_TYPE.html)
| Build Type              | CMake Option     |
|-------------------------|------------------|
| Debug                   | `DEBUG`          |
| Release with Debug Info | `RELWITHDEBINFO` |
| Release                 | `RELEASE`        |
| Minimum Size Release    | `MINSIZEREL`     |

## <a name="installation" />Installation
Installing will copy the files necessary to use the library (the headers for the library, as well as the library) to a chosen path.
```
cmake [-G"<generator>"] -DCMAKE_INSTALL_PREFIX:PATH=</path/to/install> <path/to/src>
cmake --build . --target install
```

#### <a name="installexamples" />Installing Examples
Since exammples are only built when opted in, they are installed through a separate install target: `install-examples`. It an be coupled with `install` to install all of the above as well as the example applications.
```
cmake [-G"<generator>"] -DCMAKE_INSTALL_PREFIX:PATH=</path/to/install> <path/to/src>
cmake --build . --target [install] install-examples
```

#### <a name="installpaths" /> Installation Paths
The installed components will be in the following directories

| Component | Install Path                 |
|-----------|------------------------------|
| Library   | `<path/to/install>/lib`      |
| Headers   | `<path/to/install>/include`  |
| Examples  | `<path/to/install>/examples` |

## <a name="tests" />Tests
Tests are run on [AppVeyor](https://www.appveyor.com/) and can be viewed [here](https://ci.appveyor.com/project/deewhiz/timer/branch/master).

They can be built and run locally by building the `check` target which builds all tests...
```
cmake [-G"<generator>"] <path/to/src>
cmake --build . --target check
```
... and then running them.
```
ctest -V
```
#### <a name="specifictests" />Running Specific Tests
Individual tests can be built if their `targets` are specified...
```
cmake [-G"<generator>"] <path/to/src>
cmake --build . --target <...targets>
```
... and running each test by specifying each tests `target` name.
```
ctest -R "<target1>[|target2[|target3[|...]]]"
```