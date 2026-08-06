#include "softloq/utf-8/pch/pch.hpp"
#include "softloq/utf-8/octet-sequence.hpp"

namespace softloq::utf_8
{

std::expected<OctetSequence, Error> OctetSequence::create(const Octet& first_octet) noexcept
{
    if (!first_octet.is_valid()) { return std::unexpected(Error::create_invalid_octet_error(first_octet)); }

    const auto length_result = get_octet_sequence_length(first_octet);
    if (!length_result) { return std::unexpected(Error::create_invalid_octet_sequence_length_error(1, 0)); }
    if (length_result.value() != 1) { return std::unexpected(Error::create_invalid_octet_sequence_length_error(1, length_result.value())); }

    return OctetSequence(first_octet);
}

std::expected<OctetSequence, Error> OctetSequence::create(const Octet& first_octet, const Octet& second_octet) noexcept
{
    if (!first_octet.is_valid()) { return std::unexpected(Error::create_invalid_octet_error(first_octet)); }
    if (!second_octet.is_valid()) { return std::unexpected(Error::create_invalid_octet_error(second_octet)); }

    const auto length_result = get_octet_sequence_length(first_octet);
    if (!length_result) { return std::unexpected(Error::create_invalid_octet_sequence_length_error(2, 0)); }
    if (length_result.value() != 2) { return std::unexpected(Error::create_invalid_octet_sequence_length_error(2, length_result.value())); }

    return OctetSequence(first_octet, second_octet);
}

std::expected<OctetSequence, Error> OctetSequence::create(const Octet& first_octet, const Octet& second_octet, const Octet& third_octet) noexcept
{
    if (!first_octet.is_valid()) { return std::unexpected(Error::create_invalid_octet_error(first_octet)); }
    if (!second_octet.is_valid()) { return std::unexpected(Error::create_invalid_octet_error(second_octet)); }
    if (!third_octet.is_valid()) { return std::unexpected(Error::create_invalid_octet_error(third_octet)); }

    const auto length_result = get_octet_sequence_length(first_octet);
    if (!length_result) { return std::unexpected(Error::create_invalid_octet_sequence_length_error(3, 0)); }
    if (length_result.value() != 3) { return std::unexpected(Error::create_invalid_octet_sequence_length_error(3, length_result.value())); }

    return OctetSequence(first_octet, second_octet, third_octet);
}

std::expected<OctetSequence, Error> OctetSequence::create(const Octet& first_octet, const Octet& second_octet, const Octet& third_octet, const Octet& fourth_octet) noexcept
{
    if (!first_octet.is_valid()) { return std::unexpected(Error::create_invalid_octet_error(first_octet)); }
    if (!second_octet.is_valid()) { return std::unexpected(Error::create_invalid_octet_error(second_octet)); }
    if (!third_octet.is_valid()) { return std::unexpected(Error::create_invalid_octet_error(third_octet)); }
    if (!fourth_octet.is_valid()) { return std::unexpected(Error::create_invalid_octet_error(fourth_octet)); }

    const auto length_result = get_octet_sequence_length(first_octet);
    if (!length_result) { return std::unexpected(Error::create_invalid_octet_sequence_length_error(4, 0)); }
    if (length_result.value() != 4) { return std::unexpected(Error::create_invalid_octet_sequence_length_error(4, length_result.value())); }

    return OctetSequence(first_octet, second_octet, third_octet, fourth_octet);
}

OctetSequence::OctetSequence(const Octet& first_octet) noexcept
    : octets(std::make_unique<Octet[]>(1)), length(1)
{
    octets[0] = first_octet;
}

OctetSequence::OctetSequence(const Octet& first_octet, const Octet& second_octet) noexcept
    : octets(std::make_unique<Octet[]>(2)), length(2)
{
    octets[0] = first_octet;
    octets[1] = second_octet;
}

OctetSequence::OctetSequence(const Octet& first_octet, const Octet& second_octet, const Octet& third_octet) noexcept
    : octets(std::make_unique<Octet[]>(3)), length(3)
{
    octets[0] = first_octet;
    octets[1] = second_octet;
    octets[2] = third_octet;
}

OctetSequence::OctetSequence(const Octet& first_octet, const Octet& second_octet, const Octet& third_octet, const Octet& fourth_octet) noexcept
    : octets(std::make_unique<Octet[]>(4)), length(4)
{
    octets[0] = first_octet;
    octets[1] = second_octet;
    octets[2] = third_octet;
    octets[3] = fourth_octet;
}

std::expected<std::reference_wrapper<const Octet>, Error> OctetSequence::at(std::size_t index) const noexcept
{
    if (index >= length) { return std::unexpected(Error::create_invalid_octet_error(Octet(0))); }

    return std::cref(octets[index]);
}

std::size_t OctetSequence::get_length() const noexcept { return length; }

bool OctetSequence::is_valid() const noexcept
{
    switch (length)
    {
    case 1: return octets[0].is_valid();
    case 2: return octets[0].is_valid() && octets[1].is_valid();
    case 3: return octets[0].is_valid() && octets[1].is_valid() && octets[2].is_valid();
    case 4: return octets[0].is_valid() && octets[1].is_valid() && octets[2].is_valid() && octets[3].is_valid();
    default: return false;
    }

    std::unreachable();
}

bool OctetSequence::is_bom() const noexcept
{
    if (length != 3) { return false; }

    return octets[0].get_value() == 0xEF && octets[1].get_value() == 0xBB && octets[2].get_value() == 0xBF;
}

bool OctetSequence::is_word_joiner() const noexcept
{
    if (length != 3) { return false; }

    return octets[0].get_value() == 0xE2 && octets[1].get_value() == 0x80 && octets[2].get_value() == 0x8C;
}

std::expected<std::size_t, Error> get_octet_sequence_length(const Octet& first_octet) noexcept
{
    if (!first_octet.is_valid()) { return std::unexpected(Error::create_invalid_octet_error(first_octet)); }

    if ((first_octet.get_value() & 0x80) == 0x00) { return 1; }
    else if ((first_octet.get_value() & 0xE0) == 0xC0) { return 2; }
    else if ((first_octet.get_value() & 0xF0) == 0xE0) { return 3; }
    else if ((first_octet.get_value() & 0xF8) == 0xF0) { return 4; }
    else { std::unreachable(); }
}

} // namespace softloq::utf_8