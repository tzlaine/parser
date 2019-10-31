#include <boost/yaml/json.hpp>
#include <boost/yaml/exception.hpp>
#include <boost/parser/parser.hpp>

#include <boost/container/small_vector.hpp>


namespace boost { namespace json {

    namespace bp = ::boost::parser;
    using namespace bp::literals;

    struct global_state
    {
        int recursive_open_count = 0;
        int max_recursive_open_count = 0;
    };

    struct double_escape_locals
    {
        int first_surrogate = 0;
    };


    bp::rule<class ws> const ws = "whitespace";

    bp::rule<class string_char, uint32_t> const string_char =
        "code point (code points <= U+001F must be escaped)";
    bp::rule<class four_hex_digits, uint32_t> const hex_4 =
        "four hexidecimal digits";
    bp::rule<class escape_seq, uint32_t> const escape_seq =
        "\\uXXXX hexidecimal escape sequence";
    bp::rule<class escape_double_seq, uint32_t, double_escape_locals> const
        escape_double_seq = "\\uXXXX hexidecimal escape sequence";
    bp::rule<class single_escaped_char, uint32_t> const single_escaped_char =
        "'\"', '\\', '/', 'b', 'f', 'n', 'r', or 't'";

    bp::rule<class null, value> const null = "null";
    bp::rule<class string, std::string> const string = "string";
    bp::rule<class number, double> const number = "number";
    bp::rule<class object_element, hana::tuple<std::string, value>> const
        object_element = "object-element";
    bp::rule<class object_tag, value> const object_p = "object";
    bp::rule<class array_tag, value> const array_p = "array";

    bp::rule<class value_tag, value> const value_p = "value";



    auto const ws_def = '\x09'_l | '\x0a' | '\x0d' | '\x20';

    auto object_init = [](auto & ctx) {
        auto & globals = _globals(ctx);
        if (globals.max_recursive_open_count < ++globals.recursive_open_count)
            throw yaml::excessive_nesting(_where(ctx).begin());
        _val(ctx) = object();
    };
    auto object_insert = [](auto & ctx) {
        using namespace hana::literals;
        value & v = _val(ctx);
        get<object>(v).insert(std::make_pair(
            std::move(_attr(ctx))[0_c], std::move(_attr(ctx)[1_c])));
    };
    auto array_init = [](auto & ctx) {
        auto & globals = _globals(ctx);
        if (globals.max_recursive_open_count < ++globals.recursive_open_count)
            throw yaml::excessive_nesting(_where(ctx).begin());
        _val(ctx) = array();
    };
    auto array_append = [](auto & ctx) {
        value & v = _val(ctx);
        get<array>(v).push_back(std::move(_attr(ctx)));
    };

    auto first_hex_escape = [](auto & ctx) {
        auto & locals = _locals(ctx);
        uint32_t const cu = _attr(ctx);
        if (!text::utf8::high_surrogate(cu))
            _pass(ctx) = false;
        else
            locals.first_surrogate = cu;
    };
    auto second_hex_escape = [](auto & ctx) {
        auto & locals = _locals(ctx);
        uint32_t const cu = _attr(ctx);
        if (!text::utf8::low_surrogate(cu)) {
            _pass(ctx) = false;
        } else {
            uint32_t const high_surrogate_min = 0xd800;
            uint32_t const low_surrogate_min = 0xdc00;
            uint32_t const surrogate_offset =
                0x10000 - (high_surrogate_min << 10) - low_surrogate_min;
            uint32_t const first_cu = locals.first_surrogate;
            _val(ctx) = (first_cu << 10) + cu + surrogate_offset;
        }
    };

    bp::parser_interface<bp::uint_parser<uint32_t, 16, 4, 4>> const hex_4_def;

    auto const escape_seq_def = "\\u" > hex_4;

    auto const escape_double_seq_def =
        escape_seq[first_hex_escape] >> escape_seq[second_hex_escape];

    bp::symbols<uint32_t> const single_escaped_char_def = {{"\"", 0x0022u},
                                                           {"\\", 0x005cu},
                                                           {"/", 0x002fu},
                                                           {"b", 0x0008u},
                                                           {"f", 0x000cu},
                                                           {"n", 0x000au},
                                                           {"r", 0x000du},
                                                           {"t", 0x0009u}};

    auto const string_char_def = escape_double_seq | escape_seq |
                                 '\\'_l > single_escaped_char |
                                 (bp::cp - bp::char_(0x0000u, 0x001fu));

    auto const null_def = "null" >> bp::attr(value());

    auto const string_def = bp::lexeme['"' >> *(string_char - '"') > '"'];

    // TODO: Test very long strings of digits before and after the 'e/E+/-'.
    auto parse_double = [](auto & ctx) {
        auto const cp_range = _attr(ctx);
        auto cp_first = cp_range.begin();
        auto const cp_last = cp_range.end();

        auto const result = bp::parse(cp_first, cp_last, bp::double_);
        if (result) {
            _val(ctx) = *result;
        } else {
            container::small_vector<char, 128> chars(cp_first, cp_last);
            auto const chars_first = &*chars.begin();
            auto chars_last = chars_first + chars.size();
            _val(ctx) = std::strtod(chars_first, &chars_last);
        }
    };

    auto const number_def = bp::raw
        [bp::lexeme
             [-bp::char_('-') >>
              (bp::char_('1', '9') >> *bp::ascii::digit | bp::char_('0')) >>
              -(bp::char_('.') >> +bp::ascii::digit) >>
              -(bp::char_("eE") >> -bp::char_("+-") >> +bp::ascii::digit)]]
        [parse_double];

    auto const object_element_def = string > ':' > value_p;

    auto const object_p_def = '{'_l[object_init] >>
                              -(object_element[object_insert] % ',') > '}';

    auto const array_p_def = '['_l[array_init] >>
                             -(value_p[array_append] % ',') > ']';

    auto const value_p_def =
        number | bp::bool_ | null | string | array_p | object_p;

    BOOST_PARSER_DEFINE_RULES(
        ws,
        hex_4,
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

    // TODO: This needs to change; it cannot parse a rope; there should also
    // be interfaces that accept CPIters and CPRanges.
    std::optional<value> parse(
        string_view str, diagnostic_function errors_callback, int max_recursion)
    {
        auto const range = text::make_to_utf32_range(str);
        using iter_t = decltype(range.begin());
        auto first = range.begin();
        auto const last = range.end();

        if (max_recursion <= 0)
            max_recursion = INT_MAX;

        global_state globals{0, max_recursion};
        bp::callback_error_handler error_handler(errors_callback);
        auto const parser = bp::with_error_handler(
            bp::with_globals(value_p, globals), error_handler);

        try {
            value val;
            bool const success = bp::skip_parse(first, last, parser, ws, val);
            if (!success || first != last)
                return {};
            return std::optional<value>(std::move(val));
        } catch (yaml::excessive_nesting<iter_t> const & e) {
            if (errors_callback) {
                std::string const message = "error: Exceeded maximum number (" +
                                            std::to_string(max_recursion) +
                                            ") of open arrays and/or objects";
                std::stringstream ss;
                bp::write_formatted_message(
                    ss, "", range.begin(), e.iter, last, message);
                errors_callback(ss.str());
            }
        }

        return {};
    }

}}
