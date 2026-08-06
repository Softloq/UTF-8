#include "softloq/utf-8/pch/pch.hpp"
#include "softloq/utf-8/utf-8.hpp"

namespace softloq::utf_8
{

std::expected<Char, Error> decode(const octet::OctetSequence& sequence) noexcept
{
    return Char::create(sequence);
}

std::expected<Char, Error> decode(const std::string_view& sequence_view) noexcept
{
    const auto length = sequence_view.length();
    if (length == 0) { return std::unexpected(Error::create_invalid_octet_sequence_error(octet::OctetSequence::create(octet::Octet(0)).value())); }

    const auto octet_sequence_result = [&]() -> std::expected<octet::OctetSequence, Error>
    {
        const auto num_of_octets_result = octet::get_octet_sequence_length(octet::Octet(static_cast<std::uint8_t>(sequence_view[0])));
        if (!num_of_octets_result) { return std::unexpected(Error::create_invalid_octet_sequence_error(octet::OctetSequence::create(octet::Octet(0)).value())); }

        if (length < num_of_octets_result.value()) { return std::unexpected(Error::create_invalid_octet_sequence_error(octet::OctetSequence::create(octet::Octet(0)).value())); }

        switch (num_of_octets_result.value())
        {
        case 1:
        {
            const auto octet_sequence_result = octet::OctetSequence::create(octet::Octet(static_cast<std::uint8_t>(sequence_view[0])));
            if (!octet_sequence_result) { return std::unexpected(Error::create_invalid_octet_sequence_error(octet::OctetSequence::create(octet::Octet(0)).value())); }
            return octet_sequence_result.value();
        }
        case 2:
        {
            return octet::OctetSequence::create(octet::Octet(static_cast<std::uint8_t>(sequence_view[0])), octet::Octet(static_cast<std::uint8_t>(sequence_view[1])));
        }
        case 3:
        {
            return octet::OctetSequence::create(octet::Octet(static_cast<std::uint8_t>(sequence_view[0])), octet::Octet(static_cast<std::uint8_t>(sequence_view[1])), octet::Octet(static_cast<std::uint8_t>(sequence_view[2])));
        }
        case 4:
        {
            return octet::OctetSequence::create(octet::Octet(static_cast<std::uint8_t>(sequence_view[0])), octet::Octet(static_cast<std::uint8_t>(sequence_view[1])), octet::Octet(static_cast<std::uint8_t>(sequence_view[2])), octet::Octet(static_cast<std::uint8_t>(sequence_view[3])));
        }
        }

        std::unreachable();
    }();

    return decode(octet_sequence);
}

std::expected<octet::OctetSequence, Error> encode(const Char& character) noexcept
{
    return character.to_octet_sequence();
}

} // namespace softloq::utf_8