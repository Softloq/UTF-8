# Contributing

Thanks for your interest in improving Softloq UTF-8. This document explains how to propose changes.

## Required Reading

Before opening a contribution, please read:

* the root [`README.md`](README.md);
* the generated documentation in [`docs/`](docs/), if you've built it; and
* the existing tests in [`tests/`](tests/) and examples in [`examples/`](examples/), to see established patterns.

## Code Philosophy

* **Let the code speak for itself.** Names and structure should make intent obvious. Comments and documentation are reserved for the genuinely complex; don't restate what a well-named function or variable already says.
* **Braces, always.** Every `if`, `else`, `for`, `while`, and `do` body uses `{ }`, even for a single statement.
* **Prefer one line when it fits.** A short function or conditional that reads cleanly on one line should be written that way. Longer, multi-step logic should be broken up with blank lines between distinct steps rather than crammed together.
* **Naming conventions:**
  * Classes: `PascalCase`.
  * Functions and methods: `snake_case`.
  * Namespaces: `snake_case`, structured as `organization::repository::path`.
  * Files (headers and sources): `kebab-case`, matching the primary class they declare.
* **Header guards** are named (`#pragma once` is not used), built from the organization, repository, and file path in `SCREAMING_SNAKE_CASE`.
* **Error handling:**
  * Programming errors (broken invariants, impossible states) use `assert`/`static_assert` and fail loudly in Debug/Devel builds.
  * Runtime errors (invalid input, anything that can legitimately fail) are represented with `std::expected<Value, Error>`, never exceptions or silent failure.
* **Modern C++23:** attributes like `[[nodiscard]]` come first in a declaration, ahead of `static`/`virtual`/`inline`, which in turn come ahead of the library's export macro.

## Test-Driven Development

This project follows a **Red-Green-Refactor-Documentation** cycle:

1. **Red:** Write a failing test in `tests/` that describes the desired behavior.
2. **Green:** Write the minimum library code needed to make that test pass.
3. **Refactor:** Clean up the implementation while keeping every test passing.
4. **Documentation:** Update the relevant README, inline documentation, or `.dox` files in the same change.

No production logic should be added without a test that already exercises it. Tests use GoogleTest v1.17.0, fetched automatically by CMake — see [`tests/README.md`](tests/README.md).

## Opening a Contribution

Every contribution should identify, upfront, which of the following it addresses:

* a functional bug;
* an optimization or performance issue;
* a security concern;
* a readability or maintainability problem; or
* another clearly articulated problem with the project.

Along with the problem, state your **proposed solution**.

If you've spotted a problem but don't yet have a solution in mind, please [open an issue](https://github.com/Softloq/UTF-8/issues) describing it instead of opening a pull request. Pull requests that don't clearly state both a problem and a solution will be asked to become an issue first.

## AI-Assisted Contributions

Contributions written or refined with the help of an AI coding assistant are welcome. They're held to the exact same bar as any other contribution: they must solve a real, clearly articulated problem per the section above. How a contribution was written isn't a factor in whether it's accepted.
