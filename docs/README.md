# Documentation

Generated API reference for the Softloq UTF-8 library, built with [Doxygen](https://www.doxygen.nl/) from the `.dox` files in [`doxs/`](doxs/).

## Prerequisites

* [Doxygen](https://www.doxygen.nl/) (available on the `PATH` or discoverable by CMake's `find_package(Doxygen)`)
* [Graphviz](https://graphviz.org/) (optional, enables diagram generation)

## Generating

From the project root:

```sh
cmake -S . -B build/debug -DCMAKE_BUILD_TYPE=Debug -DSOFTLOQ_UTF_8_BUILD_DOCS=ON
cmake --build build/debug --target docs
```

Doxygen is configured to read only the `.dox` files under `doxs/`; it does not scan `include/` or `src/` directly.

## Output

The generated HTML site is written to [`html/index.html`](html/index.html).

## Cleaning

Delete the generated `html/` directory to reset to a clean state:

```sh
rm -rf docs/html
```
