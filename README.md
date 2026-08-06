# Softloq UTF-8

**Developer:** Brandon Foster ([@BrandonFoster](https://github.com/BrandonFoster))
**Organization:** [Softloq](https://github.com/Softloq)

## License

Softloq UTF-8 is released under the [MIT License](LICENSE) — a permissive open-source license. You're free to use, modify, and redistribute this project, including in commercial and proprietary software, as long as the original copyright notice is preserved.

The current version is **v1.0.0** — see its [changelog](changelogs/v1.0.0/CHANGELOG.md) for what it includes.

[Jump to Build Options](#build-options)

## Contributing

Found a bug, or have an improvement in mind? Contributions are welcome if you feel like making one — see [CONTRIBUTING.md](CONTRIBUTING.md) for how to get started.

## Purpose

Softloq UTF-8 is a modern C++23 library for encoding and decoding UTF-8 text. It validates raw bytes and Unicode code points against the rules defined by the Unicode Standard, and exposes small, composable types (`Octet`, `OctetSequence`, `Char`) along with a `decode()`/`encode()` facade for converting between raw UTF-8 bytes and validated code points.

Working with UTF-8 correctly is easy to get subtly wrong — overlong encodings, unpaired surrogates, truncated sequences, and out-of-range code points can all silently corrupt data or introduce security issues if unvalidated bytes are trusted. Softloq UTF-8 addresses this by requiring every byte and code point to pass explicit validation before it can be used, with failures represented as recoverable `std::expected` results instead of being left to slip through unnoticed.

## Documentation

Generated API reference documentation is available once built — see [docs/README.md](docs/README.md) for how to generate and browse it.

## Examples

The [examples/](examples/) directory contains runnable programs demonstrating the public API, such as decoding a multi-octet UTF-8 sequence and encoding a code point back into bytes. See [examples/README.md](examples/README.md) for the full list of examples and more comprehensive example applications.

## Testing

The [tests/](tests/) directory contains the GoogleTest suite covering `Octet`, `OctetSequence`, `Char`, and the `decode()`/`encode()` facade. See [tests/README.md](tests/README.md) for more comprehensive test case analysis.

## Build Options

Softloq UTF-8 requires **CMake 3.16+** and a **C++23** compiler.

For a single-configuration generator:

```sh
# Debug
cmake -S . -B build/debug -DCMAKE_BUILD_TYPE=Debug
cmake --build build/debug

# Devel
cmake -S . -B build/devel -DCMAKE_BUILD_TYPE=Devel
cmake --build build/devel

# Release
cmake -S . -B build/release -DCMAKE_BUILD_TYPE=Release
cmake --build build/release
```

For a multi-configuration generator (e.g. Visual Studio):

```sh
cmake -S . -B build
cmake --build build --config Debug
cmake --build build --config Devel
cmake --build build --config Release
```

**Optional flags:**

| Flag | Effect |
|---|---|
| `SOFTLOQ_UTF_8_BUILD_STATIC` | Build a static library instead of the default shared library. |
| `SOFTLOQ_UTF_8_BUILD_TESTING` | Build the test suite (see [Testing](#testing)). |
| `SOFTLOQ_UTF_8_BUILD_EXAMPLES` | Build the example applications (see [Examples](#examples)). |
| `SOFTLOQ_UTF_8_BUILD_DOCS` | Build the generated documentation (see [Documentation](#documentation)). |

Pass any of these as `-D<FLAG>=ON` during configuration.

### Consuming the Library

Add this repository as a subdirectory of your own CMake project and link against the `Softloq::UTF-8` target:

```cmake
add_subdirectory(path/to/softloq-utf-8)
target_link_libraries(consumer PRIVATE Softloq::UTF-8)
```

```cpp
#include "softloq/utf-8/utf-8.hpp"
```

If you consume the default shared build (i.e. `SOFTLOQ_UTF_8_BUILD_STATIC` is `OFF`), define `SOFTLOQ_UTF_8_IMPORTS` when compiling your own sources against the library's headers:

```cmake
target_compile_definitions(consumer PRIVATE SOFTLOQ_UTF_8_IMPORTS)
```

## References

* [RFC 3629 — UTF-8, a transformation format of ISO 10646](https://www.rfc-editor.org/rfc/rfc3629)
* [The Unicode Standard](https://www.unicode.org/versions/latest/)

## Solving the Problem

UTF-8's variable-length encoding means a "byte" and a "character" are not the same thing, and a naive implementation that just reads bytes without validating them can accept malformed input — overlong encodings, lone continuation bytes, or code points reserved for UTF-16 surrogate pairs — that a spec-compliant decoder must reject.

Softloq UTF-8 addresses this by splitting the problem into small, independently-validated layers instead of one large decoding routine:

* `Octet` rejects byte values that can never legally appear in UTF-8 the moment they're constructed.
* `OctetSequence` rejects a lead octet paired with the wrong number of trailing octets before those bytes are ever interpreted as a code point.
* `Char` rejects code points outside the Unicode range or inside the UTF-16 surrogate range, whether they arrive as a raw code point or as a decoded octet sequence.

Because every layer returns `std::expected<Value, Error>` instead of throwing or silently clamping invalid input, callers are forced to explicitly handle malformed data at the point where it's detected, rather than propagating corrupted text further into a program.
