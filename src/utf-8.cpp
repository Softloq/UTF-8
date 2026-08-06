#include "softloq/utf-8/pch/pch.hpp"
#include "softloq/utf-8/utf-8.hpp"

namespace softloq::utf_8
{

std::expected<Char, Error> decode(const OctetSequence& sequence) noexcept
{
    return Char::create(sequence);
}

std::expected<Char, Error> decode(const std::string_view& sequence_view) noexcept
{
    const auto length = sequence_view.length();
    if (length == 0) { return std::unexpected(Error::create_invalid_octet_sequence_error(OctetSequence::create(Octet(0)).value())); }
    
    const auto octet_sequence_length_result = get_octet_sequence_length(static_cast<std::uint8_t>(sequence_view[0]));
    if (!octet_sequence_length_result) { return std::unexpected(octet_sequence_length_result.error()); }

    const auto octet_sequence_length = octet_sequence_length_result.value();

    switch (octet_sequence_length)
    {
    case 1:
    {
        const auto octet_sequence_result = OctetSequence::create(static_cast<std::uint8_t>(sequence_view[0]));
        if (!octet_sequence_result) { return std::unexpected(octet_sequence_result.error()); }
        return decode(octet_sequence_result.value());
    }
    case 2:
    {
        const auto octet_sequence_result = OctetSequence::create(static_cast<std::uint8_t>(sequence_view[0]), static_cast<std::uint8_t>(sequence_view[1]));
        if (!octet_sequence_result) { return std::unexpected(octet_sequence_result.error()); }
        return decode(octet_sequence_result.value());
    }
    case 3:
    {
        const auto octet_sequence_result = OctetSequence::create(static_cast<std::uint8_t>(sequence_view[0]), static_cast<std::uint8_t>(sequence_view[1]), static_cast<std::uint8_t>(sequence_view[2]));
        if (!octet_sequence_result) { return std::unexpected(octet_sequence_result.error()); }
        return decode(octet_sequence_result.value());
    }
    case 4:
    {
        const auto octet_sequence_result = OctetSequence::create(static_cast<std::uint8_t>(sequence_view[0]), static_cast<std::uint8_t>(sequence_view[1]), static_cast<std::uint8_t>(sequence_view[2]), static_cast<std::uint8_t>(sequence_view[3]));
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

    const auto octet_sequence_length_result = get_octet_sequence_length(static_cast<std::uint8_t>(sequence_str[0]));
    if (!octet_sequence_length_result) { return std::unexpected(octet_sequence_length_result.error()); }

    const auto octet_sequence_length = octet_sequence_length_result.value();

    switch (octet_sequence_length)
    {
    case 1:
    {
        const auto octet_sequence_result = OctetSequence::create(static_cast<std::uint8_t>(sequence_str[0]));
        if (!octet_sequence_result) { return std::unexpected(octet_sequence_result.error()); }
        return decode(octet_sequence_result.value());
    }
    case 2:
    {
        const auto octet_sequence_result = OctetSequence::create(static_cast<std::uint8_t>(sequence_str[0]), static_cast<std::uint8_t>(sequence_str[1]));
        if (!octet_sequence_result) { return std::unexpected(octet_sequence_result.error()); }
        return decode(octet_sequence_result.value());
    }
    case 3:
    {
        const auto octet_sequence_result = OctetSequence::create(static_cast<std::uint8_t>(sequence_str[0]), static_cast<std::uint8_t>(sequence_str[1]), static_cast<std::uint8_t>(sequence_str[2]));
        if (!octet_sequence_result) { return std::unexpected(octet_sequence_result.error()); }
        return decode(octet_sequence_result.value());
    }
    case 4:
    {
        const auto octet_sequence_result = OctetSequence::create(static_cast<std::uint8_t>(sequence_str[0]), static_cast<std::uint8_t>(sequence_str[1]), static_cast<std::uint8_t>(sequence_str[2]), static_cast<std::uint8_t>(sequence_str[3]));
        if (!octet_sequence_result) { return std::unexpected(octet_sequence_result.error()); }
        return decode(octet_sequence_result.value());
    }
    default: std::unreachable();
    }
    
    std::unreachable();
}

std::expected<OctetSequence, Error> encode(const Char& character) noexcept
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