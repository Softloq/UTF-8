#include "softloq/utf-8/pch/pch.hpp"
#include "softloq/utf-8/char.hpp"

namespace softloq::utf_8
{

std::expected<Char, Error> Char::create(const OctetSequence& sequence) noexcept
{
    const auto num_of_octets = sequence.get_length();
    
    switch(num_of_octets)
    {
    case 1:
    {
        const auto first_octet = sequence.at(0)->get();

        const std::uint32_t code_point = first_octet.get_value() & 0x7F;

        return Char::create(code_point);
    }
    case 2:
    {
        const auto first_octet = sequence.at(0)->get();
        const auto second_octet = sequence.at(1)->get();

        std::uint32_t code_point = first_octet.get_value() & 0x1F;
        code_point <<= 6;
        code_point |= second_octet.get_value() & 0x3F;

        return Char::create(code_point);
    }
    case 3:
    {
        const auto first_octet = sequence.at(0)->get();
        const auto second_octet = sequence.at(1)->get();
        const auto third_octet = sequence.at(2)->get();

        std::uint32_t code_point = first_octet.get_value() & 0x0F;
        code_point <<= 6;
        code_point |= second_octet.get_value() & 0x3F;
        code_point <<= 6;
        code_point |= third_octet.get_value() & 0x3F;

        return Char::create(code_point);
    }
    case 4:
    {
        const auto first_octet = sequence.at(0)->get();
        const auto second_octet = sequence.at(1)->get();
        const auto third_octet = sequence.at(2)->get();
        const auto fourth_octet = sequence.at(3)->get();

        std::uint32_t code_point = first_octet.get_value() & 0x07;
        code_point <<= 6;
        code_point |= second_octet.get_value() & 0x3F;
        code_point <<= 6;
        code_point |= third_octet.get_value() & 0x3F;
        code_point <<= 6;
        code_point |= fourth_octet.get_value() & 0x3F;

        return Char::create(code_point);
    }
    }

    std::unreachable();
}

std::expected<Char, Error> Char::create(std::uint32_t code_point) noexcept
{
    if (0xD800 <= code_point && code_point <= 0xDFFF) { return std::unexpected(Error::create_invalid_char_error(Char(code_point))); }
    if (code_point > 0x10FFFF) { return std::unexpected(Error::create_invalid_char_error(Char(code_point))); }

    return Char(code_point);
}

Char::Char(std::uint32_t code_point) noexcept : code_point(code_point) {}

std::uint32_t Char::get_code_point() const noexcept { return code_point; }

Char::operator std::uint32_t() const noexcept { return get_code_point(); }

OctetSequence Char::to_octet_sequence() const noexcept
{    
    if (code_point <= 0x7F)
    {
        const auto first_octet = Octet::create(static_cast<std::uint8_t>(code_point)).value();

        return OctetSequence::create(first_octet).value();
    }
    else if (code_point <= 0x7FF)
    {
        const auto first_octet = Octet::create(static_cast<std::uint8_t>(0xC0 | ((code_point >> 6) & 0x1F))).value();
        const auto second_octet = Octet::create(static_cast<std::uint8_t>(0x80 | (code_point & 0x3F))).value();

        return OctetSequence::create(first_octet, second_octet).value();
    }
    else if (code_point <= 0xFFFF)
    {
        const auto first_octet = Octet::create(static_cast<std::uint8_t>(0xE0 | ((code_point >> 12) & 0x0F))).value();
        const auto second_octet = Octet::create(static_cast<std::uint8_t>(0x80 | ((code_point >> 6) & 0x3F))).value();
        const auto third_octet = Octet::create(static_cast<std::uint8_t>(0x80 | (code_point & 0x3F))).value();

        return OctetSequence::create(first_octet, second_octet, third_octet).value();
    }
    else if (code_point <= 0x10FFFF)
    {
        const auto first_octet = Octet::create(static_cast<std::uint8_t>(0xF0 | ((code_point >> 18) & 0x07))).value();
        const auto second_octet = Octet::create(static_cast<std::uint8_t>(0x80 | ((code_point >> 12) & 0x3F))).value();
        const auto third_octet = Octet::create(static_cast<std::uint8_t>(0x80 | ((code_point >> 6) & 0x3F))).value();
        const auto fourth_octet = Octet::create(static_cast<std::uint8_t>(0x80 | (code_point & 0x3F))).value();

        return OctetSequence::create(first_octet, second_octet, third_octet, fourth_octet).value();
    }
    else { std::unreachable(); }
}

bool Char::is_bom() const noexcept { return code_point == 0xFEFF; }

bool Char::is_word_joiner() const noexcept { return code_point == 0x2060; }

std::strong_ordering Char::operator<=>(const Char& other) const noexcept
{
    return code_point <=> other.code_point;
}

} // namespace softloq::utf_8