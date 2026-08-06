/**
 * @file char-tests.cpp
 * @author Brandon Foster (https://github.com/BrandonFoster)
 * @brief GoogleTest cases covering softloq::utf_8::Char.
 *
 * Copyright (c) Softloq. All rights reserved.
 * Verifies Char construction from code points and octet sequences, and round-trip encoding.
 */

#include "softloq/utf-8/char.hpp"
#include "softloq/utf-8/octet-sequence.hpp"

#include <gtest/gtest.h>

namespace softloq::utf_8::tests
{

TEST(CharTests, CreateAcceptsOrdinaryCodePoint)
{
    const auto result = Char::create(static_cast<std::uint32_t>(0x41));

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->get_code_point(), 0x41u);
}

TEST(CharTests, CreateRejectsSurrogateRange)
{
    EXPECT_FALSE(Char::create(static_cast<std::uint32_t>(0xD800)).has_value());
    EXPECT_FALSE(Char::create(static_cast<std::uint32_t>(0xDFFF)).has_value());
}

TEST(CharTests, CreateRejectsCodePointBeyondUnicodeRange)
{
    EXPECT_FALSE(Char::create(static_cast<std::uint32_t>(0x110000)).has_value());
}

TEST(CharTests, ToOctetSequenceRoundTripsAsciiCodePoint)
{
    const auto character = Char::create(static_cast<std::uint32_t>(0x41)).value();

    const auto sequence = character.to_octet_sequence();
    const auto decoded = Char::create(sequence).value();

    EXPECT_EQ(sequence.get_length(), 1);
    EXPECT_EQ(decoded.get_code_point(), character.get_code_point());
}

TEST(CharTests, ToOctetSequenceRoundTripsTwoOctetCodePoint)
{
    const auto character = Char::create(static_cast<std::uint32_t>(0xE9)).value(); // U+00E9 'é'

    const auto sequence = character.to_octet_sequence();
    const auto decoded = Char::create(sequence).value();

    EXPECT_EQ(sequence.get_length(), 2);
    EXPECT_EQ(decoded.get_code_point(), character.get_code_point());
}

TEST(CharTests, ToOctetSequenceRoundTripsThreeOctetCodePoint)
{
    const auto character = Char::create(static_cast<std::uint32_t>(0x20AC)).value(); // U+20AC '€'

    const auto sequence = character.to_octet_sequence();
    const auto decoded = Char::create(sequence).value();

    EXPECT_EQ(sequence.get_length(), 3);
    EXPECT_EQ(decoded.get_code_point(), character.get_code_point());
}

TEST(CharTests, ToOctetSequenceRoundTripsFourOctetCodePoint)
{
    const auto character = Char::create(static_cast<std::uint32_t>(0x1F600)).value(); // U+1F600 '😀'

    const auto sequence = character.to_octet_sequence();
    const auto decoded = Char::create(sequence).value();

    EXPECT_EQ(sequence.get_length(), 4);
    EXPECT_EQ(decoded.get_code_point(), character.get_code_point());
}

TEST(CharTests, IsBomDetectsByteOrderMarkCodePoint)
{
    const auto character = Char::create(static_cast<std::uint32_t>(0xFEFF)).value();

    EXPECT_TRUE(character.is_bom());
}

TEST(CharTests, OrderingMatchesCodePoint)
{
    const auto smaller = Char::create(static_cast<std::uint32_t>(0x41)).value();
    const auto larger = Char::create(static_cast<std::uint32_t>(0x42)).value();

    EXPECT_LT(smaller, larger);
}

} // namespace softloq::utf_8::tests
