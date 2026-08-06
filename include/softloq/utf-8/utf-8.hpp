#ifndef SOFTLOQ_UTF_8_HPP
#define SOFTLOQ_UTF_8_HPP

#include "softloq/utf-8/api/api.hpp"
#include "softloq/utf-8/char.hpp"
#include "softloq/utf-8/octet/octet-sequence.hpp"
#include <string>

namespace softloq::utf_8
{

[[nodiscard]] SOFTLOQ_UTF_8_API std::expected<Char, Error> decode(const octet::OctetSequence& sequence) noexcept;
[[nodiscard]] SOFTLOQ_UTF_8_API std::expected<Char, Error> decode(const std::string_view& sequence_view) noexcept;
[[nodiscard]] SOFTLOQ_UTF_8_API std::expected<Char, Error> decode(const char* sequence_str) noexcept;

[[nodiscard]] SOFTLOQ_UTF_8_API std::expected<octet::OctetSequence, Error> encode(const Char& character) noexcept;
[[nodiscard]] SOFTLOQ_UTF_8_API std::expected<octet::OctetSequence, Error> encode(std::uint32_t code_point) noexcept;

} // namespace softloq::utf_8

#endif // SOFTLOQ_UTF_8_HPP