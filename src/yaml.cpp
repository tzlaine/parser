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

    struct block_header_t
    {
        int indentation_;
        chomping chomping_;
    };

#ifdef BOOST_SPIRIT_X3_DEBUG
    inline std::ostream & operator<<(std::ostream & os, block_header_t b)
    {
        return os << b.indentation_ << ',' << b.chomping_;
    }
#endif

    struct parser_properties
    {
        std::string tag_;
        any anchor_; // iterator range
    };
#ifdef BOOST_SPIRIT_X3_DEBUG
    inline std::ostream &
    operator<<(std::ostream & out, parser_properties const & p)
    {
        return out << p.tag_ << ',' << rangeo_string(p.anchor_);
    }
#endif

    struct anchor
    {
        alias alias_;
        any position_; // iterator
    };



    // State to track during the parse.

    struct parser_state_tag;

    template<typename Iter>
    struct parser_state
    {
        using iterator = Iter;
        using iterator_range = boost::iterator_range<Iter>;

        parser_state(int max_recursion) :
            max_recursive_open_count_(max_recursion)
        {
            indent_stack_.push_back(0); // TODO
            context_stack_.push_back(context::block_in); // TODO
        }

        int indent() const noexcept { return indent_stack_.back(); }
        context context_() const noexcept { return context_stack_.back(); }

        void push_in_flow_context()
        {
            // in-flow [136]
            switch (context_()) {
            case context::flow_out:
            case context::flow_in:
                context_stack_.push_back(context::flow_in);
                break;
            case context::block_key:
            case context::flow_key:
                context_stack_.push_back(context::flow_key);
                break;
            default: BOOST_ASSERT(!"Invalid input passed to in_flow()");
            }
        }

        int recursive_open_count_ = 0;
        int const max_recursive_open_count_;

        std::vector<int> indent_stack_;
        std::vector<context> context_stack_;
        bool stop_at_document_delimiter_ = false;

        eoi_state eoi_state_ = eoi_state::not_at_end;

        bool yaml_directive_seen_ = false;
        iterator first_yaml_directive_it_;
        iterator latest_yaml_directive_it_;

        iterator_range tag_handle_;

        std::string tag_property_;
        any anchor_property_; // iterator range
    };


    // Declarations.

    namespace x3 = spirit::x3;

    // Helper rules.

    x3::rule<class two_hex_digits, char> const two_hex_digits =
        "two hexidecimal digits";
    x3::rule<class four_hex_digits, char> const four_hex_digits =
        "four hexidecimal digits";
    x3::rule<class eight_hex_digits, char> const eight_hex_digits =
        "eight hexidecimal digits";

    x3::rule<class x_escape_seq, uint32_t> const x_escape_seq =
        "\\xXX hexidecimal escape sequence";
    x3::rule<class u_escape_seq, uint32_t> const u_escape_seq =
        "\\uXXXX hexidecimal escape sequence";
    x3::rule<class U_escape_seq, uint32_t> const U_escape_seq =
        "\\UXXXXXXXX hexidecimal escape sequence";
    x3::rule<class single_escaped_char, uint32_t> const single_escaped_char =
        "'0', 'a', 'b', 't', 'n', 'v', 'f', 'r', 'e', '\"', '/', '\\', 'N', "
        "'_', 'L', 'P', SPACE or TAB";

    x3::rule<class push_in_flow_context> const push_in_flow_context;
    x3::rule<class pop_context> const pop_context;
    x3::rule<class pop_indent> const pop_indent;



    // 5.2. Character Encodings

    // [1]
    x3::rule<class printable, uint32_t> const printable = "printable";

    // [2]
    x3::rule<class ws, uint32_t> const nb_json = "nb_json";

    // [3]
    x3::rule<class bom, uint32_t> const bom = "bom";

    // 5.4. Line Break Characters

    // [27]
    x3::rule<class nb_char, uint32_t> const nb_char = "nb_char";

    // 5.5. White Space Characters

    // [34]
    x3::rule<class ns_char, std::string> const ns_char = "ns_char";
    x3::rule<class raw_ns_char, std::string> const raw_ns_char = "ns_char";

    // 5.6. Miscellaneous Characters

    // [38]
    x3::rule<class word_char, uint32_t> const word_char = "word_char";

    // [39]
    x3::rule<class uri_char, uint32_t> const uri_char = "uri_char";

    // [40]
    x3::rule<class tag_char, uint32_t> const tag_char = "tag_char";

    // 5.7. Escaped Characters

    // [62]
    x3::rule<class esc_char, uint32_t> const esc_char = "esc_char";

    // 6.1. Indentation Spaces

    // [63]
    x3::rule<class indent> const indent = "indent";

    // [64]
    x3::rule<class indent_lt> const indent_lt = "indent_lt";

    // [65]
    x3::rule<class indent_le> const indent_le = "indent_le";

    // 6.2. Separation Spaces

    // [66]
    x3::rule<class separate_in_line> const separate_in_line =
        "separate_in_line";

    // 6.3. Line Prefixes

    // [67]
    x3::rule<class line_prefix> const line_prefix = "line_prefix";

    // 6.4 Empty Lines

    // [70]
    x3::rule<class l_empty, char> const l_empty = "l_empty";

    // 6.5 Line Folding

    // [73]
    x3::rule<class b_l_folded, std::string> const b_l_folded = "b_l_folded";

    // [74]
    x3::rule<class flow_folded, std::string> const flow_folded = "flow_folded";

    // 6.6 Comments

    // [75]
    x3::rule<class comment_text> const comment_text = "comment_text";

    // [77]
    x3::rule<class s_b_comment> const s_b_comment = "s_b_comment";

    // [78]
    x3::rule<class l_comment> const l_comment = "l_comment";

    // [79]
    x3::rule<class s_l_comments> const s_l_comments = "s_l_comments";

    // 6.7 Separation Lines

    // [80]
    x3::rule<class separate> const separate = "separate";

    // [81]
    x3::rule<class separate_lines> const separate_lines = "separate_lines";

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

    // 6.9 Node Properties

    // [96]
    x3::rule<class properties_t, parser_properties> const properties =
        "properties";

    // [97]
    x3::rule<class tag_property, std::string> const tag_property =
        "tag_property";

    // [22]
    // auto indicator = char_("-?:,[]{}#&*!|>'\"%@`");

    // [101]
    x3::rule<class anchor_property, any> const anchor_property =
        "anchor_property";

    // [102]
    // auto anchor_char = ns_char - char_(",[]{}");

    // [103]
    x3::rule<class anchor_name, any> const anchor_name = "anchor_name";

    x3::rule<class one_time_eoi> const one_time_eoi = "one_time_eoi";

    // 7.1 Alias Nodes

    // [104]
    x3::rule<class alias_node, alias> const alias_node = "alias_node";

    // 7.3 Flow Scalar Styles

    // 7.3.1 Double Quoted Style

    // [107]
    x3::rule<class nb_double_char, std::string> const nb_double_char =
        "nb_double_char";

    // [108]
    x3::rule<class ns_double_char, std::string> const ns_double_char =
        "ns_double_char";

    // [109]
    x3::rule<class double_quoted, std::string> const double_quoted =
        "double_quoted";

    // [110]
    x3::rule<class double_text, std::string> const double_text = "double_text";

    // [112]
    x3::rule<class double_escaped, std::string> const double_escaped =
        "double_escaped";

    // [113]
    x3::rule<class double_break, std::string> const double_break =
        "double_break";

    // [114]
    x3::rule<class double_in_line, std::string> const double_in_line =
        "double_in_line";

    // [115]
    x3::rule<class double_next_line, std::string> const double_next_line =
        "double_next_line";

    // [116]
    x3::rule<class double_multi_line, std::string> const double_multi_line =
        "double_multi_line";

    // 7.3.2 Single Quoted Style

    // [118]
    x3::rule<class nb_single_char, std::string> const nb_single_char =
        "nb_single_char";

    // [119]
    x3::rule<class ns_single_char, std::string> const ns_single_char =
        "ns_single_char";

    // [120]
    x3::rule<class single_quoted, std::string> const single_quoted =
        "single_quoted";

    // [121]
    x3::rule<class single_text, std::string> const single_text = "single_text";

    // [123]
    x3::rule<class single_in_line, std::string> const single_in_line =
        "single_in_line";

    // [124]
    x3::rule<class single_next_line, std::string> const single_next_line =
        "single_next_line";

    // [125]
    x3::rule<class single_multi_line, std::string> const single_multi_line =
        "single_multi_line";

    // 7.3.3 Plain Style

    // [22]
    x3::rule<class indicator> const indicator = "indicator";

    // [126]
    x3::rule<class plain_first, std::string> const plain_first = "plain_first";

    // [127]
    x3::rule<class plain_safe, std::string> const plain_safe = "plain_safe";
    x3::rule<class not_plain_safe> const not_plain_safe = "not_plain_safe";

    // [130]
    x3::rule<class plain_char, std::string> const plain_char = "plain_char";

    // [131]
    x3::rule<class plain, std::string> const plain = "plain";

    // [132]
    x3::rule<class plain_in_line, std::string> const plain_in_line =
        "plain_in_line";

    // [133]
    x3::rule<class plain_one_line, std::string> const plain_one_line =
        "plain_one_line";

    // [134]
    x3::rule<class plain_next_line, std::string> const plain_next_line =
        "plain_next_line";

    // [135]
    x3::rule<class plain_multi_line, std::string> const plain_multi_line =
        "plain_multi_line";


    // 7.4 Flow Collection Styles

    // [137]
    x3::rule<class flow_sequence, value> const flow_sequence = "flow_sequence";

    // [138]
    x3::rule<class flow_seq_entries, value> const flow_seq_entries =
        "flow_seq_entries";

    // [139]
    x3::rule<class flow_seq_entry, value> const flow_seq_entry =
        "flow_seq_entry";

    // 7.4.2 Flow Mappings

    // [140]
    x3::rule<class flow_mapping, value> const flow_mapping = "flow_mapping";

    // [141]
    x3::rule<class flow_map_entries, value> const flow_map_entries =
        "flow_map_entries";

    // [142]
    x3::rule<class flow_map_entry, map_element> const flow_map_entry =
        "flow_map_entry";

    // [143]
    x3::rule<class flow_map_explicit_entry, map_element> const
        flow_map_explicit_entry = "flow_map_explicit_entry";

    // [144]
    x3::rule<class flow_map_implicit_entry, map_element> const
        flow_map_implicit_entry = "flow_map_implicit_entry";

    // [145]
    x3::rule<class flow_map_yaml_key_entry, map_element> const
        flow_map_yaml_key_entry = "flow_map_yaml_key_entry";

    // [146]
    x3::rule<class flow_map_empty_key_entry, map_element> const
        flow_map_empty_key_entry = "flow_map_empty_key_entry";

    // [147]
    x3::rule<class flow_map_separate_value, value> const
        flow_map_separate_value = "flow_map_separate_value";

    // [148]
    x3::rule<class flow_map_json_key_entry, map_element> const
        flow_map_json_key_entry = "flow_map_json_key_entry";

    // [149]
    x3::rule<class flow_map_adjacent_value, value> const
        flow_map_adjacent_value = "flow_map_adjacent_value";

    // [150]
    x3::rule<class flow_pair, value> const flow_pair = "flow_pair";

    // [151]
    x3::rule<class flow_pair_entry, map_element> const flow_pair_entry =
        "flow_pair_entry";

    // [152]
    x3::rule<class flow_pair_yaml_key_entry, map_element> const
        flow_pair_yaml_key_entry = "flow_pair_yaml_key_entry";

    // [153]
    x3::rule<class flow_pair_json_key_entry, map_element> const
        flow_pair_json_key_entry = "flow_pair_json_key_entry";

    // [154]
    x3::rule<class implicit_yaml_key, value> const implicit_yaml_key =
        "implicit_yaml_key";

    // [155]
    x3::rule<class implicit_json_key, value> const implicit_json_key =
        "implicit_json_key";

    // 7.5 Flow Nodes

    // [156]
    // flow_yaml_content = plain

    // [157]
    x3::rule<class flow_json_content, value> const flow_json_content =
        "flow_json_content";

    // [158]
    x3::rule<class flow_content, value> const flow_content = "flow_content";

    // [159]
    x3::rule<class flow_yaml_node, value> const flow_yaml_node =
        "flow_yaml_node";

    // [160]
    x3::rule<class flow_json_node, value> const flow_json_node =
        "flow_json_node";

    // [161]
    x3::rule<class flow_node, value> const flow_node = "flow_node";

    // 8.1 Block Scalar Styles

    // [162]
    x3::rule<class block_header, block_header_t> const block_header =
        "block_header";

    // [163]
    x3::rule<class indentation_indicator, int> const indentation_indicator =
        "indentation_indicator";

    // [164]
    x3::rule<class chomping_indicator, chomping> const chomping_indicator =
        "chomping_indicator";

    // [165]
    x3::rule<class chomped_last, std::string> const chomped_last =
        "chomped_last";

    // [166]
    x3::rule<class chomped_empty> const chomped_empty = "chomped_empty";

    // [167]
    x3::rule<class strip_empty> const strip_empty = "strip_empty";

    // [168]
    x3::rule<class keep_empty, std::string> const keep_empty = "keep_empty";

    // [169]
    x3::rule<class trail_comments> const trail_comments = "trail_comments";

    // [170]
    x3::rule<class literal, std::string> const literal = "literal";

    // [171]
    x3::rule<class literal_text, std::string> const literal_text =
        "literal_text";

    // [172]
    x3::rule<class literal_next, std::string> const literal_next =
        "literal_next";

    x3::rule<class literal_content_optional, std::string> const
        literal_content_optional = "literal_content_optional";

    // [173]
    x3::rule<class literal_content, std::string> const literal_content =
        "literal_content";

    // 8.1.3. Folded Style

    // [174]
    x3::rule<class folded, std::string> const folded = "folded";

    // [175]
    x3::rule<class folded_text, std::string> const folded_text = "folded_text";

    // [176]
    x3::rule<class folded_lines, std::string> const folded_lines =
        "folded_lines";

    // [177]
    x3::rule<class spaced_text, std::string> const spaced_text = "spaced_text";

    // [178]
    x3::rule<class spaced, std::string> const spaced = "spaced";

    // [179]
    x3::rule<class spaced_lines, std::string> const spaced_lines =
        "spaced_lines";

    // [180]
    x3::rule<class same_lines, std::string> const same_lines = "same_lines";

    // [181]
    x3::rule<class diff_lines, std::string> const diff_lines = "diff_lines";

    x3::rule<class folded_content_optional, std::string> const
        folded_content_optional = "folded_content_optional";

    // [182]
    x3::rule<class folded_content, std::string> const folded_content =
        "folded_content";

    // 8.2.1. Block Sequences

    x3::rule<class auto_detect_indent, int> const auto_detect_indent =
        "auto_detect_indent";

    x3::rule<class scalar_auto_detect_indent, int> const
        scalar_auto_detect_indent = "scalar_auto_detect_indent";

    // [183]
    x3::rule<class block_sequence, seq> const block_sequence = "block_sequence";

    // [184]
    x3::rule<class block_seq_entry, value> const block_seq_entry =
        "block_seq_entry";

    // [185]
    x3::rule<class block_indented, value> const block_indented =
        "block_indented";

    // [186]
    x3::rule<class compact_sequence, seq> const compact_sequence =
        "compact_sequence";

    // 8.2.1. Block Mappings

    // [187]
    x3::rule<class block_mapping, map> const block_mapping = "block_mapping";

    // [188]
    x3::rule<class block_map_entry, map_element> const block_map_entry =
        "block_map_entry";

    // [189]
    x3::rule<class block_map_explicit_entry, map_element> const
        block_map_explicit_entry = "block_map_explicit_entry";

    // [190]
    x3::rule<class block_map_explicit_key, value> const block_map_explicit_key =
        "block_map_explicit_key";

    // [191]
    x3::rule<class block_map_explicit_value, value> const
        block_map_explicit_value = "block_map_explicit_value";

    // [192]
    x3::rule<class block_map_implicit_entry, map_element> const
        block_map_implicit_entry = "block_map_implicit_entry";

    // [193]
    x3::rule<class block_map_implicit_key, value> const block_map_implicit_key =
        "block_map_implicit_key";

    // [194]
    x3::rule<class block_map_implicit_value, value> const
        block_map_implicit_value = "block_map_implicit_value";

    // [195]
    x3::rule<class compact_mapping, map> const compact_mapping =
        "compact_mapping";

    // 8.2.3. Block Nodes

    // [196]
    x3::rule<class block_node, value> const block_node = "block_node";

    // [197]
    x3::rule<class flow_in_block, value> const flow_in_block = "flow_in_block";

    // [198]
    x3::rule<class block_in_block, value> const block_in_block =
        "block_in_block";

    // [199]
    x3::rule<class block_scalar, value> const block_scalar = "block_scalar";

    // [200]
    x3::rule<class block_collection, value> const block_collection =
        "block_collection";


    // [202]
    x3::rule<class document_prefix> const document_prefix = "document_prefix";

    // [205]
    x3::rule<class document_suffix> const document_suffix = "document_suffix";

    // [206]
    x3::rule<class forbidden> const forbidden = "forbidden";

    // [207]
    x3::rule<class bare_document, value> const bare_document = "bare_document";

    // [208]
    x3::rule<class explicit_document, value> const explicit_document =
        "explicit_document";

    // [209]
    x3::rule<class directive_document, value> const directive_document =
        "directive_document";

    // [210]
    x3::rule<class any_document, value> const any_document = "any_document";

    // [211]
    x3::rule<class yaml_stream, std::vector<value>> const yaml_stream =
        "yaml_stream";

    x3::rule<class end_of_input> const end_of_input = "end_of_input";



    // Definitions

    // Needed for use with all the uint32_t-generating char parsers.
    auto append_utf8 = [](auto & ctx) {
        std::array<uint32_t, 1> const cps = {{_attr(ctx)}};
        auto const r = text::make_from_utf32_range(cps);
        std::string & str = _val(ctx);
        str.insert(str.end(), r.begin(), r.end());
    };

#if 0 // TODO: Looks like this is unneeded.
    // Make this a callable object with multiple signatures, and recognize the
    // case that the range begin appended is a pair of
    // text::utf8::from_utf32_iterators.  In that case, insert with .base().
    auto append_utf8_range = [](auto & ctx) {
        auto const r = text::make_from_utf32_range(_attr(ctx));
        std::string & str = _val(ctx);
        str.insert(str.end(), r.begin(), r.end());
    };
#endif

    auto const two_hex_digits_def = x3::repeat(2)[x3::ascii::xdigit];
    auto const four_hex_digits_def = x3::repeat(4)[x3::ascii::xdigit];
    auto const eight_hex_digits_def = x3::repeat(8)[x3::ascii::xdigit];

    auto parse_hex = [](auto & ctx) {
        auto const cp_range = _attr(ctx);
        uint32_t result;
        if (x3::parse(cp_range.begin(), cp_range.end(), x3::hex, result))
            _val(ctx) = result;
        else
            _pass(ctx) = false;
    };

    auto const x_escape_seq_def = x3::raw["\\x" > two_hex_digits][parse_hex];
    auto const u_escape_seq_def = x3::raw["\\u" > four_hex_digits][parse_hex];
    auto const U_escape_seq_def = x3::raw["\\U" > eight_hex_digits][parse_hex];

    auto push_in_flow_context_ = [](auto & ctx) {
        auto & state = x3::get<parser_state_tag>(ctx).get();
        state.push_in_flow_context();
    };
    auto pop_context_ = [](auto & ctx) {
        auto & state = x3::get<parser_state_tag>(ctx).get();
        state.context_stack_.pop_back();
    };

    auto const push_in_flow_context_def = x3::eps[push_in_flow_context_];
    auto const pop_context_def = x3::eps[pop_context_];

    auto pop_indent_ = [](auto & ctx) {
        auto & state = x3::get<parser_state_tag>(ctx).get();
        state.indent_stack_.pop_back();
    };

    auto const pop_indent_def = x3::eps[pop_indent_];




    // 5.2. Character Encodings

    // [1]
    auto const printable_def = x3::char_("\t\n\f") | x3::char_('\x20', '\x7e') |
                               x3::unicode::char_(0x0085u) |
                               x3::unicode::char_(0x00a0u, 0xd7ffu) |
                               x3::unicode::char_(0xe000u, 0xfffdu) |
                               x3::unicode::char_(0x00010000u, 0x0010ffffu);

    // [2]
    auto const nb_json_def =
        x3::char_('\t') | x3::unicode::char_(0x0020u, 0x0010ffffu);

    // [3]
    auto const bom_def = x3::unicode::char_(0xfeff);

    // 5.4. Line Break Characters

    // [27]
    auto const nb_char_def = printable - x3::eol - bom;

    // 5.5. White Space Characters

    // [34]
    auto const ns_char_def = (nb_char_def - x3::ascii::blank)[append_utf8];
    auto const raw_ns_char_def = nb_char_def - x3::ascii::blank;

    // 5.6. Miscellaneous Characters

    // [38]
    auto const word_char_def = x3::ascii::alnum | x3::char_('-');

    // [39]
    auto const uri_char_def = x3::char_('%') >> &two_hex_digits | word_char |
                              x3::char_("#;/?:@&=+$,_.!~*'()[]");

    // [40]
    auto const tag_char_def =
        uri_char - x3::char_("!,[]{}"); // - '!' - flow_indicator [23]

    // 5.7. Escaped Characters

    // [62]
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

    auto const esc_char_def = x_escape_seq | u_escape_seq | U_escape_seq |
                              x3::lit('\\') > single_escaped_char;



    // 6.1. Indentation Spaces

    auto indent_ = [](auto & ctx) {
        auto const & state = x3::get<parser_state_tag>(ctx).get();
        return state.indent();
    };
    auto indent_minus_1 = [](auto & ctx) {
        auto const & state = x3::get<parser_state_tag>(ctx).get();
        return state.indent() - 1;
    };

    // [63]
    auto const indent_def = x3::lazy_repeat(indent_)[x3::lit(' ')];

    // [64]
    auto const indent_lt_def = x3::lazy_repeat(0, indent_minus_1)[x3::lit(' ')];

    // [65]
    auto const indent_le_def = x3::lazy_repeat(0, indent_)[x3::lit(' ')];

    // 6.2. Separation Spaces

    auto check_start_of_line = [](auto & ctx) {
        auto const iter_range = _attr(ctx);
        auto const & error_handler =
            x3::get<yaml::error_handler_tag>(ctx).get();
        if (error_handler.column(iter_range.begin()))
            _pass(ctx) = false;
    };

    // [66]
    auto const separate_in_line_def =
        +x3::blank | x3::raw[x3::eps][check_start_of_line];

    // 6.3. Line Prefixes

    auto block_context = [](auto & rule_ctx) {
        return rule_ctx.get().context_() == context::block_in ||
               rule_ctx.get().context_() == context::block_out;
    };

    auto flow_context = [](auto & rule_ctx) {
        return rule_ctx.get().context_() == context::flow_in ||
               rule_ctx.get().context_() == context::flow_out;
    };

    // [67]
    auto const line_prefix_def = x3::eps(block_context) >> indent |
                                 x3::eps(flow_context) >> indent >>
                                     -separate_in_line;

    // 6.4 Empty Lines

    // [70]
    auto const l_empty_def = x3::omit[line_prefix | indent_lt] >> x3::eol >>
                             x3::attr('\n');

    // 6.5 Line Folding

    auto dont_stop_at_doc_delimiter = [](auto & rule_ctx) {
        return !rule_ctx.get().stop_at_document_delimiter_;
    };

    // [73]
    auto const b_l_folded_def = x3::eol >>
                                (x3::eps(dont_stop_at_doc_delimiter) |
                                 !(x3::lit("...") | "---")) >>
                                (+l_empty /* b-l-trimmed [71] */
                                 | x3::attr(" "));

    auto set_context = [](context c) {
        return [c](auto & rule_ctx) {
            rule_ctx.get().context_stack_.back() = c;
            return true;
        };
    };

    // [74]
    // TODO: Prolly need to push the context here, not set it.
    auto const flow_folded_def = x3::eps(set_context(context::flow_in)) >>
                                 -separate_in_line >> b_l_folded >> line_prefix;

    // 6.6 Comments

    // [75]
    auto const comment_text_def = '#' >> +nb_char;

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
    auto const s_b_comment_def =
        -(separate_in_line >> -comment_text) >>
        (x3::eol | x3::eoi >> x3::eps(first_time_eoi)); // b-comment [77]

    // [78]
    auto const l_comment_def = separate_in_line >> -comment_text >>
                               (x3::eol | x3::eoi >> x3::eps(first_time_eoi));

    // [79]
    auto const s_l_comments_def =
        (s_b_comment | x3::raw[x3::eps][check_start_of_line]) >> *l_comment;

    // 6.7 Separation Lines

    auto key_context = [](auto & rule_ctx) {
        return rule_ctx.get().context_() == context::block_key ||
               rule_ctx.get().context_() == context::flow_key;
    };

    auto not_key_context = [](auto & rule_ctx) {
        return rule_ctx.get().context_() != context::block_key &&
               rule_ctx.get().context_() != context::flow_key;
    };

    // [80]
    auto const separate_def = x3::eps(key_context) >> separate_in_line |
                              x3::eps(not_key_context) >> separate_lines;

    // [81]
    auto const separate_lines_def =
        s_l_comments >> indent >> -separate_in_line // flow-line-prefix [69]
        | separate_in_line;

    // 6.8 Directives

    // [82]
    auto const directive_def =
        '%' >>
        (yaml_directive | tag_directive | reserved_directive) >> s_l_comments;

    auto reserved_directive_warning = [](auto & ctx) {
#if 0 // TODO
        auto const & error_handler =
            x3::get<yaml::error_handler_tag>(ctx).get();
#endif
        // TODO: Report warning.
    };

    // [83]
    auto const reserved_directive_def = x3::raw
        [+x3::omit[ns_char] >> *(+x3::omit[x3::blank] >> +x3::omit[ns_char])]
        [reserved_directive_warning];

    auto record_yaml_directive = [](auto & ctx) {
        auto & state = x3::get<parser_state_tag>(ctx).get();
        state.latest_yaml_directive_it_ = _attr(ctx).begin();
    };

    auto check_yaml_version = [](auto & ctx) {
        auto & state = x3::get<parser_state_tag>(ctx).get();
#if 0 // TODO
        auto const & error_handler =
            x3::get<yaml::error_handler_tag>(ctx).get();
#endif

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
            } else if (
                minor != 2 /* TODO && error_handler.impl().warning_fn_*/) {
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


    struct tag
    {
        // This allows parsing rules that use the tagparsing symbol table to
        // produce strings without semantic actions.
        operator std::string const &() const noexcept { return prefix_; }

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

    auto record_tag_handle = [](auto & ctx) {
        auto & state = x3::get<parser_state_tag>(ctx).get();
        state.tag_handle_ = _attr(ctx);
    };

    auto record_tag = [](auto & ctx) {
        auto & state = x3::get<parser_state_tag>(ctx).get();
#if 0 // TODO
        auto const & error_handler =
            x3::get<yaml::error_handler_tag>(ctx).get();
#endif

        using state_t = typename std::remove_reference<decltype(state)>::type;
        using cp_range = typename state_t::iterator_range;
        cp_range const handle_cp_range = state.tag_handle_;
        cp_range const prefix_cp_range = _attr(ctx);

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
    auto const tag_directive_def = "TAG" >> +x3::omit[x3::blank] >>
                                   x3::raw[tag_handle][record_tag_handle] >>
                                   +x3::omit[x3::blank] >>
                                   x3::raw[tag_prefix][record_tag];

    // [89]
    auto const tag_handle_def =
        // "alnum..." below is  word_char [38]
        '!' >> +(x3::alnum | x3::char_("-")) >> '!' // named_tag_handle [92]
        | "!!"                                      // secondary_tag_handle [91]
        | '!'                                       // primary_tag_handle [90]
        ;

    // [93]
    auto const tag_prefix_def = '!' >> *uri_char | tag_char >> *uri_char;


    // 6.9 Node Properties

    auto assign_tag_property = [](auto & ctx) {
        auto & state = x3::get<parser_state_tag>(ctx).get();
        state.tag_property_ = _attr(ctx);
    };
    auto assign_optional_tag_property = [](auto & ctx) {
        auto & state = x3::get<parser_state_tag>(ctx).get();
        state.tag_property_ = *_attr(ctx);
    };
    auto assign_anchor_property = [](auto & ctx) {
        auto & state = x3::get<parser_state_tag>(ctx).get();
        state.anchor_property_ = _attr(ctx);
    };
    auto assign_optional_anchor_property = [](auto & ctx) {
        auto & state = x3::get<parser_state_tag>(ctx).get();
        state.anchor_property_ = *_attr(ctx);
    };

    auto make_parser_properties = [](auto & ctx) {
        auto & state = x3::get<parser_state_tag>(ctx).get();
        _val(ctx) = parser_properties{std::move(state.tag_property_),
                                      std::move(state.anchor_property_)};
    };

    // [96]
    auto const properties_def =
        (tag_property[assign_tag_property] >>
             -(separate >> anchor_property[assign_optional_anchor_property]) |
         anchor_property[assign_anchor_property] >>
             -(separate >> tag_property[assign_optional_tag_property]))
            [make_parser_properties];

    // [97]
    auto const tag_property_def =
        "!<" > +uri_char[append_utf8] > '>' // verbatim_tag [98]
        | (tags >> +tag_char[append_utf8])  // shorthand_tag [99]
        | x3::lit('!') >> x3::attr("!")     // non_specific_tag [100]
        ;

    // [22]
    // auto indicator = char_("-?:,[]{}#&*!|>'\"%@`");

    auto make_iterator_range_any = [](auto & ctx) {
        any & result = _val(ctx);
        using state_t = typename std::remove_reference<decltype(
            x3::get<parser_state_tag>(ctx).get())>::type;
        typename state_t::iterator_range range = _attr(ctx);
        result = range;
    };

    // [101]
    auto const anchor_property_def =
        '&' >>
        x3::raw[+(ns_char - x3::char_(",[]{}"))][make_iterator_range_any];

    // [102]
    // auto anchor_char = ns_char - char_(",[]{}");

    // [103]
    auto const anchor_name_def =
        x3::raw[+(ns_char - x3::char_(",[]{}"))][make_iterator_range_any];

    auto const one_time_eoi_def = x3::eoi >> x3::eps(first_time_eoi);

    // 7.1 Alias Nodes

    struct anchors_t : x3::symbols<anchor>
    {};

    // TODO: -> context
    anchors_t anchors;

    auto alias_from_anchor = [](auto&ctx) {
        _val(ctx) = _attr(ctx).alias_;
    };

    // [104]
    auto const alias_node_def = '*' > anchors[alias_from_anchor];

    // 7.3 Flow Scalar Styles

    // 7.3.1 Double Quoted Style

    // [107]
    auto const nb_double_char_def =
        esc_char[append_utf8] | (nb_json - x3::char_("\"\\"))[append_utf8];

    // [108]
    auto const ns_double_char_def = nb_double_char - x3::blank;

    // [109]
    auto const double_quoted_def = '"' >> double_text >> '"';

    // [110]
    auto const double_text_def =
        x3::eps(flow_context) >> double_multi_line |
        x3::eps(key_context) >> *nb_double_char // double-one-line [111]
        ;

    // [112]
    // TODO: A hold[] was removed here; this may need a fix somewhere else.
    // TODO: Prolly need to push the context here, not set it.
    auto const double_escaped_def = *x3::blank >> '\\' >> x3::omit[x3::eol] >>
                                    x3::eps(set_context(context::flow_in)) >>
                                    *l_empty >> line_prefix;

    auto set_stop_at_doc_delimiter = [](bool b) {
        return [b](auto & rule_ctx) {
            rule_ctx.get().stop_at_document_delimiter_ = b;
            return true;
        };
    };

    // [113]
    auto const double_break_def =
        double_escaped |
        x3::eps(set_stop_at_doc_delimiter(false)) >> flow_folded;

    // [114]
    auto const double_in_line_def = *(*x3::blank >> ns_double_char);

    // [115]
    auto const double_next_line_def = double_break >>
                                      -(ns_double_char >> double_in_line >>
                                        (double_next_line | *x3::blank));

    // [116]
    auto const double_multi_line_def = double_in_line >>
                                       (double_next_line | *x3::blank);

    // 7.3.2 Single Quoted Style

    // [118]
    auto const nb_single_char_def = "''" >> x3::attr('\'') |
                                    (nb_json - '\'')[append_utf8];

    // [119]
    auto const ns_single_char_def = nb_single_char - x3::blank;

    // [120]
    auto const single_quoted_def = '\'' >> single_text >> '\'';

    // [121]
    auto const single_text_def = x3::eps(flow_context) >> single_multi_line |
                                 x3::eps(key_context) >> *nb_single_char;

    // [123]
    auto const single_in_line_def = *(*x3::blank >> ns_single_char);

    // [124]
    auto const single_next_line_def =
        x3::eps(set_stop_at_doc_delimiter(false)) >> flow_folded >>
        -(ns_single_char >> single_in_line >> (single_next_line | *x3::blank));

    // [125]
    auto const single_multi_line_def = single_in_line >>
                                       (single_next_line | *x3::blank);

    // 7.3.3 Plain Style

    // [22]
    // auto indicator = char_("-?:,[]{}#&*!|>'\"%@`");

    // [126]
    auto const plain_first_def = (ns_char - x3::char_("-?:,[]{}#&*!|>'\"%@`")) |
                                 (x3::char_("?:-") >> plain_safe);

    auto flow_out_block_key_context = [](auto & rule_ctx) {
        return rule_ctx.get().context_() == context::flow_out ||
               rule_ctx.get().context_() == context::block_key;
    };

    auto flow_in_key_context = [](auto & rule_ctx) {
        return rule_ctx.get().context_() == context::flow_in ||
               rule_ctx.get().context_() == context::flow_key;
    };

    // [127]
    auto const plain_safe_def = x3::eps(flow_out_block_key_context) >> ns_char |
                                x3::eps(flow_in_key_context) >>
                                    (ns_char - x3::char_(",[]{}"));
    auto const not_plain_safe_def =
        !(x3::eps(flow_out_block_key_context) >> raw_ns_char |
          x3::eps(flow_in_key_context) >> (raw_ns_char - x3::char_(",[]{}")));

    // [130]
    auto const plain_char_def =
        ns_char >> x3::char_('#') | x3::char_(':') >> plain_safe
        | plain_safe - x3::char_(":#");

    // [131]
    auto const plain_def = x3::eps(flow_context) >> plain_multi_line |
                           x3::eps(key_context) >> plain_one_line;

    // [132]
    // TODO: Removed hold[].
    auto const plain_in_line_def = *(*x3::blank >> plain_char);

    // [133]
    // TODO: Removed hold[].
    auto const plain_one_line_def = plain_first >> plain_in_line;

    // [134]
    // TODO: Removed hold[].
    auto const plain_next_line_def = x3::eps(set_stop_at_doc_delimiter(true)) >>
                                     flow_folded >> plain_char >> plain_in_line;

    // [135]
    auto const plain_multi_line_def = plain_one_line >> *plain_next_line;

    // 7.4 Flow Collection Styles

    // 7.4.1 Flow Sequences

    auto seq_init = [](auto & ctx) {
        auto & state = x3::get<parser_state_tag>(ctx).get();
        if (state.max_recursive_open_count_ < ++state.recursive_open_count_)
            _pass(ctx) = false;
        else
            _val(ctx) = seq();
    };
    auto seq_append = [](auto & ctx) {
        value & v = _val(ctx);
        get<seq>(v).push_back(std::move(_attr(ctx)));
    };

    // [137]
    auto const flow_sequence_def = // !
        '[' >> -separate >> push_in_flow_context >>
        (flow_seq_entries | x3::attr(value(seq()))) >> pop_context >> -separate
        >> ']';

    // [138]
    auto const flow_seq_entries_def = x3::eps[seq_init] >> // !
                                      flow_seq_entry[seq_append] %
                                          (-separate >> ',' >> -separate) >>
                                      -(-separate >> ',');

    // [139]
    auto const flow_seq_entry_def = flow_pair | flow_node; // !

    // 7.4.2 Flow Mappings

    auto map_init = [](auto & ctx) {
        auto & state = x3::get<parser_state_tag>(ctx).get();
        if (state.max_recursive_open_count_ < ++state.recursive_open_count_)
            _pass(ctx) = false;
        else
            _val(ctx) = map();
    };
    auto map_insert = [](auto & ctx) {
        value & v = _val(ctx);
        get<map>(v).insert(std::make_pair(
            std::move(fusion::at_c<0>(_attr(ctx))),
            std::move(fusion::at_c<1>(_attr(ctx)))));
    };

    // [140]
    auto const flow_mapping_def = '{' >> -separate >> push_in_flow_context >> // !
                                  (flow_map_entries | x3::attr(value(map()))) >>
                                  pop_context >> -separate >> '}';

    // [141]
    auto const flow_map_entries_def = x3::eps[map_init] >> // !
                                      flow_map_entry[map_insert] %
                                          (-separate >> ',' >> -separate) >>
                                      -(-separate >> ',');

    // [142]
    auto const flow_map_entry_def = // !
        '?' >> separate >> flow_map_explicit_entry | flow_map_implicit_entry;

    // [143]
    auto const flow_map_explicit_entry_def = // !
        flow_map_implicit_entry | x3::attr(map_element());

    // [144]
    auto const flow_map_implicit_entry_def = flow_map_json_key_entry | // !
                                             flow_map_yaml_key_entry |
                                             flow_map_empty_key_entry;

    // [145]
    auto const flow_map_yaml_key_entry_def = // !
        flow_yaml_node >>
        (-separate >> flow_map_separate_value |
         x3::attr(value()));

    // [146]
    auto const flow_map_empty_key_entry_def = // !
        x3::attr(value()) >> flow_map_separate_value;

    // [147]
    auto const flow_map_separate_value_def = ':' >> not_plain_safe >> // !
                                             (separate >> flow_node |
                                              x3::attr(value()));

    // [148]
    auto const flow_map_json_key_entry_def = flow_json_node >> // !
                                             (-separate >>
                                                  flow_map_adjacent_value |
                                              x3::attr(value()));

    // [149]
    auto const flow_map_adjacent_value_def = ':' >>
                                             (-separate >> flow_node | // !
                                              x3::attr(value()));

    auto value_from_map_from_element = [](auto & ctx) {
        _val(ctx) = map();
        map_element & element = _attr(ctx);
        get<map>(_val(ctx)).emplace(
            std::move(element.first), std::move(element.second));
    };

    // [150]
    auto const
        flow_pair_def = '?' >> separate >> // !
                            flow_map_explicit_entry[value_from_map_from_element] |
                        flow_pair_entry[value_from_map_from_element];

    // [151]
    auto const flow_pair_entry_def = flow_pair_yaml_key_entry | // !
                                     flow_map_empty_key_entry |
                                     flow_pair_json_key_entry;

    // [152]
    auto const flow_pair_yaml_key_entry_def = // !
        implicit_yaml_key >> flow_map_separate_value;

    // [153]
    auto const flow_pair_json_key_entry_def = // !
        implicit_json_key >> flow_map_adjacent_value;

    auto push_indent = [](int i) {
        return [i](auto & rule_ctx) {
            rule_ctx.get().indent_stack_.push_back(i);
            return true;
        };
    };

    // [154]
    auto const implicit_yaml_key_def = // TODO: Limit to 1024 characters. // !
        x3::eps(push_indent(0)) >> flow_yaml_node >> -separate_in_line >>
        pop_indent;

    // [155]
    auto const implicit_json_key_def = // TODO: Limit to 1024 characters. // !
        x3::eps(push_indent(0)) >> flow_json_node >> -separate_in_line >>
        pop_indent;

    // 7.5 Flow Nodes

    // [156]
    // flow_yaml_content = plain;

#define BOOST_YAML_FLOW_YAML_CONTENT plain

    // [157]
    auto const flow_json_content_def =
        flow_sequence | flow_mapping |
        single_quoted | double_quoted;

    // [158]
    auto const flow_content_def =
        flow_json_content | BOOST_YAML_FLOW_YAML_CONTENT;

    // TODO: Use Niabelek trick to perform a typesafe parse after properties.

    auto handle_properties = [](auto & ctx) {
        // TODO
#if 0
        ast::properties_t properties;
        properties.tag_ = parser_properties.tag_;

        if (!parser_properties.anchor_.empty()) {
            properties.anchor_ = range_to_string(parser_properties.anchor_);

            anchor_t anchor;
            std::shared_ptr<ast::value_t> anchor_ptr(new ast::value_t(x));
            anchor.alias_ = ast::alias_t(properties.anchor_, anchor_ptr);
            anchor.position_ = parser_properties.anchor_.begin();

            auto existing_anchor = anchors.find(properties.anchor_);
            if (existing_anchor && error_handler.impl().warning_fn_) {
                std::ostringstream oss;
                oss << "Redefining anchor " << properties.anchor_;
                error_handler.impl().report_warning_at(
                    parser_properties.anchor_.begin(), oss.str());
                error_handler.impl().report_warning_at(
                    existing_anchor->position_,
                    "The previous one was was here");
            }

            anchors.remove(properties.anchor_);
            anchors.add(properties.anchor_, anchor);
        }

        if (properties)
            return ast::value_t(
                ast::properties_node_t(properties, ast::value_t(x)));

        return ast::value_t(x);
#endif
    };

    // [159]
    auto const flow_yaml_node_def = x3::attr(value());
#if 0 // TODO
        alias_node | BOOST_YAML_FLOW_YAML_CONTENT |
        (properties >> (separate >> BOOST_YAML_FLOW_YAML_CONTENT |
                        x3::attr(value())))[handle_properties];
#endif

#undef BOOST_YAML_FLOW_YAML_CONTENT

    auto handle_optional_properties = [](auto & ctx) {
        // TODO
    };

    // [160]
    auto const flow_json_node_def = x3::attr(value());
#if 0 // TODO
        (-(properties >> separate) >>
         flow_json_content)[handle_optional_properties];
#endif

    // [161]
    auto const flow_node_def = x3::attr(value());
#if 0 // TODO
        alias_node | flow_content |
        (properties >>
         (separate >> flow_content | x3::attr(value())))[handle_properties];
#endif



    // Helper rules.
    BOOST_SPIRIT_DEFINE(
        two_hex_digits,
        four_hex_digits,
        eight_hex_digits,
        x_escape_seq,
        u_escape_seq,
        U_escape_seq,
        push_in_flow_context,
        pop_context,
        pop_indent);

    // Characters.
    BOOST_SPIRIT_DEFINE(
        printable,
        nb_json,
        bom,
        nb_char,
        ns_char,
        raw_ns_char,
        word_char,
        uri_char,
        tag_char,
        single_escaped_char,
        esc_char);

    // Basic structures.
    BOOST_SPIRIT_DEFINE(
        indent,
        indent_lt,
        indent_le,
        separate_in_line,
        line_prefix,
        l_empty,
        b_l_folded,
        flow_folded,
        comment_text,
        s_b_comment,
        l_comment,
        s_l_comments,
        separate,
        separate_lines,
        directive,
        reserved_directive,
        yaml_directive,
        tag_directive,
        tag_handle,
        tag_prefix,
        properties,
        tag_property,
        anchor_property,
        anchor_name,
        one_time_eoi);

    // Flow styles.
    BOOST_SPIRIT_DEFINE(
        alias_node,
        nb_double_char,
        ns_double_char,
        double_quoted,
        double_text,
        double_escaped,
        double_break,
        double_in_line,
        double_next_line,
        double_multi_line,
        nb_single_char,
        ns_single_char,
        single_quoted,
        single_text,
        single_in_line,
        single_next_line,
        single_multi_line,
        plain_first,
        plain_safe,
        not_plain_safe,
        plain_char,
        plain,
        plain_in_line,
        plain_one_line,
        plain_next_line,
        plain_multi_line,
        flow_sequence,
        flow_seq_entries,
        flow_seq_entry,
        flow_mapping,
        flow_map_entries,
        flow_map_entry,
        flow_map_explicit_entry,
        flow_map_implicit_entry,
        flow_map_yaml_key_entry,
        flow_map_empty_key_entry,
        flow_map_separate_value,
        flow_map_json_key_entry,
        flow_map_adjacent_value,
        flow_pair,
        flow_pair_entry,
        flow_pair_yaml_key_entry,
        flow_pair_json_key_entry,
        implicit_yaml_key,
        implicit_json_key,
        flow_json_content,
        flow_content,
        flow_yaml_node,
        flow_json_node,
        flow_node);



    // TODO
    struct test_parser_struct;
    x3::rule<test_parser_struct> const test = "test";
    auto const test_def = flow_yaml_node; // flow_json_node flow_node // TODO
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
        string_view const & str, error_function parse_error, int max_recursion)
    {
        auto const range = text::make_to_utf32_range(str);
        using iter_t = decltype(range.begin());
        auto first = range.begin();
        auto const last = range.end();

        if (max_recursion <= 0)
            max_recursion = INT_MAX;

        yaml::x3_error_handler<iter_t> error_handler{first, last, parse_error};
        parser_state<iter_t> state(max_recursion);

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
