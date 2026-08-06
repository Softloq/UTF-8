#include "softloq/utf-8/pch/pch.hpp"
#include "softloq/utf-8/octet.hpp"

namespace softloq::utf_8
{

std::expected<Octet, Error> Octet::create(std::uint8_t value) noexcept
{
    Octet octet(value);

    switch (value)
    {
    case 0xC0:
    case 0xC1:
    case 0xF5:
    case 0xF6:
    case 0xF7:
    case 0xF8:
    case 0xF9:
    case 0xFA:
    case 0xFB:
    case 0xFC:
    case 0xFD:
    case 0xFE:
    case 0xFF: return std::unexpected(Error::create_invalid_octet_error(octet));

    default: return octet;
    }

    std::unreachable();
}

Octet::Octet(std::uint8_t value) noexcept : value(value) {}

Octet::operator std::uint8_t() const noexcept { return value; }

std::uint8_t Octet::get_value() const noexcept { return value; }

} // namespace softloq::utf_8
