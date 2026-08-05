#ifndef SOFTLOQ_UTF_8_HPP
#define SOFTLOQ_UTF_8_HPP

#include "softloq/utf-8/api/api.hpp"
#include "softloq/utf-8/octet/octet-sequence.hpp"
#include <cstdint>

namespace softloq::utf_8
{

class Char
{
public:
    SOFTLOQ_UTF_8_API Char(const octet::OctetSequence& sequence) noexcept;
    SOFTLOQ_UTF_8_API explicit Char(std::uint32_t code_point) noexcept;

    SOFTLOQ_UTF_8_API std::uint32_t get_code_point() const noexcept;
    SOFTLOQ_UTF_8_API operator std::uint32_t() const noexcept;

    SOFTLOQ_UTF_8_API octet::OctetSequence get_octet_sequence() const noexcept;
    SOFTLOQ_UTF_8_API operator octet::OctetSequence() const noexcept;

    SOFTLOQ_UTF_8_API bool is_valid() const noexcept;

private:
    std::uint32_t code_point;
};

} // namespace softloq::utf_8

#endif // SOFTLOQ_UTF_8_HPP