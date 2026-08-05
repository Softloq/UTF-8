#include "softloq/utf-8/pch/pch.hpp"
#include "softloq/utf-8/octet/octet-sequence.hpp"

namespace softloq::utf_8::octet
{

std::expected<std::size_t, Error> get_octet_sequence_length(const Octet& first_octet) noexcept
{
    if (!first_octet.is_valid())
    {
        return std::unexpected(Error::create_invalid_octet_error(first_octet));
    }

    if ((first_octet.get_value() & 0xE0) == 0xC0)
    {
        return 2;
    }
    else if ((first_octet.get_value() & 0xF0) == 0xE0)
    {
        return 3;
    }
    else if ((first_octet.get_value() & 0xF8) == 0xF0)
    {
        return 4;
    }
    else std::unreachable();
}

} // namespace softloq::utf_8::octet