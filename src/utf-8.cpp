/**
 * @file utf-8.cpp
 * @author Brandon Foster (https://github.com/BrandonFoster)
 * @brief Implements the top-level decode()/encode() facade declared in softloq/utf-8/utf-8.hpp.
 *
 * Copyright (c) Softloq. All rights reserved.
 * Implements convenience functions for converting between raw UTF-8 bytes and validated code points.
 */

#include "softloq/utf-8/pch/pch.hpp"
#include "softloq/utf-8/utf-8.hpp"

namespace softloq::utf_8
{

Char decode(const OctetSequence& sequence) noexcept
{
    return Char::create(sequence).value();
}

std::expected<Char, Error> decode(const std::string_view& sequence_view) noexcept
{
    const auto length = sequence_view.length();
    if (length == 0) { return std::unexpected(Error::create_encoding_empty_char_sequence_error()); }
    
    const auto first_octet_result = Octet::create(static_cast<std::uint8_t>(sequence_view[0]));
    if (!first_octet_result) { return std::unexpected(first_octet_result.error()); }    
    const auto first_octet = first_octet_result.value();

    const auto octet_sequence_length = get_octet_sequence_length(first_octet);
    if (length < octet_sequence_length) { return std::unexpected(Error::create_invalid_octet_sequence_length_error(octet_sequence_length, length)); }

    switch (get_octet_sequence_length(first_octet))
    {
    case 1:
    {
        const auto octet_sequence_result = OctetSequence::create(first_octet);
        return decode(octet_sequence_result.value());
    }
    case 2:
    {
        const auto second_octet_result = Octet::create(static_cast<std::uint8_t>(sequence_view[1]));
        if (!second_octet_result) { return std::unexpected(second_octet_result.error()); }
        const auto second_octet = second_octet_result.value();

        const auto octet_sequence_result = OctetSequence::create(first_octet, second_octet);
        if (!octet_sequence_result) { return std::unexpected(octet_sequence_result.error()); }
        return decode(octet_sequence_result.value());
    }
    case 3:
    {
        const auto second_octet_result = Octet::create(static_cast<std::uint8_t>(sequence_view[1]));
        if (!second_octet_result) { return std::unexpected(second_octet_result.error()); }
        const auto second_octet = second_octet_result.value();

        const auto third_octet_result = Octet::create(static_cast<std::uint8_t>(sequence_view[2]));
        if (!third_octet_result) { return std::unexpected(third_octet_result.error()); }
        const auto third_octet = third_octet_result.value();

        const auto octet_sequence_result = OctetSequence::create(first_octet, second_octet, third_octet);
        if (!octet_sequence_result) { return std::unexpected(octet_sequence_result.error()); }
        return decode(octet_sequence_result.value());
    }
    case 4:
    {
        const auto second_octet_result = Octet::create(static_cast<std::uint8_t>(sequence_view[1]));
        if (!second_octet_result) { return std::unexpected(second_octet_result.error()); }
        const auto second_octet = second_octet_result.value();

        const auto third_octet_result = Octet::create(static_cast<std::uint8_t>(sequence_view[2]));
        if (!third_octet_result) { return std::unexpected(third_octet_result.error()); }
        const auto third_octet = third_octet_result.value();

        const auto fourth_octet_result = Octet::create(static_cast<std::uint8_t>(sequence_view[3]));
        if (!fourth_octet_result) { return std::unexpected(fourth_octet_result.error()); }
        const auto fourth_octet = fourth_octet_result.value();

        const auto octet_sequence_result = OctetSequence::create(first_octet, second_octet, third_octet, fourth_octet);
        if (!octet_sequence_result) { return std::unexpected(octet_sequence_result.error()); }
        return decode(octet_sequence_result.value());
    }
    default: std::unreachable();
    }
    
    std::unreachable();
}

std::expected<Char, Error> decode(const char* sequence_str) noexcept
{
    std::uint8_t length = 0;
    while (length < 4)
    {
        if (sequence_str + length == nullptr) { break; }
        length++;
        if (length == 4) { break; }
    }

    if (length == 0) { return std::unexpected(Error::create_encoding_empty_char_sequence_error()); }
    
    const auto first_octet_result = Octet::create(static_cast<std::uint8_t>(sequence_str[0]));
    if (!first_octet_result) { return std::unexpected(first_octet_result.error()); }    
    const auto first_octet = first_octet_result.value();

    const auto octet_sequence_length = get_octet_sequence_length(first_octet);
    if (length < octet_sequence_length) { return std::unexpected(Error::create_invalid_octet_sequence_length_error(octet_sequence_length, length)); }

    switch (get_octet_sequence_length(first_octet))
    {
    case 1:
    {
        const auto octet_sequence_result = OctetSequence::create(first_octet);
        return decode(octet_sequence_result.value());
    }
    case 2:
    {
        const auto second_octet_result = Octet::create(static_cast<std::uint8_t>(sequence_str[1]));
        if (!second_octet_result) { return std::unexpected(second_octet_result.error()); }
        const auto second_octet = second_octet_result.value();

        const auto octet_sequence_result = OctetSequence::create(first_octet, second_octet);
        if (!octet_sequence_result) { return std::unexpected(octet_sequence_result.error()); }
        return decode(octet_sequence_result.value());
    }
    case 3:
    {
        const auto second_octet_result = Octet::create(static_cast<std::uint8_t>(sequence_str[1]));
        if (!second_octet_result) { return std::unexpected(second_octet_result.error()); }
        const auto second_octet = second_octet_result.value();

        const auto third_octet_result = Octet::create(static_cast<std::uint8_t>(sequence_str[2]));
        if (!third_octet_result) { return std::unexpected(third_octet_result.error()); }
        const auto third_octet = third_octet_result.value();

        const auto octet_sequence_result = OctetSequence::create(first_octet, second_octet, third_octet);
        if (!octet_sequence_result) { return std::unexpected(octet_sequence_result.error()); }
        return decode(octet_sequence_result.value());
    }
    case 4:
    {
        const auto second_octet_result = Octet::create(static_cast<std::uint8_t>(sequence_str[1]));
        if (!second_octet_result) { return std::unexpected(second_octet_result.error()); }
        const auto second_octet = second_octet_result.value();

        const auto third_octet_result = Octet::create(static_cast<std::uint8_t>(sequence_str[2]));
        if (!third_octet_result) { return std::unexpected(third_octet_result.error()); }
        const auto third_octet = third_octet_result.value();

        const auto fourth_octet_result = Octet::create(static_cast<std::uint8_t>(sequence_str[3]));
        if (!fourth_octet_result) { return std::unexpected(fourth_octet_result.error()); }
        const auto fourth_octet = fourth_octet_result.value();

        const auto octet_sequence_result = OctetSequence::create(first_octet, second_octet, third_octet, fourth_octet);
        if (!octet_sequence_result) { return std::unexpected(octet_sequence_result.error()); }
        return decode(octet_sequence_result.value());
    }
    default: std::unreachable();
    }
    
    std::unreachable();
}

OctetSequence encode(const Char& character) noexcept
{
    return character.to_octet_sequence();
}

std::expected<OctetSequence, Error> encode(std::uint32_t code_point) noexcept
{
    const auto character_result = Char::create(code_point);
    if (!character_result) { return std::unexpected(character_result.error()); }

    return character_result.value().to_octet_sequence();
}

} // namespace softloq::utf_8