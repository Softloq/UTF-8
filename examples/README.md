# Examples

Example applications demonstrating the Softloq UTF-8 public API.

## decode-encode

**Purpose:** Decodes a known multi-octet UTF-8 byte sequence into a `Char`, then encodes a Unicode code point back into an `OctetSequence`, printing the results.

**Building:**

```sh
cmake -S . -B build/debug -DCMAKE_BUILD_TYPE=Debug -DSOFTLOQ_UTF_8_BUILD_EXAMPLES=ON
cmake --build build/debug
```

**Running:**

Run the resulting `softloq-utf-8-decode-encode` executable from `build/debug/output/` (or `build/debug/output/Debug/` on multi-configuration generators).

Expected output:

```
Decoded code point: U+20ac
Encoded byte count: 4
```
