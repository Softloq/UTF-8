/**
 * @file octet-tests.cpp
 * @author Brandon Foster (https://github.com/BrandonFoster)
 * @brief GoogleTest cases covering softloq::utf_8::Octet.
 *
 * Copyright (c) Softloq. All rights reserved.
 * Verifies Octet construction, value access, conversion, and ordering.
 */

#include "softloq/utf-8/octet.hpp"

#include <gtest/gtest.h>

namespace softloq::utf_8::tests
{

TEST(OctetTests, CreateAcceptsOrdinaryValues)
{
    const auto result = Octet::create(0x41);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->get_value(), 0x41);
}

TEST(OctetTests, CreateRejectsReservedLeadValues)
{
    EXPECT_FALSE(Octet::create(0xC0).has_value());
    EXPECT_FALSE(Octet::create(0xC1).has_value());
    EXPECT_FALSE(Octet::create(0xF5).has_value());
    EXPECT_FALSE(Octet::create(0xFF).has_value());
}

TEST(OctetTests, ImplicitConversionReturnsValue)
{
    const auto octet = Octet::create(0x7F).value();

    EXPECT_EQ(static_cast<std::uint8_t>(octet), 0x7F);
}

TEST(OctetTests, OrderingMatchesUnderlyingValue)
{
    const auto smaller = Octet::create(0x10).value();
    const auto larger = Octet::create(0x20).value();

    EXPECT_LT(smaller, larger);
    EXPECT_EQ(smaller, Octet::create(0x10).value());
}

} // namespace softloq::utf_8::tests
