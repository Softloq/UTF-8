# Tests

This directory contains the test suite for the Softloq UTF-8 library.

All tests in this directory **must** follow the Test-Driven Development rules defined in the project's Test-Driven-Development specification. In particular:

* No production logic may be added to `src/` without a corresponding failing test in this directory existing first (Red), followed by the minimum implementation needed to pass it (Green) and any necessary cleanup (Refactor).
* Every change made here must be accompanied by an update to relevant documentation (README, inline documentation, or API specs) in the same change (Documentation).
* This suite uses **GoogleTest v1.17.0**, acquired automatically via CMake's `FetchContent` module — no manual GoogleTest installation is required.
* See the root [`CONTRIBUTING.md`](../CONTRIBUTING.md) for the full Red-Green-Refactor-Documentation cycle.

## Building

From the project root:

```sh
cmake -S . -B build/debug -DCMAKE_BUILD_TYPE=Debug -DSOFTLOQ_UTF_8_BUILD_TESTING=ON
cmake --build build/debug
```

## Running

```sh
ctest --test-dir build/debug --output-on-failure
```
