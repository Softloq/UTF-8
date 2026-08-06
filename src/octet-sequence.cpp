#include "softloq/utf-8/pch/pch.hpp"
#include "softloq/utf-8/octet-sequence.hpp"

namespace softloq::utf_8
{

std::expected<OctetSequence, Error> OctetSequence::create(const Octet& first_octet) noexcept
{
    const auto length = get_octet_sequence_length(first_octet);
    if (length != 1) { return std::unexpected(Error::create_invalid_octet_sequence_length_error(1, length)); }

    return OctetSequence(first_octet);
}

std::expected<OctetSequence, Error> OctetSequence::create(const Octet& first_octet, const Octet& second_octet) noexcept
{
    const auto length = get_octet_sequence_length(first_octet);
    if (length != 2) { return std::unexpected(Error::create_invalid_octet_sequence_length_error(2, length)); }

    return OctetSequence(first_octet, second_octet);
}

std::expected<OctetSequence, Error> OctetSequence::create(const Octet& first_octet, const Octet& second_octet, const Octet& third_octet) noexcept
{
    const auto length = get_octet_sequence_length(first_octet);
    if (length != 3) { return std::unexpected(Error::create_invalid_octet_sequence_length_error(3, length)); }

    return OctetSequence(first_octet, second_octet, third_octet);
}

std::expected<OctetSequence, Error> OctetSequence::create(const Octet& first_octet, const Octet& second_octet, const Octet& third_octet, const Octet& fourth_octet) noexcept
{
    const auto length = get_octet_sequence_length(first_octet);
    if (length != 4) { return std::unexpected(Error::create_invalid_octet_sequence_length_error(4, length)); }

    return OctetSequence(first_octet, second_octet, third_octet, fourth_octet);
}

OctetSequence::OctetSequence(const Octet& first_octet) noexcept
    : octets(std::unique_ptr<Octet[]>(new Octet[1]{ first_octet }))
    , length(1)
{
}

OctetSequence::OctetSequence(const Octet& first_octet, const Octet& second_octet) noexcept
    : octets(std::unique_ptr<Octet[]>(new Octet[2]{ first_octet, second_octet }))
    , length(2)
{
}

OctetSequence::OctetSequence(const Octet& first_octet, const Octet& second_octet, const Octet& third_octet) noexcept
    : octets(std::unique_ptr<Octet[]>(new Octet[3]{ first_octet, second_octet, third_octet }))
    , length(3)
{
}

OctetSequence::OctetSequence(const Octet& first_octet, const Octet& second_octet, const Octet& third_octet, const Octet& fourth_octet) noexcept
    : octets(std::unique_ptr<Octet[]>(new Octet[4]{ first_octet, second_octet, third_octet, fourth_octet }))
    , length(4)
{
}

std::expected<std::reference_wrapper<const Octet>, Error> OctetSequence::at(std::size_t index) const noexcept
{
    if (index >= length) { return std::unexpected(Error::create_invalid_octet_sequence_index_error(index, length)); }

    return std::cref(octets[index]);
}

std::size_t OctetSequence::get_length() const noexcept { return length; }

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

std::strong_ordering OctetSequence::operator<=>(const OctetSequence& other) const noexcept
{
    if (length != other.length) { return length <=> other.length; }

    for (std::size_t i = 0; i < length; ++i)
    {
        const auto comparison = octets[i] <=> other.octets[i];
        if (comparison != std::strong_ordering::equal) { return comparison; }
    }

    return std::strong_ordering::equal;
}

std::size_t get_octet_sequence_length(const Octet& first_octet) noexcept
{
    if ((first_octet.get_value() & 0x80) == 0x00) { return 1; }
    else if ((first_octet.get_value() & 0xE0) == 0xC0) { return 2; }
    else if ((first_octet.get_value() & 0xF0) == 0xE0) { return 3; }
    else if ((first_octet.get_value() & 0xF8) == 0xF0) { return 4; }
    else { std::unreachable(); }
}

} // namespace softloq::utf_8