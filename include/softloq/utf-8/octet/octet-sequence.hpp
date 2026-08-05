#ifndef SOFTLOQ_UTF_8_OCTET_SEQUENCE_HPP
#define SOFTLOQ_UTF_8_OCTET_SEQUENCE_HPP

#include "softloq/utf-8/api/api.hpp"
#include "softloq/utf-8/octet/octet.hpp"
#include "softloq/utf-8/octet/error.hpp"
#include <expected>
#include <cstddef>
#include <memory>

namespace softloq::utf_8::octet
{

class OctetSequence final
{
public:
    [[nodiscard]] static SOFTLOQ_UTF_8_API std::expected<OctetSequence, Error> create(const Octet& first_octet) noexcept;
    [[nodiscard]] static SOFTLOQ_UTF_8_API std::expected<OctetSequence, Error> create(const Octet& first_octet, const Octet& second_octet) noexcept;
    [[nodiscard]] static SOFTLOQ_UTF_8_API std::expected<OctetSequence, Error> create(const Octet& first_octet, const Octet& second_octet, const Octet& third_octet) noexcept;
    [[nodiscard]] static SOFTLOQ_UTF_8_API std::expected<OctetSequence, Error> create(const Octet& first_octet, const Octet& second_octet, const Octet& third_octet, const Octet& fourth_octet) noexcept;

    [[nodiscard]] SOFTLOQ_UTF_8_API std::expected<std::reference_wrapper<const Octet>, Error> at(std::size_t index) const noexcept;
    [[nodiscard]] SOFTLOQ_UTF_8_API std::expected<std::size_t, Error> get_length() const noexcept;
    [[nodiscard]] SOFTLOQ_UTF_8_API bool is_valid() const noexcept;

private:
    std::unique_ptr<Octet[]> octets;

    [[nodiscard]] SOFTLOQ_UTF_8_API OctetSequence(const Octet& first_octet) noexcept;
    [[nodiscard]] SOFTLOQ_UTF_8_API OctetSequence(const Octet& first_octet, const Octet& second_octet) noexcept;
    [[nodiscard]] SOFTLOQ_UTF_8_API OctetSequence(const Octet& first_octet, const Octet& second_octet, const Octet& third_octet) noexcept;
    [[nodiscard]] SOFTLOQ_UTF_8_API OctetSequence(const Octet& first_octet, const Octet& second_octet, const Octet& third_octet, const Octet& fourth_octet) noexcept;

};

[[nodiscard]] SOFTLOQ_UTF_8_API std::expected<std::size_t, Error> get_octet_sequence_length(const Octet& first_octet) noexcept;

} // namespace softloq::utf_8::octet

#endif // SOFTLOQ_UTF_8_OCTET_SEQUENCE_HPP