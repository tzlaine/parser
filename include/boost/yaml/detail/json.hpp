#ifndef BOOST_YAML_DETAIL_JSON_HPP
#define BOOST_YAML_DETAIL_JSON_HPP

#include <boost/yaml/json_fwd.hpp>

#include <boost/text/algorithm.hpp>
#include <boost/text/utility.hpp>

#include <iomanip>
#include <iostream>


namespace boost { namespace json { namespace detail {

    template<typename T>
    struct is_object;

    template<typename T>
    struct is_array;

    template<typename T>
    struct is_string;

    struct value_impl_base
    {
        virtual ~value_impl_base() = 0;

        virtual std::unique_ptr<value_impl_base> copy_impl() const = 0;

        virtual value_kind kind() const noexcept = 0;

        virtual std::ostream & to_json(std::ostream & os) const noexcept = 0;
    };

    inline value_impl_base::~value_impl_base() {}

    template<typename T>
    struct value_impl;

    // TODO: Use this, and put objects (unordered_maps) on the heap, in
    // the implementation of jason_value_impl below.
    constexpr int value_buffer_size()
    {
        return (std::max)(sizeof(std::vector<int>), sizeof(std::string));
    }

    template<typename...>
    struct void_
    {
        using type = void;
    };

    template<typename... T>
    using void_t = typename void_<T...>::type;

    template<typename T>
    using remove_cv_ref_t =
        typename std::remove_cv<typename std::remove_reference<T>::type>::type;

    struct nonesuch
    {};

    template<
        typename Default,
        typename AlwaysVoid,
        template<typename...> class Template,
        typename... Args>
    struct detector
    {
        using value_t = std::false_type;
        using type = Default;
    };

    template<
        typename Default,
        template<typename...> class Template,
        typename... Args>
    struct detector<Default, void_t<Template<Args...>>, Template, Args...>
    {
        using value_t = std::true_type;
        using type = Template<Args...>;
    };

    template<template<typename...> class Template, typename... Args>
    using is_detected =
        typename detector<nonesuch, void, Template, Args...>::value_t;

    template<template<typename...> class Template, typename... Args>
    using detected_t =
        typename detector<nonesuch, void, Template, Args...>::type;

    template<
        typename Default,
        template<typename...> class Template,
        typename... Args>
    using detected_or =
        typename detector<Default, void, Template, Args...>::type;



    template<typename T>
    using has_begin = decltype(*std::begin(std::declval<T>()));
    template<typename T>
    using has_end = decltype(*std::end(std::declval<T>()));


    template<typename T, typename U, typename V = U>
    using is_range_of = std::integral_constant<
        bool,
        ((std::is_same<remove_cv_ref_t<detected_t<has_begin, T>>, U>::value ||
          std::is_same<remove_cv_ref_t<detected_t<has_begin, T>>, V>::value) &&
         is_detected<has_end, T>::value)>;

    template<typename T>
    struct is_object : is_range_of<
                           T,
                           std::pair<std::string, value>,
                           std::pair<std::string const, value>>
    {
    };

    template<typename T>
    struct is_array : is_range_of<T, value>
    {
    };

    template<typename T, typename BeginValueType>
    using is_range_of_char = std::integral_constant<
        bool,
        (std::is_convertible<BeginValueType, const char>::value &&
         sizeof(BeginValueType) == 1 && is_detected<has_end, T>::value)>;

    template<typename T>
    struct is_string
        : is_range_of_char<T, remove_cv_ref_t<detected_t<has_begin, T>>>
    {
    };

    template<>
    struct value_impl<object> : value_impl_base
    {
        template<typename Iter>
        value_impl(Iter first, Iter last) : value_(first, last)
        {}

        virtual std::unique_ptr<value_impl_base> copy_impl() const override
        {
            return std::unique_ptr<value_impl_base>(
                new value_impl<object>(*this));
        }

        virtual value_kind kind() const noexcept override
        {
            return value_kind::object;
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

        virtual std::unique_ptr<value_impl_base> copy_impl() const override
        {
            return std::unique_ptr<value_impl_base>(
                new value_impl<array>(*this));
        }

        virtual value_kind kind() const noexcept override
        {
            return value_kind::array;
        }

        virtual std::ostream & to_json(std::ostream & os) const
            noexcept override;

        array value_;
    };

    template<>
    struct value_impl<double> : value_impl_base
    {
        value_impl(double d) : value_(d) {}

        virtual std::unique_ptr<value_impl_base> copy_impl() const override
        {
            return std::unique_ptr<value_impl_base>(
                new value_impl<double>(*this));
        }

        virtual value_kind kind() const noexcept override
        {
            return value_kind::number;
        }

        virtual std::ostream & to_json(std::ostream & os) const
            noexcept override
        {
            return os << value_;
        }

        double value_;
    };

    template<>
    struct value_impl<std::string> : value_impl_base
    {
        value_impl(std::string && s) : value_(std::move(s)) {}

        virtual std::unique_ptr<value_impl_base> copy_impl() const override
        {
            return std::unique_ptr<value_impl_base>(
                new value_impl<std::string>(*this));
        }

        virtual value_kind kind() const noexcept override
        {
            return value_kind::string;
        }

        template<typename CPSubRange>
        static std::ostream &
        write_escaped_cps(std::ostream & os, CPSubRange subr)
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
                        auto const hi = static_cast<uint16_t>(cp >> 10) +
                                        high_surrogate_base;
                        auto const lo = static_cast<uint16_t>(cp & 0x3ff) +
                                        low_surrogate_base;
                        os << "\\u" << std::setw(4) << hi;
                        os << "\\u" << std::setw(4) << lo;
                    }
                    break;
                }
            }
            os << std::dec;
            return os;
        }

        virtual std::ostream & to_json(std::ostream & os) const
            noexcept override
        {
            os << '"';
            auto const r = boost::text::make_to_utf32_range(value_);
            char const * last_written_it = &*value_.begin();
            boost::text::foreach_subrange_if(
                r.begin(),
                r.end(),
                [](uint32_t cp) { return cp < 0x0020 || 0xffff < cp; },
                [&](auto subr) {
                    os.write(
                        last_written_it,
                        &*subr.begin().base() - last_written_it);
                    write_escaped_cps(os, subr);
                    last_written_it = &*subr.end().base();
                });
            os.write(last_written_it, &*value_.end() - last_written_it);
            os << '"';
            return os;
        }

        std::string value_;
    };

    template<>
    struct value_impl<bool> : value_impl_base
    {
        value_impl(bool b) : value_(b) {}

        virtual std::unique_ptr<value_impl_base> copy_impl() const override
        {
            return std::unique_ptr<value_impl_base>(
                new value_impl<bool>(*this));
        }

        virtual value_kind kind() const noexcept override
        {
            return value_kind::boolean;
        }

        virtual std::ostream & to_json(std::ostream & os) const
            noexcept override
        {
            return os << (value_ ? "true" : "false");
        }

        bool value_;
    };

    template<>
    struct value_impl<null_t> : value_impl_base
    {
        value_impl() {}
        value_impl(null_t) {}

        virtual std::unique_ptr<value_impl_base> copy_impl() const override
        {
            return std::unique_ptr<value_impl_base>(
                new value_impl<null_t>(*this));
        }

        virtual value_kind kind() const noexcept override
        {
            return value_kind::null;
        }

        virtual std::ostream & to_json(std::ostream & os) const
            noexcept override
        {
            return os << "null";
        }

        null_t value_;
    };

}}}

#endif
