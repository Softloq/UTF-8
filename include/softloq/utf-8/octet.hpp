/**
 * @file softloq/utf-8/octet.hpp
 * @author Brandon Foster (https://github.com/BrandonFoster)
 * @brief Declares the Octet type representing a single validated UTF-8 byte.
 *
 * Copyright (c) Softloq. All rights reserved.
 * Declares construction, value access, and comparison of a single validated UTF-8 byte.
 */

#ifndef SOFTLOQ_UTF_8_OCTET_HPP
#define SOFTLOQ_UTF_8_OCTET_HPP

#include "softloq/utf-8/api/api.hpp"
#include "softloq/utf-8/error.hpp"

#include <cstdint>
#include <compare>
#include <expected>

namespace softloq::utf_8
{

class Octet final
{
public:
    [[nodiscard]] static SOFTLOQ_UTF_8_API std::expected<Octet, Error> create(std::uint8_t value) noexcept;

    [[nodiscard]] SOFTLOQ_UTF_8_API operator std::uint8_t() const noexcept;
    [[nodiscard]] SOFTLOQ_UTF_8_API std::uint8_t get_value() const noexcept;

    [[nodiscard]] SOFTLOQ_UTF_8_API std::strong_ordering operator<=>(const Octet& other) const noexcept;

private:
    std::uint8_t value;

    [[nodiscard]] SOFTLOQ_UTF_8_API Octet(std::uint8_t value) noexcept;
};

} // namespace softloq::utf_8

#endif // SOFTLOQ_UTF_8_OCTET_HPP