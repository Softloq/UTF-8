# v1.0.0

Initial release of Softloq UTF-8.

## Added

### `Octet`
A single validated UTF-8 byte.
- `create(value)` — validates a raw byte, rejecting values that can never legally appear in UTF-8 (`0xC0`, `0xC1`, `0xF5`-`0xFF`).
- `get_value()` / implicit `operator std::uint8_t()` — access the underlying byte value.
- `operator<=>` — orders octets by their byte value.

### `OctetSequence`
The 1-4 octets that together encode a single Unicode code point.
- `create(...)` (1, 2, 3, and 4-octet overloads) — validates that the lead octet's declared length matches the number of octets provided.
- `at(index)` — bounds-checked access to an individual octet.
- `get_length()` — the sequence's octet count.
- `is_bom()` — detects the UTF-8 byte order mark encoding (`EF BB BF`).
- `is_word_joiner()` — detects the sequence's recognized word-joining control character encoding.
- `operator<=>` — orders sequences by length, then octet-by-octet.
- `get_octet_sequence_length(first_octet)` — free function reporting the octet count a lead octet declares.

### `Char`
A single validated Unicode code point.
- `create(sequence)` — decodes a validated `OctetSequence` into its represented code point.
- `create(code_point)` — validates a raw code point, rejecting the UTF-16 surrogate range (`U+D800`-`U+DFFF`) and anything beyond `U+10FFFF`.
- `get_code_point()` / implicit `operator std::uint32_t()` — access the underlying code point.
- `to_octet_sequence()` — encodes the code point back into its UTF-8 byte representation.
- `is_bom()` — detects the byte order mark code point (`U+FEFF`).
- `is_word_joiner()` — detects the code point `U+2060`.
- `operator<=>` — orders characters by code point.

### `Error`
A recoverable failure returned via `std::expected` from every fallible operation above.
- `Code` — a stable enum identifying the failure category (invalid char, octet, octet sequence, sequence length, sequence index, or empty encoding input).
- `create_invalid_char_error`, `create_invalid_octet_error`, `create_invalid_octet_sequence_error`, `create_invalid_octet_sequence_length_error`, `create_invalid_octet_sequence_index_error`, `create_encoding_empty_char_sequence_error` — factory functions for each failure category.
- `get_code()` / `get_message()` — access the failure's category and a human-readable message.

### `decode()` / `encode()` facade
- `decode(sequence)` — decodes an already-validated `OctetSequence` into a `Char`.
- `decode(string_view)` / `decode(const char*)` — decodes the leading UTF-8 character out of raw bytes, validating as it goes.
- `encode(character)` — encodes an already-validated `Char` into an `OctetSequence`.
- `encode(code_point)` — validates a raw code point and encodes it into an `OctetSequence`.

### Project Infrastructure
- Shared/static CMake library build (`SOFTLOQ_UTF_8_BUILD_STATIC`), with export/import macro handling on Windows and hidden-by-default symbol visibility on GCC/Clang.
- GoogleTest-based test suite (`SOFTLOQ_UTF_8_BUILD_TESTING`).
- Example applications demonstrating the public API (`SOFTLOQ_UTF_8_BUILD_EXAMPLES`).
- Doxygen-generated API documentation (`SOFTLOQ_UTF_8_BUILD_DOCS`).

## Removed
None — this is the initial release.
