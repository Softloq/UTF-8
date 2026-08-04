#ifndef SOFTLOQ_UTF_8_OCTET_HPP
#define SOFTLOQ_UTF_8_OCTET_HPP

#include "softloq/UTF-8/API/api.hpp"
#include <cstdint>

namespace softloq::utf_8::octet
{

class Octet
{
public:
    SOFTLOQ_UTF_8_API Octet() noexcept;
    SOFTLOQ_UTF_8_API explicit Octet(std::uint8_t value) noexcept;

    SOFTLOQ_UTF_8_API operator std::uint8_t() const noexcept;
    SOFTLOQ_UTF_8_API bool is_valid() const noexcept;

private:
    std::uint8_t value;
};

} // namespace softloq::utf_8::octet

#endif // SOFTLOQ_UTF_8_OCTET_HPP