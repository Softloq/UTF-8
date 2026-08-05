#ifndef SOFTLOQ_UTF_8_CHAR_HPP
#define SOFTLOQ_UTF_8_CHAR_HPP

#include "softloq/utf-8/api/api.hpp"
#include "softloq/utf-8/octet/octet-sequence.hpp"
#include "softloq/utf-8/error.hpp"
#include <cstdint>

namespace softloq::utf_8
{

class Char final
{
public:
    [[nodiscard]] static SOFTLOQ_UTF_8_API std::expected<Char, Error> create(const octet::OctetSequence& sequence) noexcept;
    [[nodiscard]] static SOFTLOQ_UTF_8_API std::expected<Char, Error> create(std::uint32_t code_point) noexcept;

    [[nodiscard]] SOFTLOQ_UTF_8_API std::uint32_t get_code_point() const noexcept;
    [[nodiscard]] SOFTLOQ_UTF_8_API operator std::uint32_t() const noexcept;

    [[nodiscard]] SOFTLOQ_UTF_8_API std::expected<octet::OctetSequence, Error> to_octet_sequence() const noexcept;

    [[nodiscard]] SOFTLOQ_UTF_8_API bool is_valid() const noexcept;

    [[nodiscard]] SOFTLOQ_UTF_8_API bool is_bom() const noexcept;
    [[nodiscard]] SOFTLOQ_UTF_8_API bool is_word_joiner() const noexcept;

private:
    std::uint32_t code_point;

    [[nodiscard]] SOFTLOQ_UTF_8_API explicit Char(std::uint32_t code_point) noexcept;
};

} // namespace softloq::utf_8

#endif // SOFTLOQ_UTF_8_CHAR_HPP