#ifndef BOOST_YAML_DETAIL_YAML_IMPL_HPP
#define BOOST_YAML_DETAIL_YAML_IMPL_HPP

#include <boost/yaml/yaml_fwd.hpp>

#include <boost/text/algorithm.hpp>
#include <boost/text/transcode_view.hpp>

#include <iomanip>
#include <iostream>


namespace boost { namespace yaml { namespace detail {

    template<typename T>
    using to_yamlable = decltype(
        to_yaml(std::declval<std::ostream &>(), std::declval<T const &>()));

    template<typename T>
    std::ostream & call_to_yaml(std::ostream & os, T const & x, std::true_type)
    {
        return to_yaml(os, x);
    }

    template<typename T>
    std::ostream & call_to_yaml(std::ostream & os, T const & x, std::false_type)
    {
        return os << "[[UNPRINTABLE]]";
    }

    template<typename T>
    struct value_impl : value_impl_base
    {
        value_impl(T && x) : value_(std::move(x)) {}

        virtual std::unique_ptr<value_impl_base> copy_impl() const override
        {
            return std::unique_ptr<value_impl_base>(new value_impl(*this));
        }

        virtual value_kind kind() const noexcept override
        {
            return value_kind::user_defined;
        }

        virtual bool equal_impl(value const & rhs) const noexcept override
        {
            return value_ == get<T>(rhs);
        }

        virtual std::ostream & to_yaml_impl(std::ostream & os) const
            noexcept override
        {
            return call_to_yaml(os, value_, is_detected<to_yamlable, T>{});
        }

        virtual typeindex::type_index type_id() const noexcept override
        {
            return typeindex::type_id<T>();
        }

        virtual std::size_t hash_append_impl(std::size_t seed) const
            noexcept override
        {
            return hash_append(seed, value_);
        }

        T value_;
    };

    template<>
    struct value_impl<map> : value_impl_base
    {
        template<typename Iter>
        value_impl(Iter first, Iter last) : value_(first, last)
        {}
        value_impl(map && m) : value_(std::move(m)) {}

        virtual std::unique_ptr<value_impl_base> copy_impl() const override
        {
            return std::unique_ptr<value_impl_base>(new value_impl<map>(*this));
        }

        virtual value_kind kind() const noexcept override
        {
            return value_kind::map;
        }

        virtual bool equal_impl(value const & rhs) const noexcept override;

        virtual std::ostream & to_yaml_impl(std::ostream & os) const
            noexcept override;

        virtual typeindex::type_index type_id() const noexcept override
        {
            return typeindex::type_id<map>();
        }

        map value_;
    };

    template<>
    struct value_impl<seq> : value_impl_base
    {
        template<typename Iter>
        value_impl(Iter first, Iter last) : value_(first, last)
        {}
        value_impl(seq && s) : value_(std::move(s)) {}

        virtual std::unique_ptr<value_impl_base> copy_impl() const override
        {
            return std::unique_ptr<value_impl_base>(new value_impl<seq>(*this));
        }

        virtual value_kind kind() const noexcept override
        {
            return value_kind::seq;
        }

        virtual bool equal_impl(value const & rhs) const noexcept override;

        virtual std::ostream & to_yaml_impl(std::ostream & os) const
            noexcept override;

        virtual typeindex::type_index type_id() const noexcept override
        {
            return typeindex::type_id<seq>();
        }

        seq value_;
    };

    template<typename CPSubRange>
    std::ostream & write_escaped_cps(std::ostream & os, CPSubRange subr)
    {
        // TODO: This is JSON specific!
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
    to_yaml_impl(std::ostream & os, std::string_view s) noexcept
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

        virtual bool equal_impl(value const & rhs) const noexcept override;

        virtual std::ostream & to_yaml_impl(std::ostream & os) const
            noexcept override
        {
            return detail::to_yaml_impl(os, value_);
        }

        virtual typeindex::type_index type_id() const noexcept override
        {
            return typeindex::type_id<std::string>();
        }

        std::string value_;
    };

    template<>
    struct value_impl<alias> : value_impl_base
    {
        value_impl(alias && a) : value_(std::move(a)) {}

        virtual std::unique_ptr<value_impl_base> copy_impl() const override
        {
            return std::unique_ptr<value_impl_base>(
                new value_impl<alias>(*this));
        }

        virtual value_kind kind() const noexcept override
        {
            return value_kind::alias;
        }

        virtual bool equal_impl(value const &) const noexcept override
        {
            return true;
        }

        virtual std::ostream & to_yaml_impl(std::ostream & os) const
            noexcept override;

        virtual typeindex::type_index type_id() const noexcept override
        {
            return typeindex::type_id<alias>();
        }

        alias value_;
    };

    template<>
    struct value_impl<property_node> : value_impl_base
    {
        value_impl(property_node && pn) : value_(std::move(pn)) {}

        virtual std::unique_ptr<value_impl_base> copy_impl() const override
        {
            return std::unique_ptr<value_impl_base>(
                new value_impl<property_node>(*this));
        }

        virtual value_kind kind() const noexcept override
        {
            return value_kind::property_node;
        }

        virtual bool equal_impl(value const &) const noexcept override
        {
            return true;
        }

        virtual std::ostream & to_yaml_impl(std::ostream & os) const
            noexcept override;

        virtual typeindex::type_index type_id() const noexcept override
        {
            return typeindex::type_id<property_node>();
        }

        property_node value_;
    };

}}}

#endif
