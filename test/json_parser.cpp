#define BOOST_SPIRIT_X3_NO_FILESYSTEM // TODO
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/char/unicode.hpp>
#include <boost/spirit/home/x3/support/utility/error_reporting.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/text/algorithm.hpp>
#include <boost/text/utility.hpp>

#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace boost { namespace json {

    struct value;

    enum class value_kind { object, array, number, string, boolean, null };

    struct null_t
    {};

    namespace detail {

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
    }

    template<typename T>
    T const & get(value const & v) noexcept;
    template<typename T>
    T & get(value & v) noexcept;

    using array = std::vector<value>;
    using object = std::unordered_map<std::string, value>;

    // TODO: operator==().
    struct value
    {
        value();

        value(value const & other)
        {
            if (other.ptr_)
                ptr_ = other.ptr_->copy_impl();
        }

        value & operator=(value const & other)
        {
            ptr_.reset();
            if (other.ptr_)
                ptr_ = other.ptr_->copy_impl();
            return *this;
        }

        template<typename JSONObject>
        value(
            JSONObject const & o,
            typename std::enable_if<detail::is_object<JSONObject>::value>::
                type ** enable = nullptr);

        template<typename JSONArray>
        value(
            JSONArray const & a,
            typename std::enable_if<detail::is_array<JSONArray>::value>::type **
                enable = nullptr);

        value(double d);

        template<typename String>
        value(
            String const & str,
            typename std::enable_if<detail::is_string<String>::value>::type **
                enable = nullptr);
        value(std::string && str);
        value(char const * c_str);

        value(bool b);

        value(null_t);

        template<typename JSONObject>
        typename std::enable_if<detail::is_object<JSONObject>::value, value &>::
            type
            operator=(JSONObject const & o);

        template<typename JSONArray>
        typename std::enable_if<detail::is_array<JSONArray>::value, value &>::
            type
            operator=(JSONArray const & a);

        value & operator=(double d);

        template<typename String>
        typename std::enable_if<detail::is_string<String>::value, value &>::type
        operator=(String const & str);
        value & operator=(std::string && str);
        value & operator=(char const * c_str);

        value & operator=(bool b);

        value & operator=(null_t);

        value_kind kind() const noexcept { return ptr_->kind(); }

        bool is_object() const noexcept
        {
            return ptr_->kind() == value_kind::object;
        }

        bool is_array() const noexcept
        {
            return ptr_->kind() == value_kind::array;
        }

        bool is_number() const noexcept
        {
            return ptr_->kind() == value_kind::number;
        }

        bool is_string() const noexcept
        {
            return ptr_->kind() == value_kind::string;
        }

        bool is_boolean() const noexcept
        {
            return ptr_->kind() == value_kind::boolean;
        }

        bool is_null() const noexcept
        {
            return ptr_->kind() == value_kind::null;
        }

        template<typename T>
        friend T const & get(value const & v) noexcept;
        template<typename T>
        friend T & get(value & v) noexcept;

        friend std::ostream & operator<<(std::ostream & os, value const & value)
        {
            return value.ptr_->to_json(os);
        }

    private:
        std::unique_ptr<detail::value_impl_base> ptr_;
    };

    namespace detail {

        template<typename...>
        struct void_
        {
            using type = void;
        };

        template<typename... T>
        using void_t = typename void_<T...>::type;

        template<typename T>
        using remove_cv_ref_t = typename std::remove_cv<
            typename std::remove_reference<T>::type>::type;

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
            ((std::is_same<remove_cv_ref_t<detected_t<has_begin, T>>, U>::
                  value ||
              std::is_same<remove_cv_ref_t<detected_t<has_begin, T>>, V>::
                  value) &&
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
                noexcept override
            {
                // TODO: Indentation.
                os << '{';
                bool first = true;
                for (auto const & pair : value_) {
                    if (!first)
                        os << ", ";
                    os << '"' << pair.first << "\": " << pair.second;
                    first = false;
                }
                os << '}';
                return os;
            }

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
                noexcept override
            {
                // TODO: Indentation.
                os << '[';
                bool first = true;
                for (auto const & value : value_) {
                    if (!first)
                        os << ", ";
                    os << value;
                    first = false;
                }
                os << ']';
                return os;
            }

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
    }

    inline value::value() { *this = null_t{}; }

    template<typename JSONObject>
    value::value(
        JSONObject const & o,
        typename std::enable_if<detail::is_object<JSONObject>::value>::type **
            enable) :
        ptr_(new detail::value_impl<object>(o.begin(), o.end()))
    {}

    template<typename JSONArray>
    value::value(
        JSONArray const & a,
        typename std::enable_if<detail::is_array<JSONArray>::value>::type **
            enable) :
        ptr_(new detail::value_impl<array>(a.begin(), a.end()))
    {}

    inline value::value(double d) : ptr_(new detail::value_impl<double>(d)) {}

    inline value::value(std::string && s) :
        ptr_(new detail::value_impl<std::string>{std::move(s)})
    {}

    inline value::value(char const * c_str) : value(std::string(c_str)) {}

    template<typename String>
    value::value(
        String const & str,
        typename std::enable_if<detail::is_string<String>::value>::type **
            enable) :
        value(std::string(std::begin(str), std::end(str)))
    {}

    inline value::value(bool b) : ptr_(new detail::value_impl<bool>(b)) {}

    inline value::value(null_t) : ptr_(new detail::value_impl<null_t>) {}

    template<typename JSONObject>
    typename std::enable_if<detail::is_object<JSONObject>::value, value &>::type
    value::operator=(JSONObject const & object)
    {
        return *this = value(object);
    }

    template<typename JSONArray>
    typename std::enable_if<detail::is_array<JSONArray>::value, value &>::type
    value::operator=(JSONArray const & object)
    {
        return *this = value(object);
    }

    inline value & value::operator=(double d) { return *this = value(d); }

    inline value & value::operator=(std::string && s)
    {
        return *this = value(std::move(s));
    }

    inline value & value::operator=(char const * c_str)
    {
        return *this = value(std::string(c_str));
    }

    template<typename String>
    typename std::enable_if<detail::is_string<String>::value, value &>::type
    value::operator=(String const & str)
    {
        return *this = value(std::string(std::begin(str), std::end(str)));
    }

    inline value & value::operator=(bool b) { return *this = value(b); }

    inline value & value::operator=(null_t) { return *this = value(null_t{}); }

    template<>
    inline object const & get<object>(value const & v) noexcept
    {
        assert(v.is_object());
        return static_cast<detail::value_impl<object> *>(v.ptr_.get())->value_;
    }

    template<>
    inline array const & get<array>(value const & v) noexcept
    {
        assert(v.is_array());
        return static_cast<detail::value_impl<array> *>(v.ptr_.get())->value_;
    }

    template<>
    inline double const & get<double>(value const & v) noexcept
    {
        assert(v.is_number());
        return static_cast<detail::value_impl<double> *>(v.ptr_.get())->value_;
    }

    template<>
    inline std::string const & get<std::string>(value const & v) noexcept
    {
        assert(v.is_string());
        return static_cast<detail::value_impl<std::string> *>(v.ptr_.get())
            ->value_;
    }

    template<>
    inline bool const & get<bool>(value const & v) noexcept
    {
        assert(v.is_boolean());
        return static_cast<detail::value_impl<bool> *>(v.ptr_.get())->value_;
    }

    template<>
    inline null_t const & get<null_t>(value const & v) noexcept
    {
        assert(v.is_null());
        return static_cast<detail::value_impl<null_t> *>(v.ptr_.get())->value_;
    }

    template<>
    inline object & get<object>(value & v) noexcept
    {
        assert(v.is_object());
        return static_cast<detail::value_impl<object> *>(v.ptr_.get())->value_;
    }

    template<>
    inline array & get<array>(value & v) noexcept
    {
        assert(v.is_array());
        return static_cast<detail::value_impl<array> *>(v.ptr_.get())->value_;
    }

    template<>
    inline double & get<double>(value & v) noexcept
    {
        assert(v.is_number());
        return static_cast<detail::value_impl<double> *>(v.ptr_.get())->value_;
    }

    template<>
    inline std::string & get<std::string>(value & v) noexcept
    {
        assert(v.is_string());
        return static_cast<detail::value_impl<std::string> *>(v.ptr_.get())
            ->value_;
    }

    template<>
    inline bool & get<bool>(value & v) noexcept
    {
        assert(v.is_boolean());
        return static_cast<detail::value_impl<bool> *>(v.ptr_.get())->value_;
    }

    template<>
    inline null_t & get<null_t>(value & v) noexcept
    {
        assert(v.is_null());
        return static_cast<detail::value_impl<null_t> *>(v.ptr_.get())->value_;
    }

    // parsing

    namespace x3 = boost::spirit::x3;
    namespace ascii = boost::spirit::x3::ascii;

    x3::rule<class ws, std::string> const ws = "whitespace";
    auto const ws_def = x3::lit('\x09') | '\x0a' | '\x0d' | '\x20';
    BOOST_SPIRIT_DEFINE(ws);

    auto append_utf8 = [](auto & ctx) {
        std::array<uint32_t, 1> const cps = {{_attr(ctx)}};
        auto const r = boost::text::make_from_utf32_range(cps);
        std::string & str = _val(ctx);
        str.insert(str.end(), r.begin(), r.end());
    };

    auto object_init = [](auto & ctx) { _val(ctx) = object(); };
    auto object_insert = [](auto & ctx) {
        value & v = _val(ctx);
        get<object>(v).insert(std::make_pair(
            std::move(boost::fusion::at_c<0>(_attr(ctx))),
            std::move(boost::fusion::at_c<1>(_attr(ctx)))));
    };
    auto array_init = [](auto & ctx) { _val(ctx) = array(); };
    auto array_append = [](auto & ctx) {
        value & v = _val(ctx);
        get<array>(v).push_back(std::move(_attr(ctx)));
    };

    struct first_surrogate_tag
    {};

    auto first_hex_escape = [](auto & ctx) {
        uint32_t const cu = _attr(ctx);
        if (!boost::text::utf8::high_surrogate(cu))
            _pass(ctx) = false;
        else
            x3::get<first_surrogate_tag>(ctx).get() = cu;
    };
    auto second_hex_escape = [](auto & ctx) {
        uint32_t const cu = _attr(ctx);
        if (!boost::text::utf8::low_surrogate(cu)) {
            _pass(ctx) = false;
        } else {
            uint32_t const high_surrogate_min = 0xd800;
            uint32_t const low_surrogate_min = 0xdc00;
            uint32_t const surrogate_offset =
                0x10000 - (high_surrogate_min << 10) - low_surrogate_min;
            uint32_t const first_cu = x3::get<first_surrogate_tag>(ctx).get();
            _val(ctx) = (first_cu << 10) + cu + surrogate_offset;
        }
    };

    x3::rule<class string_char, uint32_t> const string_char =
        "code point (code points <= U+001F must be escaped)";
    x3::rule<class hex_digit, char> const hex_digit = "hexidecimal digit";
    x3::rule<class four_hex_digits, char> const four_hex_digits =
        "four hexidecimal digits";
    x3::rule<class escape_seq, uint32_t> const escape_seq =
        "\\uXXXX hexidecimal escape sequence";
    x3::rule<class escape_double_seq, uint32_t> const escape_double_seq =
        "\\uXXXX hexidecimal escape sequence";
    x3::rule<class single_escaped_char, uint32_t> const single_escaped_char =
        "\", \\, /, b, f, n, r, or t";

    auto const hex_digit_def = x3::ascii::xdigit;
    BOOST_SPIRIT_DEFINE(hex_digit);

    auto const four_hex_digits_def = &x3::repeat(4)[hex_digit];
    BOOST_SPIRIT_DEFINE(four_hex_digits);

    auto const escape_seq_def = (x3::lit("\\u") > four_hex_digits) >> x3::hex;
    BOOST_SPIRIT_DEFINE(escape_seq);

    auto const escape_double_seq_def =
        escape_seq[first_hex_escape] >> escape_seq[second_hex_escape];
    BOOST_SPIRIT_DEFINE(escape_double_seq);

    auto const single_escaped_char_def =
        x3::lit('"') >> x3::attr(0x0022u) | x3::lit('\\') >> x3::attr(0x005cu) |
        x3::lit('/') >> x3::attr(0x002fu) | x3::lit('b') >> x3::attr(0x0008u) |
        x3::lit('f') >> x3::attr(0x000cu) | x3::lit('n') >> x3::attr(0x000au) |
        x3::lit('r') >> x3::attr(0x000du) | x3::lit('t') >> x3::attr(0x0009u);
    BOOST_SPIRIT_DEFINE(single_escaped_char);

    auto const string_char_def = escape_double_seq | escape_seq |
                                 x3::lit('\\') > single_escaped_char |
                                 (x3::unicode::char_ -
                                  x3::unicode::char_(0x0000u, 0x001fu));
    BOOST_SPIRIT_DEFINE(string_char);

    x3::rule<class null, value> const null = "null";
    x3::rule<class string, std::string> const string = "string";
    x3::rule<class object_element, std::pair<std::string, value>> const
        object_element = "object_element";
    x3::rule<class object_tag, value> const object_p = "object";
    x3::rule<class array_tag, value> const array_p = "array";

    struct value_parser_struct;
    x3::rule<value_parser_struct, value> const value_p = "value";

    auto const null_def = x3::lit("null") >> x3::attr(value());
    BOOST_SPIRIT_DEFINE(null);

    auto const string_def =
        x3::lit('"') >> x3::lexeme[*(string_char[append_utf8] - '"')] > '"';
    BOOST_SPIRIT_DEFINE(string);

    auto const object_element_def = string > ':' > value_p;
    BOOST_SPIRIT_DEFINE(object_element);

    auto const object_p_def = x3::lit('{')[object_init] >>
                              -(object_element[object_insert] % ',') > '}';
    BOOST_SPIRIT_DEFINE(object_p);

    auto const array_p_def = x3::lit('[')[array_init] >>
                             -(value_p[array_append] % ',') > ']';
    BOOST_SPIRIT_DEFINE(array_p);

    auto const value_p_def =
        x3::double_ | x3::bool_ | null | string | array_p | object_p;
    BOOST_SPIRIT_DEFINE(value_p);

    struct error_handler_base
    {
        template<typename Iterator, typename Exception, typename Context>
        x3::error_handler_result on_error(
            Iterator & first,
            Iterator const & last,
            Exception const & e,
            Context const & ctx)
        {
            auto & error_handler = x3::get<x3::error_handler_tag>(ctx).get();
            std::string message = "Error! Expecting: " + e.which() + " here:";
            error_handler(e.where(), message);
            return x3::error_handler_result::fail;
        }
    };

    struct value_parser_struct : error_handler_base
    {};

    template<typename CPRange>
    boost::optional<value> parse(CPRange const & range)
    {
        using iter_t = decltype(range.begin());
        auto first = range.begin();
        auto const last = range.end();

        // TODO: Emit the error via a callback instead of jsut dumping it to
        // the console.
        x3::error_handler<iter_t> error_handler{first, last, std::cout};
        uint32_t first_surrogate = 0;

        auto parser = x3::with<x3::error_handler_tag>(
            std::ref(error_handler))[x3::with<first_surrogate_tag>(
            std::ref(first_surrogate))[value_p]];

        value v;
        bool const result = x3::phrase_parse(first, last, parser, ws, v);

        if (!result || first != last)
            return {};

        return boost::optional<value>(std::move(v));
    }

}}

int main()
{
    std::string str;
    while (getline(std::cin, str)) {
        if (str.empty())
            break;

        auto const range = boost::text::make_to_utf32_range(str);
        boost::optional<boost::json::value> value;
        if (value = boost::json::parse(range)) {
            std::cout << "Parsed value:\n";
            std::cout << *value << std::endl;
        }
    }

    return 0;
}