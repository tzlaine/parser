// Define this to turn on a verbose trace of the parse.
//#define BOOST_SPIRIT_X3_DEBUG

#include <boost/yaml/json.hpp>
#include <boost/yaml/parser/x3_error_reporting.hpp>

#include <boost/container/small_vector.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/spirit/home/x3/char/unicode.hpp>


#ifdef BOOST_SPIRIT_X3_DEBUG
namespace boost { namespace spirit { namespace x3 { namespace detail {

    // Used in simple_trace to print a single character of the parsed stream;
    // specialized here for code points.
    template<>
    inline void token_printer<uint32_t>(std::ostream & os, uint32_t cp)
    {
        if (cp < 0x0020) {
            os << "\\u" << std::hex << std::setw(4) << std::setfill('0') << cp
               << std::dec;
        } else {
            uint32_t cps[1] = {cp};
            char cus[5] = {0};
            std::copy(
                text::utf8::make_from_utf32_iterator(cps, cps, cps + 1),
                text::utf8::make_from_utf32_iterator(cps, cps + 1, cps + 1),
                cus);
            os << cus;
        }
    }

}}}}
#endif

namespace boost { namespace json {

    namespace x3 = spirit::x3;

    x3::rule<class ws, std::string> const ws = "whitespace";
    auto const ws_def = x3::lit('\x09') | '\x0a' | '\x0d' | '\x20';

    auto append_utf8 = [](auto & ctx) {
        std::array<uint32_t, 1> const cps = {{_attr(ctx)}};
        auto const r = text::make_from_utf32_range(cps);
        std::string & str = _val(ctx);
        str.insert(str.end(), r.begin(), r.end());
    };

    struct recursive_open_count_tag;
    struct max_recursive_open_count_tag;

    auto object_init = [](auto & ctx) {
        int & recursive_open_count =
            x3::get<recursive_open_count_tag>(ctx).get();
        int const max_recursive_open_count =
            x3::get<max_recursive_open_count_tag>(ctx);
        if (max_recursive_open_count < ++recursive_open_count)
            _pass(ctx) = false;
        else
            _val(ctx) = object();
    };
    auto object_insert = [](auto & ctx) {
        value & v = _val(ctx);
        get<object>(v).insert(std::make_pair(
            std::move(fusion::at_c<0>(_attr(ctx))),
            std::move(fusion::at_c<1>(_attr(ctx)))));
    };
    auto array_init = [](auto & ctx) {
        int & recursive_open_count =
            x3::get<recursive_open_count_tag>(ctx).get();
        int const max_recursive_open_count =
            x3::get<max_recursive_open_count_tag>(ctx);
        if (max_recursive_open_count < ++recursive_open_count)
            _pass(ctx) = false;
        else
            _val(ctx) = array();
    };
    auto array_append = [](auto & ctx) {
        value & v = _val(ctx);
        get<array>(v).push_back(std::move(_attr(ctx)));
    };

    struct first_surrogate_tag;

    auto first_hex_escape = [](auto & ctx) {
        uint32_t const cu = _attr(ctx);
        if (!text::utf8::high_surrogate(cu))
            _pass(ctx) = false;
        else
            x3::get<first_surrogate_tag>(ctx).get() = cu;
    };
    auto second_hex_escape = [](auto & ctx) {
        uint32_t const cu = _attr(ctx);
        if (!text::utf8::low_surrogate(cu)) {
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
    x3::rule<class four_hex_digits, char> const four_hex_digits =
        "four hexidecimal digits";
    x3::rule<class escape_seq, uint32_t> const escape_seq =
        "\\uXXXX hexidecimal escape sequence";
    x3::rule<class escape_double_seq, uint32_t> const escape_double_seq =
        "\\uXXXX hexidecimal escape sequence";
    x3::rule<class single_escaped_char, uint32_t> const single_escaped_char =
        "'\"', '\\', '/', 'b', 'f', 'n', 'r', or 't'";

    auto const four_hex_digits_def = &x3::repeat(4)[x3::ascii::xdigit];

    auto const escape_seq_def = ("\\u" > four_hex_digits) >> x3::hex;

    auto const escape_double_seq_def =
        escape_seq[first_hex_escape] >> escape_seq[second_hex_escape];

    auto const single_escaped_char_def = '"' >> x3::attr(0x0022u) |
                                         '\\' >> x3::attr(0x005cu) |
                                         '/' >> x3::attr(0x002fu) |
                                         'b' >> x3::attr(0x0008u) |
                                         'f' >> x3::attr(0x000cu) |
                                         'n' >> x3::attr(0x000au) |
                                         'r' >> x3::attr(0x000du) |
                                         't' >> x3::attr(0x0009u);

    auto const string_char_def = escape_double_seq | escape_seq |
                                 x3::lit('\\') > single_escaped_char |
                                 (x3::unicode::char_ -
                                  x3::unicode::char_(0x0000u, 0x001fu));

    x3::rule<class null, value> const null = "null";
    x3::rule<class string, std::string> const string = "string";
    x3::rule<class number, double> const number = "number";
    x3::rule<class object_element, std::pair<std::string, value>> const
        object_element = "object_element";
    x3::rule<class object_tag, value> const object_p = "object";
    x3::rule<class array_tag, value> const array_p = "array";

    struct value_parser_struct;
    x3::rule<value_parser_struct, value> const value_p = "value";

    auto const null_def = "null" >> x3::attr(value());

    auto const string_def =
        x3::lexeme['"' >> *(string_char[append_utf8] - '"') > '"'];

    // TODO: Test very long strings of digits before and after the 'e/E+/-'.
    auto parse_double = [](auto & ctx) {
        auto const cp_range = _attr(ctx);
        auto cp_first = cp_range.begin();
        auto const cp_last = cp_range.end();

        double result;
        if (x3::parse(cp_first, cp_last, x3::double_, result)) {
            _val(ctx) = result;
        } else {
            container::small_vector<char, 128> chars(cp_first, cp_last);
            auto const chars_first = &*chars.begin();
            auto chars_last = chars_first + chars.size();
            _val(ctx) = std::strtod(chars_first, &chars_last);
        }
    };

    auto const number_def = x3::raw
        [x3::lexeme
             [-x3::char_('-') >>
              (x3::char_('1', '9') >> *x3::ascii::digit | x3::char_('0')) >>
              -(x3::char_('.') >> +x3::ascii::digit) >>
              -(x3::char_("eE") >> -x3::char_("+-") >> +x3::ascii::digit)]]
        [parse_double];

    auto const object_element_def = string > ':' > value_p;

    auto const object_p_def = x3::lit('{')[object_init] >>
                              -(object_element[object_insert] % ',') > '}';

    auto const array_p_def = x3::lit('[')[array_init] >>
                             -(value_p[array_append] % ',') > ']';

    auto const value_p_def =
        number | x3::bool_ | null | string | array_p | object_p;

    BOOST_SPIRIT_DEFINE(
        ws,
        four_hex_digits,
        escape_seq,
        escape_double_seq,
        single_escaped_char,
        string_char,
        null,
        string,
        number,
        object_element,
        object_p,
        array_p,
        value_p);

    struct x3_error_handler_base
    {
        template<typename Iterator, typename Exception, typename Context>
        spirit::x3::error_handler_result on_error(
            Iterator & first,
            Iterator const & last,
            Exception const & e,
            Context const & ctx)
        {
            namespace x3 = spirit::x3;
            auto & error_handler = x3::get<yaml::error_handler_tag>(ctx).get();

            int const recursive_open_count =
                x3::get<recursive_open_count_tag>(ctx).get();
            int const max_recursive_open_count =
                x3::get<max_recursive_open_count_tag>(ctx);

            if (max_recursive_open_count < recursive_open_count) {
                return x3::error_handler_result::rethrow;
            } else {
                std::string message = "error: Expected " + e.which() + " here:";
                error_handler(e.where(), message);
                return x3::error_handler_result::fail;
            }
        }
    };

    struct value_parser_struct : x3_error_handler_base
    {};

    // TODO: This needs to change; it cannot parse a rope; there should also
    // be interfaces that accept CPIters and CPRanges.
    optional<value> parse(
        string_view const & str,
        error_function parse_error,
        int max_recursive_count)
    {
        auto const range = text::make_to_utf32_range(str);
        using iter_t = decltype(range.begin());
        auto first = range.begin();
        auto const last = range.end();

        yaml::x3_error_handler<iter_t> error_handler{first, last, parse_error};
        uint32_t first_surrogate = 0;
        int recursive_open_count = 0;

        if (max_recursive_count < 0)
            max_recursive_count = INT_MAX;

        // clang-format off
        auto parser = x3::with<yaml::error_handler_tag>(std::ref(error_handler))[
            x3::with<first_surrogate_tag>(std::ref(first_surrogate))[
                x3::with<recursive_open_count_tag>(std::ref(recursive_open_count))[
                    x3::with<max_recursive_open_count_tag>(max_recursive_count)[
                        value_p
                    ]
                ]
            ]
        ];
        // clang-format on

        value v;
        bool result = false;
        try {
            result = x3::phrase_parse(first, last, parser, ws, v);
        } catch (x3::expectation_failure<iter_t> const & e) {
            std::string message = "error: Exceeded maximum number (" +
                                  std::to_string(max_recursive_count) +
                                  ") of open arrays and/or objects " +
                                  e.which() + " here:";
            error_handler(e.where(), message);
            return {};
        }

        if (!result || first != last)
            return {};

        return optional<value>(std::move(v));
    }

}}
