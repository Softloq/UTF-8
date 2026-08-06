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

    const auto octet_sequence = OctetSequence::create(Octet(static_cast<std::uint8_t>(sequence_view[0])));
    if (!octet_sequence) { return std::unexpected(Error::create_invalid_octet_sequence_error(OctetSequence::create(Octet(0)).value())); }
    return decode(octet_sequence.value());
}

std::expected<OctetSequence, Error> encode(const Char& character) noexcept
{
    return character.to_octet_sequence();
}

} // namespace softloq::utf_8