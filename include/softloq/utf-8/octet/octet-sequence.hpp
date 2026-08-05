#ifndef SOFTLOQ_UTF_8_OCTET_SEQUENCE_HPP
#define SOFTLOQ_UTF_8_OCTET_SEQUENCE_HPP

#include "softloq/utf-8/api/api.hpp"
#include "softloq/utf-8/octet/octet.hpp"
#include "softloq/utf-8/octet/error.hpp"
#include <expected>
#include <cstddef>

namespace softloq::utf_8::octet
{

class OctetSequence
{
public:
private:
};

SOFTLOQ_UTF_8_API std::expected<std::size_t, Error> get_octet_sequence_length(const Octet& first_octet) noexcept;

} // namespace softloq::utf_8::octet

#endif // SOFTLOQ_UTF_8_OCTET_SEQUENCE_HPP