// Define this to turn on a verbose trace of the parse.
//#define BOOST_SPIRIT_X3_DEBUG

#include <boost/yaml/yaml.hpp>
#include <boost/yaml/parser/x3_error_reporting.hpp>

#include <boost/container/small_vector.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/spirit/home/x3/char/unicode.hpp>
#include <boost/any.hpp>


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

namespace boost { namespace spirit { namespace x3 {

    namespace detail {

        template<typename Fn>
        struct lazy_exact_count // handles repeat(exact)[p]
        {
            typedef int type;

            template<typename Context>
            bool got_max(int i, Context const & ctx) const
            {
                return i >= exact_value(ctx);
            }
            template<typename Context>
            bool got_min(int i, Context const & ctx) const
            {
                return i >= exact_value(ctx);
            }

            Fn exact_value;
        };

        template<typename Fn>
        struct lazy_finite_count // handles repeat(min, max)[p]
        {
            typedef int type;

            template<typename Context>
            bool got_max(int i, Context const & ctx) const
            {
                return i >= max_value(ctx);
            }
            template<typename Context>
            bool got_min(int i, Context const & ctx) const
            {
                return i >= min_value;
            }

            int const min_value;
            Fn max_value;
        };
    }

    template<typename Subject, typename RepeatCountLimit>
    struct lazy_repeat_directive
        : unary_parser<
              Subject,
              lazy_repeat_directive<Subject, RepeatCountLimit>>
    {
        typedef unary_parser<
            Subject,
            lazy_repeat_directive<Subject, RepeatCountLimit>>
            base_type;
        static bool const is_pass_through_unary = true;
        static bool const handles_container = true;

        lazy_repeat_directive(
            Subject const & subject, RepeatCountLimit const & repeat_limit_) :
            base_type(subject),
            repeat_limit(repeat_limit_)
        {}

        template<
            typename Iterator,
            typename Context,
            typename RContext,
            typename Attribute>
        bool parse(
            Iterator & first,
            Iterator const & last,
            Context const & context,
            RContext & rcontext,
            Attribute & attr) const
        {
            Iterator local_iterator = first;
            typename RepeatCountLimit::type i{};
            for (/**/; !repeat_limit.got_min(i, context); ++i) {
                if (!detail::parse_into_container(
                        this->subject,
                        local_iterator,
                        last,
                        context,
                        rcontext,
                        attr))
                    return false;
            }

            first = local_iterator;
            // parse some more up to the maximum specified
            for (/**/; !repeat_limit.got_max(i, context); ++i) {
                if (!detail::parse_into_container(
                        this->subject, first, last, context, rcontext, attr))
                    break;
            }
            return true;
        }

        RepeatCountLimit repeat_limit;
    };

    struct lazy_repeat_gen
    {
        template<typename Subject>
        auto operator[](Subject const & subject) const
        {
            return *as_parser(subject);
        }

        template<typename T>
        struct lazy_repeat_gen_lvl1
        {
            lazy_repeat_gen_lvl1(T && repeat_limit_) :
                repeat_limit(repeat_limit_)
            {}

            template<typename Subject>
            lazy_repeat_directive<
                typename extension::as_parser<Subject>::value_type,
                T>
            operator[](Subject const & subject) const
            {
                return {as_parser(subject), repeat_limit};
            }

            T repeat_limit;
        };

        template<typename Fn>
        lazy_repeat_gen_lvl1<detail::lazy_exact_count<Fn>>
        operator()(Fn exact) const
        {
            return {detail::lazy_exact_count<Fn>{std::move(exact)}};
        }

        template<typename Fn>
        lazy_repeat_gen_lvl1<detail::lazy_finite_count<Fn>>
        operator()(int const min_val, Fn max_val) const
        {
            return {detail::lazy_finite_count<Fn>{min_val, std::move(max_val)}};
        }
    };

    auto const lazy_repeat = lazy_repeat_gen{};

}}}

namespace boost { namespace yaml {

    // Parser enums.

    enum class context {
        block_in,
        block_out,
        flow_in,
        flow_out,
        block_key,
        flow_key
    };

#ifdef BOOST_SPIRIT_X3_DEBUG
    inline std::ostream & operator<<(std::ostream & os, context c)
    {
        switch (c) {
#define CASE(x)                                                                \
    case context::x: return os << #x
            CASE(block_in);
            CASE(block_out);
            CASE(flow_in);
            CASE(flow_out);
            CASE(block_key);
            CASE(flow_key);
#undef CASE
        }
        return os;
    }
#endif

    enum class encoding { utf32_be, utf32_le, utf16_be, utf16_le, utf8 };

    inline std::ostream & operator<<(std::ostream & os, encoding c)
    {
        switch (c) {
        case encoding::utf32_be: return os << "UTF-32 big-endian";
        case encoding::utf32_le: return os << "UTF-32 little-endian";
        case encoding::utf16_be: return os << "UTF-16 big-endian";
        case encoding::utf16_le: return os << "UTF-16 little-endian";
        case encoding::utf8: return os << "UTF-8";
        }
        return os;
    }

    enum class chomping { strip, clip, keep };

#ifdef BOOST_SPIRIT_X3_DEBUG
    inline std::ostream & operator<<(std::ostream & os, chomping c)
    {
        switch (c) {
        case chomping::strip: return os << "strip";
        case chomping::clip: return os << "clip";
        case chomping::keep: return os << "keep";
        }
        return os;
    }
#endif

    enum class eoi_state { not_at_end, at_end };

#ifdef BOOST_SPIRIT_X3_DEBUG
    inline std::ostream & operator<<(std::ostream & os, eoi_state s)
    {
        return os << (s == eoi_state::not_at_end ? "not_at_end" : "at_end");
    }
#endif

    struct block_header
    {
        block_header() : indentation_(0), chomping_(chomping::clip) {}
        block_header(int indentation, chomping chomping) :
            indentation_(indentation),
            chomping_(chomping)
        {}

        int indentation_;
        chomping chomping_;
    };

#ifdef BOOST_SPIRIT_X3_DEBUG
    inline std::ostream & operator<<(std::ostream & os, block_header b)
    {
        return os << b.indentation_ << ',' << b.chomping_;
    }
#endif

    template<typename Iter>
    struct parser_properties
    {
        parser_properties() {}
        parser_properties(
            std::string const & tag, iterator_range<Iter> anchor) :
            tag_(tag),
            anchor_(anchor)
        {}

        std::string tag_;
        iterator_range<Iter> anchor_;
    };
#ifdef BOOST_SPIRIT_X3_DEBUG
    inline std::ostream &
    operator<<(std::ostream & out, parser_properties const & p)
    {
        return out << p.tag_ << ',' << rangeo_string(p.anchor_);
    }
#endif

    template<typename Iter>
    struct anchor
    {
        alias alias_;
        Iter position_;
    };



    // State to track during the parse.

    struct parser_state_tag;

    template<typename Iter>
    struct parser_state
    {
        using iterator = Iter;
        using iterator_range = boost::iterator_range<Iter>;

        int indent_ = 0;
        context context_ = context::block_in;
        bool stop_at_document_delimiter_ = false;

        eoi_state eoi_state_ = eoi_state::not_at_end;

        bool yaml_directive_seen_;
        Iter first_yaml_directive_it_;
        Iter latest_yaml_directive_it_;
    };



    namespace x3 = spirit::x3;

    x3::rule<class two_hex_digits, char> const two_hex_digits =
        "two hexidecimal digits";
    x3::rule<class four_hex_digits, char> const four_hex_digits =
        "four hexidecimal digits";
    x3::rule<class eight_hex_digits, char> const eight_hex_digits =
        "eight hexidecimal digits";

    auto const two_hex_digits_def = x3::repeat(2)[x3::ascii::xdigit];
    BOOST_SPIRIT_DEFINE(two_hex_digits);
    auto const four_hex_digits_def = x3::repeat(4)[x3::ascii::xdigit];
    BOOST_SPIRIT_DEFINE(four_hex_digits);
    auto const eight_hex_digits_def = x3::repeat(8)[x3::ascii::xdigit];
    BOOST_SPIRIT_DEFINE(eight_hex_digits);



    // 5.2. Character Encodings

    // [1]
    x3::rule<class printable, uint32_t> const printable = "printable";
    auto const printable_def = x3::char_("\t\n\f") | x3::char_('\x20', '\x7e') |
                               x3::unicode::char_(0x0085u) |
                               x3::unicode::char_(0x00a0u, 0xd7ffu) |
                               x3::unicode::char_(0xe000u, 0xfffdu) |
                               x3::unicode::char_(0x00010000u, 0x0010ffffu);
    BOOST_SPIRIT_DEFINE(printable);

    // [2]
    x3::rule<class ws, uint32_t> const nb_json = "nb_json";
    auto const nb_json_def =
        x3::char_('\t') | x3::unicode::char_(0x0020u, 0x0010ffffu);
    BOOST_SPIRIT_DEFINE(nb_json);

    // [3]
    x3::rule<class bom, uint32_t> const bom = "bom";
    auto const bom_def = x3::unicode::char_(0xfeff);
    BOOST_SPIRIT_DEFINE(bom);

    // 5.4. Line Break Characters

    // [27]
    x3::rule<class nb_char, uint32_t> const nb_char = "nb_char";
    auto const nb_char_def = printable - x3::eol - bom;
    BOOST_SPIRIT_DEFINE(nb_char);

    // 5.5. White Space Characters

    // [34]
    x3::rule<class ns_char, uint32_t> const ns_char = "ns_char";
    auto const ns_char_def = printable - x3::eol - bom - x3::ascii::blank;
    BOOST_SPIRIT_DEFINE(ns_char);

    // 5.6. Miscellaneous Characters

    // [38]
    x3::rule<class word_char, uint32_t> const word_char = "word_char";
    auto const word_char_def = x3::ascii::alnum | x3::char_('-');
    BOOST_SPIRIT_DEFINE(word_char);

    // [39]
    x3::rule<class uri_char, uint32_t> const uri_char = "uri_char";
    auto const uri_char_def = x3::char_('%') >> &two_hex_digits | word_char |
                              x3::char_("#;/?:@&=+$,_.!~*'()[]");
    BOOST_SPIRIT_DEFINE(uri_char);

    // [40]
    x3::rule<class tag_char, uint32_t> const tag_char = "tag_char";
    auto const tag_char_def =
        uri_char - x3::char_("!,[]{}"); // - '!' - flow_indicator [23]
    BOOST_SPIRIT_DEFINE(tag_char);

    // 5.7. Escaped Characters

    // [62]
    x3::rule<class esc_char, uint32_t> const esc_char = "esc_char";

    x3::rule<class x_escape_seq, uint32_t> const x_escape_seq =
        "\\xXX hexidecimal escape sequence";
    x3::rule<class u_escape_seq, uint32_t> const u_escape_seq =
        "\\uXXXX hexidecimal escape sequence";
    x3::rule<class U_escape_seq, uint32_t> const U_escape_seq =
        "\\UXXXXXXXX hexidecimal escape sequence";
    x3::rule<class single_escaped_char, uint32_t> const single_escaped_char =
        "'0', 'a', 'b', 't', 'n', 'v', 'f', 'r', 'e', '\"', '/', '\\', 'N', "
        "'_', 'L', 'P', SPACE or TAB";

    auto parse_hex = [](auto & ctx) {
        auto const cp_range = _attr(ctx);
        uint32_t result;
        if (x3::parse(cp_range.begin(), cp_range.end(), x3::hex, result))
            _val(ctx) = result;
        else
            _pass(ctx) = false;
    };

    auto const x_escape_seq_def = x3::raw["\\x" > two_hex_digits][parse_hex];
    BOOST_SPIRIT_DEFINE(x_escape_seq);
    auto const u_escape_seq_def = x3::raw["\\u" > four_hex_digits][parse_hex];
    BOOST_SPIRIT_DEFINE(u_escape_seq);
    auto const U_escape_seq_def = x3::raw["\\U" > eight_hex_digits][parse_hex];
    BOOST_SPIRIT_DEFINE(U_escape_seq);

    auto const single_escaped_char_def =
        '0' >> x3::attr(0x0000u) | 'a' >> x3::attr(0x0007u) |
        'b' >> x3::attr(0x0008u) | (x3::lit('t') | '\t') >> x3::attr(0x0009u) |
        'n' >> x3::attr(0x000au) | 'v' >> x3::attr(0x000bu) |
        'f' >> x3::attr(0x000cu) | 'r' >> x3::attr(0x000du) |
        'e' >> x3::attr(0x001bu) | ' ' >> x3::attr(0x0020u) |
        '"' >> x3::attr(0x0022u) | '/' >> x3::attr(0x002fu) |
        '\\' >> x3::attr(0x005cu) | 'N' >> x3::attr(0x0085u) |
        '_' >> x3::attr(0x00a0u) | 'L' >> x3::attr(0x2028u) |
        'P' >> x3::attr(0x2029u);
    BOOST_SPIRIT_DEFINE(single_escaped_char);

    auto const esc_char_def = x_escape_seq | u_escape_seq | U_escape_seq |
                              x3::lit('\\') > single_escaped_char;
    BOOST_SPIRIT_DEFINE(esc_char);



    // 6.1. Indentation Spaces

    auto indent_ = [](auto & ctx) {
        auto const & state = x3::get<parser_state_tag>(ctx).get();
        return state.indent_;
    };
    auto indent_minus_1 = [](auto & ctx) {
        auto const & state = x3::get<parser_state_tag>(ctx).get();
        return state.indent_ - 1;
    };

    // [63]
    x3::rule<class indent> const indent = "indent";
    auto const indent_def = x3::lazy_repeat(indent_)[x3::lit(' ')];
    BOOST_SPIRIT_DEFINE(indent);

    // [64]
    x3::rule<class indent_lt> const indent_lt = "indent_lt";
    auto const indent_lt_def = x3::lazy_repeat(0, indent_minus_1)[x3::lit(' ')];
    BOOST_SPIRIT_DEFINE(indent_lt);

    // [65]
    x3::rule<class indent_le> const indent_le = "indent_le";
    auto const indent_le_def = x3::lazy_repeat(0, indent_)[x3::lit(' ')];
    BOOST_SPIRIT_DEFINE(indent_le);

    // 6.2. Separation Spaces

    auto check_start_of_line = [](auto & ctx) {
        auto const iter_range = _attr(ctx);
        auto const & error_handler =
            x3::get<yaml::error_handler_tag>(ctx).get();
        if (error_handler.column(iter_range.begin()))
            _pass(ctx) = false;
    };

    // [66]
    x3::rule<class separate_in_line> const separate_in_line =
        "separate_in_line";
    auto const separate_in_line_def =
        +x3::blank | x3::raw[x3::eps][check_start_of_line];
    BOOST_SPIRIT_DEFINE(separate_in_line);

    // 6.3. Line Prefixes

    auto block_context = [](auto & rule_ctx) {
        return rule_ctx.get().context_ == context::block_in ||
               rule_ctx.get().context_ == context::block_out;
    };

    auto flow_context = [](auto & rule_ctx) {
        return rule_ctx.get().context_ == context::flow_in ||
               rule_ctx.get().context_ == context::flow_out;
    };

    // [67]
    x3::rule<class line_prefix> const line_prefix = "line_prefix";
    auto const line_prefix_def = x3::eps(block_context) >> indent |
                                 x3::eps(flow_context) >> indent >>
                                     -separate_in_line;
    BOOST_SPIRIT_DEFINE(line_prefix);

    // 6.4 Empty Lines

    // [70]
    x3::rule<class l_empty, char> const l_empty = "l_empty";
    auto const l_empty_def = x3::omit[line_prefix | indent_lt] >> x3::eol >>
                             x3::attr('\n');
    BOOST_SPIRIT_DEFINE(l_empty);

    // 6.5 Line Folding

    auto dont_stop_at_doc_delimiter = [](auto & rule_ctx) {
        return !rule_ctx.get().stop_at_document_delimiter_;
    };

    // [73]
    x3::rule<class b_l_folded, std::string> const b_l_folded =
        "b_l_folded";
    auto const b_l_folded_def = x3::eol >>
                                (x3::eps(dont_stop_at_doc_delimiter) |
                                 !(x3::lit("...") | "---")) >>
                                (+l_empty /* b-l-trimmed [71] */
                                 | x3::attr(" "));
    BOOST_SPIRIT_DEFINE(b_l_folded);

    auto set_context = [](context c) {
        return [c](auto & rule_ctx) {
            rule_ctx.get().context_ = c;
            return true;
        };
    };

    // [74]
    x3::rule<class flow_folded, std::string> const flow_folded = "flow_folded";
    auto const flow_folded_def = x3::eps(set_context(context::flow_in)) >>
                                 -separate_in_line >> b_l_folded >> line_prefix;
    BOOST_SPIRIT_DEFINE(flow_folded);

    // 6.6 Comments

    // [75]
    x3::rule<class comment_text> const comment_text = "comment_text";
    auto const comment_text_def = '#' >> +nb_char;
    BOOST_SPIRIT_DEFINE(comment_text);

    // HACK!  This is a dirty, dirty hack that bears explaining.  Many
    // productions in the YAML 1.2 spec include "newline | end-of-input"
    // (e.g. b-comment).  This poses a problem, since many of the uses of this
    // construct (say, using b-comment) are repeated via Kleene star.  Spirit
    // consumes a character when parsing a newline (qi::eol), but *not* when
    // parsing end-of-input (qi::eoi).
    //
    // So, when a rule contains, say, *b-comment, infinite looping results,
    // since qi::eoi succeeds without advancing the parser's read position.
    //
    // The natural inclination is to create a consuming version of eoi -- and
    // since eoi is unique, that state can be shared across all rules in the
    // parser.  Sadly, this does not work, because some (transitive) uses of
    // eoi in this YAML parser may need to backtrack back to before the eoi
    // was seen and try some other productions.
    //
    // As a workaround, I've created a repetition-detecting eoi.  The state is
    // passed in, and the first time eoi is seen, the state changes.
    // Subsequent eoi detections will fail.
    auto first_time_eoi = [](auto & rule_ctx) {
        auto & state = rule_ctx.get().eoi_state_;
        bool const retval = state == eoi_state::not_at_end;
        state = eoi_state::at_end;
        return retval;
    };

    // [77]
    x3::rule<class s_b_comment> const s_b_comment = "s_b_comment";
    auto const s_b_comment_def =
        -(separate_in_line >> -comment_text) >>
        (x3::eol | x3::eoi >> x3::eps(first_time_eoi)); // b-comment [77]
    BOOST_SPIRIT_DEFINE(s_b_comment);

    // [78]
    x3::rule<class l_comment> const l_comment = "l_comment";
    auto const l_comment_def = separate_in_line >> -comment_text >>
                               (x3::eol | x3::eoi >> x3::eps(first_time_eoi));
    BOOST_SPIRIT_DEFINE(l_comment);

    // [79]
    x3::rule<class s_l_comments> const s_l_comments = "s_l_comments";
    auto const s_l_comments_def =
        (s_b_comment | x3::raw[x3::eps][check_start_of_line]) >> *l_comment;
    BOOST_SPIRIT_DEFINE(s_l_comments);

    // 6.7 Separation Lines

    auto key_context = [](auto & rule_ctx) {
        return rule_ctx.get().context_ == context::block_key ||
               rule_ctx.get().context_ == context::flow_key;
    };

    auto not_key_context = [](auto & rule_ctx) {
        return rule_ctx.get().context_ != context::block_key &&
               rule_ctx.get().context_ != context::flow_key;
    };

    // [80]
    x3::rule<class separate> const separate = "separate";
    // [81]
    x3::rule<class separate_lines> const separate_lines = "separate_lines";

    // [80]
    auto const separate_def = x3::eps(key_context) >> separate_in_line |
                              x3::eps(not_key_context) >> separate_lines;
    BOOST_SPIRIT_DEFINE(separate);

    // [81]
    auto const separate_lines_def =
        s_l_comments >> indent >> -separate_in_line // flow-line-prefix [69]
        | separate_in_line;
    BOOST_SPIRIT_DEFINE(separate_lines);

    // 6.8 Directives

    // [82]
    x3::rule<class directive> const directive = "directive";
    // [83]
    x3::rule<class reserved_directive> const reserved_directive =
        "reserved_directive";
    // [86]
    x3::rule<class yaml_directive> const yaml_directive = "yaml_directive";
    // [88]
    x3::rule<class tag_directive> const tag_directive = "tag_directive";
    // [89]
    x3::rule<class tag_handle> const tag_handle = "tag_handle";
    // [93]
    x3::rule<class tag_prefix> const tag_prefix = "tag_prefix";

    // [82]
    auto const directive_def =
        '%' >>
        (yaml_directive | tag_directive | reserved_directive) >> s_l_comments;
    BOOST_SPIRIT_DEFINE(directive);

    auto reserved_directive_warning = [](auto & ctx) {
        auto const & error_handler =
            x3::get<yaml::error_handler_tag>(ctx).get();
        // TODO: Report warning.
    };

    // [83]
    auto const reserved_directive_def = x3::raw
        [+x3::omit[ns_char] >> *(+x3::omit[x3::blank] >> +x3::omit[ns_char])]
        [reserved_directive_warning];
    BOOST_SPIRIT_DEFINE(reserved_directive);

    auto record_yaml_directive = [](auto & ctx) {
        auto & state = x3::get<parser_state_tag>(ctx).get();
        state.latest_yaml_directive_it_ = _attr(ctx).begin();
    };

    auto check_yaml_version = [](auto & ctx) {
        auto & state = x3::get<parser_state_tag>(ctx).get();
        auto const & error_handler =
            x3::get<yaml::error_handler_tag>(ctx).get();

        if (state.yaml_directive_seen_) {
#if 0 // TODO
            scoped_multipart_error_t multipart(error_handler.impl());
            error_handler.impl().report_error_at(
                state.latest_yaml_directive_it_,
                "The current document has more than one %YAML "
                "directive.  Only one is allowed.  The latest "
                "one is here",
                multipart);
            error_handler.impl().report_error_at(
                state.first_yaml_directive_it_,
                "The first one was was here",
                multipart);
#endif
            _pass(ctx) = false;
        } else {
            int const major = fusion::at_c<0>(_attr(ctx));
            int const minor = fusion::at_c<1>(_attr(ctx));
            state.first_yaml_directive_it_ = state.latest_yaml_directive_it_;
            if (major != 1) {
#if 0 // TODO
                scoped_multipart_error_t multipart(error_handler.impl());
                std::ostringstream oss;
                oss << "The current document has a %YAML " << major << '.'
                    << minor
                    << " directive.  This parser recognizes "
                       "YAML 1.2, and so cannot continue";
                error_handler.impl().report_error_at(
                    state.first_yaml_directive_it_, oss.str(), multipart);
#endif
                _pass(ctx) = false;
            } else if (minor != 2/* TODO && error_handler.impl().warning_fn_*/) {
#if 0 // TODO
                std::ostringstream oss;
                oss << "The current document has a %YAML " << major << '.'
                    << minor
                    << " directive.  This parser recognizes "
                       "YAML 1.2, and so might not work.  "
                       "Trying anyway...";
                error_handler.impl().report_warning_at(
                    state.first_yaml_directive_it_, oss.str());
#endif
            }
            state.yaml_directive_seen_ = true;
        }
    };

    // [86]
    auto const yaml_directive_def = x3::raw["YAML"][record_yaml_directive] >>
                                    +x3::blank >>
                                    (x3::uint_ >> '.' >>
                                     x3::uint_)[check_yaml_version];
    BOOST_SPIRIT_DEFINE(yaml_directive);


    struct tag
    {
        std::string prefix_;
        any position_;
        bool default_;
    };

    struct tags_t : x3::symbols<tag>
    {
        tags_t()
        {
            add("!!", tag{"tag:yaml.org,2002:", any(), true});
            add("!", tag{"!", any(), true});
        }
    };

    // TODO: This makes the parser thread-unsafe.
    tags_t tags;

    auto record_tag = [](auto & ctx) {
        auto & state = x3::get<parser_state_tag>(ctx).get();
        auto const & error_handler =
            x3::get<yaml::error_handler_tag>(ctx).get();

        using cp_iter = typename decltype(state)::iterator;
        using cp_range = typename decltype(state)::iterator_range;
        cp_range const handle_cp_range = fusion::at_c<0>(_attr(ctx));
        cp_range const prefix_cp_range = fusion::at_c<1>(_attr(ctx));

        auto const handle_char_range =
            text::make_from_utf32_range(handle_cp_range);
        std::string const handle(
            handle_char_range.begin(), handle_char_range.end());

        auto existing_tag = tags.find(handle);
        if (existing_tag && existing_tag->default_) {
            tags.remove(handle);
            existing_tag = nullptr;
        }

        if (existing_tag) {
#if 0 // TODO
            scoped_multipart_error_t multipart(error_handler.impl());
            std::ostringstream oss;
            oss << "The current document has more than one %TAG "
                << "directive using the handle " << handle << ".  "
                << "Only one is allowed.  The latest one is here";
            error_handler.impl().report_error_at(
                handle_range.begin(), oss.str(), multipart);
            error_handler.impl().report_error_at(
                existing_tag->position_,
                "The first one was was here",
                multipart);
#endif
            _pass(ctx) = false;
        } else {
            auto const prefix_char_range =
                text::make_from_utf32_range(prefix_cp_range);
            std::string prefix(
                prefix_char_range.begin(), prefix_char_range.end());

            tags.add(
                handle,
                tag{std::move(prefix), any(handle_cp_range.begin()), false});
        }
    };

    // [88]
    // TODO: This definition breaks directive above by leaking attributes.
    auto const tag_directive_def =
        ("TAG" >> +x3::omit[x3::blank] >> x3::raw[tag_handle] >>
         +x3::omit[x3::blank] >> x3::raw[tag_prefix])[record_tag];
    BOOST_SPIRIT_DEFINE(tag_directive);

    // [89]
    auto const tag_handle_def =
        // "alnum..." below is  word_char [38]
        '!' >> +(x3::alnum | x3::char_("-")) >> '!' // named_tag_handle [92]
        | "!!"                                      // secondary_tag_handle [91]
        | '!'                                       // primary_tag_handle [90]
        ;
    BOOST_SPIRIT_DEFINE(tag_handle);

    // [93]
    auto const tag_prefix_def = '!' >> *uri_char | tag_char >> *uri_char;
    BOOST_SPIRIT_DEFINE(tag_prefix);


    // 6.9 Node Properties

#if 0 // TODO
    // [96]
    x3::rule<class properties, parser_properties> const properties =
        "properties";
    auto const properties_def =
        (tag_property[_a = _1] >>
             -(separate(_r1, _r2) >> anchor_property[_b = *_1]) |
         anchor_property[_b = _1] >>
             -(separate(_r1, _r2) >> tag_property[_a = *_1]))
            [_val = construct<parser_properties_t>(_a, _b)];
    BOOST_SPIRIT_DEFINE(properties);

    // [97]
    x3::rule<class tag_property, std::string> const tag_property =
        "tag_property";
    auto const tag_property_def =
        raw["!<" > +uri_char > '>'][_val = to_str(_1)] // verbatim_tag [98]
        | (tags >>
           raw[+tag_char])[_val = prefix(_1) + to_str(_2)] // shorthand_tag [99]
        | lit('!')[_val = "!"] // non_specific_tag [100]
        ;
    BOOST_SPIRIT_DEFINE(tag_property);
#endif

    // [22]
    // auto indicator = char_("-?:,[]{}#&*!|>'\"%@`");

    // [101]
    x3::rule<class anchor_property, any> const anchor_property =
        "anchor_property";
    auto const anchor_property_def =
        '&' >> x3::raw[+(ns_char - x3::char_(",[]{}"))];
    BOOST_SPIRIT_DEFINE(anchor_property);

    // [102]
    // auto anchor_char = ns_char - char_(",[]{}");

    // [103]
    x3::rule<class anchor_name, any> const anchor_name = "anchor_name";
    auto const anchor_name_def = x3::raw[+(ns_char - x3::char_(",[]{}"))];
    BOOST_SPIRIT_DEFINE(anchor_name);

    x3::rule<class one_time_eoi> const one_time_eoi = "one_time_eoi";
    auto const one_time_eoi_def = x3::eoi >> x3::eps(first_time_eoi);
    BOOST_SPIRIT_DEFINE(one_time_eoi);


    // TODO
    struct test_parser_struct;
    x3::rule<test_parser_struct> const test = "test";
    auto const test_def = x3::omit
        [indent | indent_lt | indent_le | separate_in_line | line_prefix |
         l_empty | b_l_folded | flow_folded | comment_text | s_b_comment |
         s_l_comments | separate | separate_lines | reserved_directive |
         yaml_directive | tag_handle | tag_prefix | anchor_property |
         anchor_name | one_time_eoi];
    BOOST_SPIRIT_DEFINE(test);




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
            std::string message = "error: Expected " + e.which() + " here:";
            error_handler(e.where(), message);
            return x3::error_handler_result::fail;
        }
    };

    // TODO
    struct test_parser_struct : x3_error_handler_base
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
        parser_state<iter_t> state;

        if (max_recursive_count < 0)
            max_recursive_count = INT_MAX;

        // clang-format off
        auto parser = x3::with<yaml::error_handler_tag>(std::ref(error_handler))[
            x3::with<parser_state_tag>(std::ref(state))[
                // Add state again with the tag x3::rule_context_tag, for easy
                // interoperation with x3::eps(---).
                x3::with<x3::rule_context_tag>(std::ref(state))[
                    test
                ]
            ]
        ];
        // clang-format on

        bool result = x3::parse(first, last, parser);

        if (!result || first != last)
            return {};

        return {}; // TODO optional<value>(std::move(v));
    }
}}
