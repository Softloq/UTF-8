#include "softloq/utf-8/pch/pch.hpp"
#include "softloq/utf-8/utf-8.hpp"

namespace softloq::utf_8
{
    
Char::Char(const octet::OctetSequence& sequence) noexcept
{

}
Char::Char(std::uint32_t code_point) noexcept : code_point(code_point) {}

std::uint32_t Char::get_code_point() const noexcept { return code_point; }
Char::operator std::uint32_t() const noexcept { return get_code_point(); }

octet::OctetSequence Char::get_octet_sequence() const noexcept { return octet::OctetSequence(); }
Char::operator octet::OctetSequence() const noexcept { return get_octet_sequence(); }

bool Char::is_valid() const noexcept { return code_point <= 0x10FFFF; }

} // namespace softloq::utf_8