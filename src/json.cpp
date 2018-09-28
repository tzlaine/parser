#define BOOST_SPIRIT_X3_NO_FILESYSTEM // TODO
#include <boost/yaml/json.hpp>

#include <boost/fusion/include/std_pair.hpp>
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/char/unicode.hpp>
#include <boost/spirit/home/x3/support/utility/error_reporting.hpp>


namespace boost { namespace json {

    namespace x3 = boost::spirit::x3;

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

    boost::optional<value> parse(boost::string_view const & str)
    {
        auto const range = boost::text::make_to_utf32_range(str);
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