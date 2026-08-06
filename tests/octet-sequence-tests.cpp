/**
 * @file octet-sequence-tests.cpp
 * @author Brandon Foster (https://github.com/BrandonFoster)
 * @brief GoogleTest cases covering softloq::utf_8::OctetSequence.
 *
 * Copyright (c) Softloq. All rights reserved.
 * Verifies OctetSequence construction, length-mismatch rejection, indexing, and BOM detection.
 */

#include "softloq/utf-8/octet-sequence.hpp"

#include <gtest/gtest.h>

namespace softloq::utf_8::tests
{

TEST(OctetSequenceTests, SingleOctetSequenceHasLengthOne)
{
    const auto first = Octet::create(0x41).value();
    const auto sequence = OctetSequence::create(first).value();

    EXPECT_EQ(sequence.get_length(), 1);
    EXPECT_EQ(sequence.at(0)->get().get_value(), 0x41);
}

TEST(OctetSequenceTests, CreateRejectsMismatchedLeadByteLength)
{
    const auto two_byte_lead = Octet::create(0xC3).value();

    const auto result = OctetSequence::create(two_byte_lead);

    EXPECT_FALSE(result.has_value());
}

TEST(OctetSequenceTests, TwoOctetSequenceRoundTripsValues)
{
    const auto first = Octet::create(0xC3).value();
    const auto second = Octet::create(0xA9).value();

    const auto sequence = OctetSequence::create(first, second).value();

    EXPECT_EQ(sequence.get_length(), 2);
    EXPECT_EQ(sequence.at(0)->get().get_value(), 0xC3);
    EXPECT_EQ(sequence.at(1)->get().get_value(), 0xA9);
}

TEST(OctetSequenceTests, AtRejectsOutOfBoundsIndex)
{
    const auto first = Octet::create(0x41).value();
    const auto sequence = OctetSequence::create(first).value();

    EXPECT_FALSE(sequence.at(1).has_value());
}

TEST(OctetSequenceTests, IsBomDetectsBomBytes)
{
    const auto first = Octet::create(0xEF).value();
    const auto second = Octet::create(0xBB).value();
    const auto third = Octet::create(0xBF).value();

    const auto sequence = OctetSequence::create(first, second, third).value();

    EXPECT_TRUE(sequence.is_bom());
}

TEST(OctetSequenceTests, OrderingComparesLengthThenOctets)
{
    const auto shorter = OctetSequence::create(Octet::create(0x41).value()).value();
    const auto longer = OctetSequence::create(Octet::create(0xC3).value(), Octet::create(0xA9).value()).value();

    EXPECT_LT(shorter, longer);
}

} // namespace softloq::utf_8::tests
