/**
 * @file decode-encode.cpp
 * @author Brandon Foster (https://github.com/BrandonFoster)
 * @brief Demonstrates decoding a UTF-8 byte sequence and encoding a Unicode code point.
 *
 * Copyright (c) Softloq. All rights reserved.
 * Shows the minimal decode()/encode() facade usage a downstream consumer would perform.
 */

#include "softloq/utf-8/utf-8.hpp"

#include <iostream>
#include <string_view>

int main()
{
    const std::string_view euro_sign("\xE2\x82\xAC"); // UTF-8 for U+20AC '€'

    const auto decoded = softloq::utf_8::decode(euro_sign);
    if (!decoded) { std::cerr << "Failed to decode: " << decoded.error().get_message() << '\n'; return 1; }

    std::cout << "Decoded code point: U+" << std::hex << decoded->get_code_point() << '\n';

    const auto encoded = softloq::utf_8::encode(static_cast<std::uint32_t>(0x1F600)); // U+1F600 '\xF0\x9F\x98\x80'
    if (!encoded) { std::cerr << "Failed to encode: " << encoded.error().get_message() << '\n'; return 1; }

    std::cout << "Encoded byte count: " << std::dec << encoded->get_length() << '\n';

    return 0;
}
