#ifndef SOFTLOQ_UTF_8_OCTET_HPP
#define SOFTLOQ_UTF_8_OCTET_HPP

#include "softloq/utf-8/api/api.hpp"

#include <cstdint>

namespace softloq::utf_8
{

class Octet final
{
public:
    [[nodiscard]] SOFTLOQ_UTF_8_API Octet() noexcept;
    [[nodiscard]] SOFTLOQ_UTF_8_API Octet(std::uint8_t value) noexcept;

    [[nodiscard]] SOFTLOQ_UTF_8_API operator std::uint8_t() const noexcept;
    [[nodiscard]] SOFTLOQ_UTF_8_API std::uint8_t get_value() const noexcept;
    [[nodiscard]] SOFTLOQ_UTF_8_API bool is_valid() const noexcept;

private:
    std::uint8_t value;
};

} // namespace softloq::utf_8

#endif // SOFTLOQ_UTF_8_OCTET_HPP