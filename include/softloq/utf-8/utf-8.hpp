/**
 * @file softloq/utf-8/utf-8.hpp
 * @author Brandon Foster (https://github.com/BrandonFoster)
 * @brief Declares the top-level decode()/encode() facade for the library.
 *
 * Copyright (c) Softloq. All rights reserved.
 * Declares convenience functions for converting between raw UTF-8 bytes and validated code points.
 */

#ifndef SOFTLOQ_UTF_8_HPP
#define SOFTLOQ_UTF_8_HPP

#include "softloq/utf-8/api/api.hpp"
#include "softloq/utf-8/char.hpp"
#include "softloq/utf-8/octet-sequence.hpp"

#include <string_view>
#include <expected>

namespace softloq::utf_8
{

[[nodiscard]] SOFTLOQ_UTF_8_API Char decode(const OctetSequence& sequence) noexcept;
[[nodiscard]] SOFTLOQ_UTF_8_API std::expected<Char, Error> decode(const std::string_view& sequence_view) noexcept;
[[nodiscard]] SOFTLOQ_UTF_8_API std::expected<Char, Error> decode(const char* sequence_str) noexcept;

[[nodiscard]] SOFTLOQ_UTF_8_API OctetSequence encode(const Char& character) noexcept;
[[nodiscard]] SOFTLOQ_UTF_8_API std::expected<OctetSequence, Error> encode(std::uint32_t code_point) noexcept;

} // namespace softloq::utf_8

#endif // SOFTLOQ_UTF_8_HPP