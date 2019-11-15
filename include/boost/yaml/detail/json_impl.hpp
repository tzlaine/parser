#ifndef BOOST_YAML_DETAIL_JSON_IMPL_HPP
#define BOOST_YAML_DETAIL_JSON_IMPL_HPP

#include <boost/yaml/json_fwd.hpp>

#include <boost/text/algorithm.hpp>
#include <boost/text/transcode_view.hpp>

#include <iomanip>
#include <iostream>


namespace boost { namespace json { namespace detail {

    template<>
    struct value_impl<object> : value_impl_base
    {
        template<typename Iter>
        value_impl(Iter first, Iter last) : value_(first, last)
        {}
        value_impl(object && o) : value_(std::move(o)) {}

        virtual std::unique_ptr<value_impl_base> copy_impl() const override
        {
            return std::unique_ptr<value_impl_base>(
                new value_impl<object>(*this));
        }

        virtual value_kind kind() const noexcept override
        {
            return value_kind::object;
        }

        virtual bool equal_impl(value const & rhs) const noexcept override
        {
            return value_ == get<object>(rhs);
        }

        virtual std::ostream & to_json(std::ostream & os) const
            noexcept override;

        object value_;
    };

    template<>
    struct value_impl<array> : value_impl_base
    {
        template<typename Iter>
        value_impl(Iter first, Iter last) : value_(first, last)
        {}
        value_impl(array && a) : value_(std::move(a)) {}

        virtual std::unique_ptr<value_impl_base> copy_impl() const override
        {
            return std::unique_ptr<value_impl_base>(
                new value_impl<array>(*this));
        }

        virtual value_kind kind() const noexcept override
        {
            return value_kind::array;
        }

        virtual bool equal_impl(value const & rhs) const noexcept override
        {
            return value_ == get<array>(rhs);
        }

        virtual std::ostream & to_json(std::ostream & os) const
            noexcept override;

        array value_;
    };

    template<typename CPSubRange>
    std::ostream &
    write_escaped_cps(std::ostream & os, CPSubRange subr) noexcept
    {
        os << std::hex << std::setfill('0');
        for (auto cp : subr) {
            switch (cp) {
            case 0x0022: os << "\\\""; break;
            case 0x005c: os << "\\\\"; break;
            case 0x002f: os << "\\/"; break;
            case 0x0008: os << "\\b"; break;
            case 0x000c: os << "\\f"; break;
            case 0x000a: os << "\\n"; break;
            case 0x000d: os << "\\r"; break;
            case 0x0009: os << "\\t"; break;
            default:
                if (cp < 0x20) {
                    os << "\\u" << std::setw(4) << cp;
                } else {
                    uint16_t const high_surrogate_base = 0xd7c0;
                    uint16_t const low_surrogate_base = 0xdc00;
                    auto const hi =
                        static_cast<uint16_t>(cp >> 10) + high_surrogate_base;
                    auto const lo =
                        static_cast<uint16_t>(cp & 0x3ff) + low_surrogate_base;
                    os << "\\u" << std::setw(4) << hi;
                    os << "\\u" << std::setw(4) << lo;
                }
                break;
            }
        }
        os << std::dec;
        return os;
    }

    inline std::ostream &
    to_json(std::ostream & os, std::string_view s) noexcept
    {
        os << '"';
        auto const r = text::as_utf32(s);
        char const * last_written_it = &*s.begin();
        text::foreach_subrange_if(
            r.begin(),
            r.end(),
            [](uint32_t cp) { return cp < 0x0020 || 0xffff < cp; },
            [&](auto subr) {
                os.write(
                    last_written_it, &*subr.begin().base() - last_written_it);
                detail::write_escaped_cps(os, subr);
                last_written_it = &*subr.end().base();
            });
        os.write(last_written_it, &*s.end() - last_written_it);
        os << '"';
        return os;
    }

    template<>
    struct value_impl<std::string> : value_impl_base
    {
        template<typename Iter>
        value_impl(Iter f, Iter l) : value_(f, l)
        {}
        value_impl(std::string && s) : value_(std::move(s)) {}
        value_impl(std::string_view s) : value_(s) {}

        virtual std::unique_ptr<value_impl_base> copy_impl() const override
        {
            return std::unique_ptr<value_impl_base>(
                new value_impl<std::string>(*this));
        }

        virtual value_kind kind() const noexcept override
        {
            return value_kind::string;
        }

        virtual bool equal_impl(value const & rhs) const noexcept override
        {
            return value_ == get<std::string_view>(rhs);
        }

        virtual std::ostream & to_json(std::ostream & os) const
            noexcept override
        {
            return detail::to_json(os, value_);
        }

        std::string value_;
    };

}}}

#endif
