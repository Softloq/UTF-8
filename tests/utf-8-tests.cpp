/**
 * @file utf-8-tests.cpp
 * @author Brandon Foster (https://github.com/BrandonFoster)
 * @brief GoogleTest cases covering the softloq::utf_8 decode/encode facade.
 *
 * Copyright (c) Softloq. All rights reserved.
 * Verifies string_view and C-string decoding, and Char/code-point encoding.
 */

#include "softloq/utf-8/utf-8.hpp"

#include <gtest/gtest.h>

namespace softloq::utf_8::tests
{

TEST(Utf8Tests, DecodeStringViewAcceptsAsciiText)
{
    const auto result = decode(std::string_view("A"));

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->get_code_point(), 0x41u);
}

TEST(Utf8Tests, DecodeStringViewAcceptsMultiOctetText)
{
    const std::string_view euro_sign("\xE2\x82\xAC"); // U+20AC '€'

    const auto result = decode(euro_sign);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->get_code_point(), 0x20ACu);
}

TEST(Utf8Tests, DecodeStringViewRejectsEmptyInput)
{
    const auto result = decode(std::string_view(""));

    EXPECT_FALSE(result.has_value());
}

TEST(Utf8Tests, DecodeCStringAcceptsAsciiText)
{
    const auto result = decode("A");

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->get_code_point(), 0x41u);
}

TEST(Utf8Tests, EncodeCodePointRoundTripsThroughDecode)
{
    const auto sequence_result = encode(static_cast<std::uint32_t>(0x20AC));
    ASSERT_TRUE(sequence_result.has_value());

    const auto character = decode(sequence_result.value());

    EXPECT_EQ(character.get_code_point(), 0x20ACu);
}

TEST(Utf8Tests, EncodeCodePointRejectsSurrogateRange)
{
    const auto result = encode(static_cast<std::uint32_t>(0xD800));

    EXPECT_FALSE(result.has_value());
}

} // namespace softloq::utf_8::tests
