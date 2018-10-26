#include <boost/yaml/yaml.hpp>
#include <boost/parser/parser.hpp>

#include <boost/container/small_vector.hpp>
#include <boost/any.hpp>


namespace boost { namespace yaml {

    namespace bp = ::boost::parser;
    using namespace bp::literals;

    // Parser enums.

    enum class context {
        block_in,
        block_out,
        flow_in,
        flow_out,
        block_key,
        flow_key
    };

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

    inline std::ostream & operator<<(std::ostream & os, chomping c)
    {
        switch (c) {
        case chomping::strip: return os << "strip";
        case chomping::clip: return os << "clip";
        case chomping::keep: return os << "keep";
        }
        return os;
    }

    enum class eoi_state { not_at_end, at_end };

    inline std::ostream & operator<<(std::ostream & os, eoi_state s)
    {
        return os << (s == eoi_state::not_at_end ? "not_at_end" : "at_end");
    }

    struct block_header_t
    {
        int indentation_;
        chomping chomping_;
    };

    inline std::ostream & operator<<(std::ostream & os, block_header_t b)
    {
        return os << b.indentation_ << ',' << b.chomping_;
    }

    struct parser_properties
    {
        std::string tag_;
        any anchor_; // iterator range
    };

    inline std::ostream &
    operator<<(std::ostream & out, parser_properties const & p)
    {
        return out << p.tag_ << ",<<unprintable-pos>>";
    }

    struct anchor
    {
        alias alias_;
        any position_; // iterator
    };

    inline std::ostream & operator<<(std::ostream & out, anchor const & a)
    {
        return out << '&' << a.alias_.first << ",<<unprintable-pos>>";
    }



    // State to track during the parse.

    template<typename Iter>
    struct global_state
    {
        using iterator = Iter;
        using iterator_range = parser::range<Iter>;

        global_state(iterator first, int max_recursion) :
            first_(first),
            max_recursive_open_count_(max_recursion)
        {
#if 0
            indent_stack_.push_back(0);                  // TODO
            context_stack_.push_back(context::block_in); // TODO
#endif
        }

#if 0
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
#endif

        iterator const first_;
        int recursive_open_count_ = 0;
        int const max_recursive_open_count_;

#if 1
        int indent_ = 0; // TODO
        context context_ = context::block_in; // TODO
#else
        std::vector<int> indent_stack_;
        std::vector<context> context_stack_;
#endif
        bool stop_at_document_delimiter_ = false;

        eoi_state eoi_state_ = eoi_state::not_at_end;

        bool yaml_directive_seen_ = false;
        iterator first_yaml_directive_it_;
        iterator latest_yaml_directive_it_;

        std::string tag_handle_;
        iterator tag_handle_it_;

        std::string tag_property_;
        iterator_range anchor_property_;
    };


    // Helper rules.

    bp::rule<class x_escape_seq, uint32_t> const x_escape_seq =
        "\\xXX hexidecimal escape sequence";
    bp::rule<class u_escape_seq, uint32_t> const u_escape_seq =
        "\\uXXXX hexidecimal escape sequence";
    bp::rule<class U_escape_seq, uint32_t> const U_escape_seq =
        "\\UXXXXXXXX hexidecimal escape sequence";
    bp::rule<class single_escaped_char, uint32_t> const single_escaped_char =
        "'0', 'a', 'b', 't', 'n', 'v', 'f', 'r', 'e', '\"', '/', '\\', 'N', "
        "'_', 'L', 'P', SPACE or TAB";

    bp::rule<class one_time_eoi> const one_time_eoi = "end of input";



    // 5.2. Character Encodings

    // [1]
    bp::rule<class printable, uint32_t> const printable = "printable";

    // [2]
    bp::rule<class ws, uint32_t> const nb_json = "nb_json";

    // [3]
    bp::rule<class bom> const bom = "bom";

    // 5.4. Line Break Characters

    // [27]
    bp::rule<class nb_char, uint32_t> const nb_char = "nb_char";

    // 5.5. White Space Characters

    // [34]
    bp::rule<class ns_char, std::string> const ns_char = "ns_char";
    bp::rule<class raw_ns_char, std::string> const raw_ns_char = "ns_char";

    // 5.6. Miscellaneous Characters

    // [38]
    bp::rule<class word_char, uint32_t> const word_char = "word_char";

    // [39]
    bp::rule<class uri_char, uint32_t> const uri_char = "uri_char";

    // [40]
    bp::rule<class tag_char, uint32_t> const tag_char = "tag_char";

    // 5.7. Escaped Characters

    // [62]
    bp::rule<class esc_char, uint32_t> const esc_char = "esc_char";

    // 6.1. Indentation Spaces

    // [63]
    bp::rule<class indent> const indent = "indent";

    // [64]
    bp::rule<class indent_lt> const indent_lt = "indent_lt";

    // [65]
    bp::rule<class indent_le> const indent_le = "indent_le";

    // 6.2. Separation Spaces

    // [66]
    bp::rule<class separate_in_line> const separate_in_line =
        "separate_in_line";

    // 6.3. Line Prefixes

    // [67]
    bp::rule<class line_prefix> const line_prefix = "line_prefix";

    // 6.4 Empty Lines

    // [70]
    bp::rule<class l_empty, uint32_t> const l_empty = "l_empty";

    // 6.5 Line Folding

    // [73]
    bp::rule<class b_l_folded, std::string> const b_l_folded = "b_l_folded";

    // [74]
    bp::rule<class flow_folded, std::string> const flow_folded = "flow_folded";

    // 6.6 Comments

    // [75]
    bp::rule<class comment_text> const comment_text = "comment_text";

    // [77]
    bp::rule<class s_b_comment> const s_b_comment = "s_b_comment";

    // [78]
    bp::rule<class l_comment> const l_comment = "l_comment";

    // [79]
    bp::rule<class s_l_comments> const s_l_comments = "s_l_comments";

    // 6.7 Separation Lines

    // [80]
    bp::rule<class separate> const separate = "separate";

    // [81]
    bp::rule<class separate_lines> const separate_lines = "separate_lines";

    // 6.8 Directives

    // [82]
    bp::rule<class directive> const directive = "directive";

    // [83]
    bp::rule<class reserved_directive, std::string> const reserved_directive =
        "reserved_directive";

    // [86]
    struct yaml_directive_state
    {
        any position_range_; // iterator range
        int version_;
    };
    bp::rule<class yaml_directive, bp::no_attribute, yaml_directive_state> const
        yaml_directive = "yaml_directive";

    // [88]
    // any as iterator_range
    bp::rule<class tag_directive> const tag_directive = "tag_directive";

    // [89]
    bp::rule<class tag_handle, std::string> const tag_handle = "tag_handle";

    // [93]
    bp::rule<class tag_prefix, std::string> const tag_prefix = "tag_prefix";

    // 6.9 Node Properties

    // [96]
    struct properties_state
    {
        std::string str_; // TODO: Needs name.
        any position_;    // iterator range
    };
    bp::rule<class properties_t, parser_properties, properties_state> const
        properties = "properties";

    // [97]
    bp::rule<class shorthand_tag_name, std::string> const shorthand_tag_name =
        "shorthand_tag_name";
    bp::rule<class tag_property, std::string> const tag_property =
        "tag_property";

    // [22]
    // auto indicator = cp("-?:,[]{}#&*!|>'\"%@`");

    // [101]
    bp::rule<class anchor_property> const anchor_property = "anchor_property";

    // [102]
    // auto anchor_char = ns_char - cp(",[]{}");

    // [103]
    bp::rule<class anchor_name, any> const anchor_name = "anchor_name";

    // 7.1 Alias Nodes

    // [104]
    bp::rule<class alias_node, alias> const alias_node = "alias_node";

    // 7.3 Flow Scalar Styles

    // 7.3.1 Double Quoted Style

    // [107]
    bp::rule<class nb_double_char, std::string> const nb_double_char =
        "nb_double_char";

    // [108]
    bp::rule<class ns_double_char, std::string> const ns_double_char =
        "ns_double_char";

    // [109]
    bp::rule<class double_quoted, std::string> const double_quoted =
        "double_quoted";

    // [110]
    bp::rule<class double_text, std::string> const double_text = "double_text";

    // [112]
    bp::rule<class double_escaped, std::string> const double_escaped =
        "double_escaped";

    // [113]
    bp::rule<class double_break, std::string> const double_break =
        "double_break";

    // [114]
    bp::rule<class double_in_line, std::string> const double_in_line =
        "double_in_line";

    // [115]
    bp::rule<class double_next_line, std::string> const double_next_line =
        "double_next_line";

    // [116]
    bp::rule<class double_multi_line, std::string> const double_multi_line =
        "double_multi_line";

    // 7.3.2 Single Quoted Style

    // [118]
    bp::rule<class nb_single_char, std::string> const nb_single_char =
        "nb_single_char";

    // [119]
    bp::rule<class ns_single_char, std::string> const ns_single_char =
        "ns_single_char";

    // [120]
    bp::rule<class single_quoted, std::string> const single_quoted =
        "single_quoted";

    // [121]
    bp::rule<class single_text, std::string> const single_text = "single_text";

    // [123]
    bp::rule<class single_in_line, std::string> const single_in_line =
        "single_in_line";

    // [124]
    bp::rule<class single_next_line, std::string> const single_next_line =
        "single_next_line";

    // [125]
    bp::rule<class single_multi_line, std::string> const single_multi_line =
        "single_multi_line";

    // 7.3.3 Plain Style

    // [22]
    bp::rule<class indicator> const indicator = "indicator";

    // [126]
    bp::rule<class plain_first, std::string> const plain_first = "plain_first";

    // [127]
    bp::rule<class plain_safe, std::string> const plain_safe = "plain_safe";
    bp::rule<class not_plain_safe> const not_plain_safe = "not_plain_safe";

    // [130]
    bp::rule<class plain_char, std::string> const plain_char = "plain_char";

    // [131]
    bp::rule<class plain, std::string> const plain = "plain";

    // [132]
    bp::rule<class plain_in_line, std::string> const plain_in_line =
        "plain_in_line";

    // [133]
    bp::rule<class plain_one_line, std::string> const plain_one_line =
        "plain_one_line";

    // [134]
    bp::rule<class plain_next_line, std::string> const plain_next_line =
        "plain_next_line";

    // [135]
    bp::rule<class plain_multi_line, std::string> const plain_multi_line =
        "plain_multi_line";


    // 7.4 Flow Collection Styles

    // [137]
    bp::rule<class flow_sequence, value> const flow_sequence = "flow_sequence";

    // [138]
    bp::rule<class flow_seq_entries, value> const flow_seq_entries =
        "flow_seq_entries";

    // [139]
    bp::rule<class flow_seq_entry, value> const flow_seq_entry =
        "flow_seq_entry";

    // 7.4.2 Flow Mappings

    // [140]
    bp::rule<class flow_mapping, value> const flow_mapping = "flow_mapping";

    // [141]
    bp::rule<class flow_map_entries, value> const flow_map_entries =
        "flow_map_entries";

    // [142]
    bp::rule<class flow_map_entry, map_element> const flow_map_entry =
        "flow_map_entry";

    // [143]
    bp::rule<class flow_map_explicit_entry, map_element> const
        flow_map_explicit_entry = "flow_map_explicit_entry";

    // [144]
    bp::rule<class flow_map_implicit_entry, map_element> const
        flow_map_implicit_entry = "flow_map_implicit_entry";

    // [145]
    bp::rule<class flow_map_yaml_key_entry, map_element> const
        flow_map_yaml_key_entry = "flow_map_yaml_key_entry";

    // [146]
    bp::rule<class flow_map_empty_key_entry, map_element> const
        flow_map_empty_key_entry = "flow_map_empty_key_entry";

    // [147]
    bp::rule<class flow_map_separate_value, value> const
        flow_map_separate_value = "flow_map_separate_value";

    // [148]
    bp::rule<class flow_map_json_key_entry, map_element> const
        flow_map_json_key_entry = "flow_map_json_key_entry";

    // [149]
    bp::rule<class flow_map_adjacent_value, value> const
        flow_map_adjacent_value = "flow_map_adjacent_value";

    // [150]
    bp::rule<class flow_pair, value> const flow_pair = "flow_pair";

    // [151]
    bp::rule<class flow_pair_entry, map_element> const flow_pair_entry =
        "flow_pair_entry";

    // [152]
    bp::rule<class flow_pair_yaml_key_entry, map_element> const
        flow_pair_yaml_key_entry = "flow_pair_yaml_key_entry";

    // [153]
    bp::rule<class flow_pair_json_key_entry, map_element> const
        flow_pair_json_key_entry = "flow_pair_json_key_entry";

    // [154]
    bp::rule<class implicit_yaml_key, value> const implicit_yaml_key =
        "implicit_yaml_key";

    // [155]
    bp::rule<class implicit_json_key, value> const implicit_json_key =
        "implicit_json_key";

    // 7.5 Flow Nodes

    // [156]
    // flow_yaml_content = plain

    // [157]
    bp::rule<class flow_json_content, value> const flow_json_content =
        "flow_json_content";

    // [158]
    bp::rule<class flow_content, value> const flow_content = "flow_content";

    // [159]
    bp::rule<class flow_yaml_node, value> const flow_yaml_node =
        "flow_yaml_node";

    // [160]
    bp::rule<class flow_json_node, value> const flow_json_node =
        "flow_json_node";

    // [161]
    bp::rule<class flow_node, value> const flow_node = "flow_node";

    // 8.1 Block Scalar Styles

    // [162]
    bp::rule<class block_header, block_header_t> const block_header =
        "block_header";

    // [163]
    bp::rule<class indentation_indicator, int> const indentation_indicator =
        "indentation_indicator";

    // [164]
    bp::rule<class chomping_indicator, chomping> const chomping_indicator =
        "chomping_indicator";

    // [165]
    bp::rule<class chomped_last, std::string> const chomped_last =
        "chomped_last";

    // [166]
    bp::rule<class chomped_empty> const chomped_empty = "chomped_empty";

    // [167]
    bp::rule<class strip_empty> const strip_empty = "strip_empty";

    // [168]
    bp::rule<class keep_empty, std::string> const keep_empty = "keep_empty";

    // [169]
    bp::rule<class trail_comments> const trail_comments = "trail_comments";

    // [170]
    bp::rule<class literal, std::string> const literal = "literal";

    // [171]
    bp::rule<class literal_text, std::string> const literal_text =
        "literal_text";

    // [172]
    bp::rule<class literal_next, std::string> const literal_next =
        "literal_next";

    bp::rule<class literal_content_optional, std::string> const
        literal_content_optional = "literal_content_optional";

    // [173]
    bp::rule<class literal_content, std::string> const literal_content =
        "literal_content";

    // 8.1.3. Folded Style

    // [174]
    bp::rule<class folded, std::string> const folded = "folded";

    // [175]
    bp::rule<class folded_text, std::string> const folded_text = "folded_text";

    // [176]
    bp::rule<class folded_lines, std::string> const folded_lines =
        "folded_lines";

    // [177]
    bp::rule<class spaced_text, std::string> const spaced_text = "spaced_text";

    // [178]
    bp::rule<class spaced, std::string> const spaced = "spaced";

    // [179]
    bp::rule<class spaced_lines, std::string> const spaced_lines =
        "spaced_lines";

    // [180]
    bp::rule<class same_lines, std::string> const same_lines = "same_lines";

    // [181]
    bp::rule<class diff_lines, std::string> const diff_lines = "diff_lines";

    bp::rule<class folded_content_optional, std::string> const
        folded_content_optional = "folded_content_optional";

    // [182]
    bp::rule<class folded_content, std::string> const folded_content =
        "folded_content";

    // 8.2.1. Block Sequences

    bp::rule<class auto_detect_indent, int> const auto_detect_indent =
        "auto_detect_indent";

    bp::rule<class scalar_auto_detect_indent, int> const
        scalar_auto_detect_indent = "scalar_auto_detect_indent";

    // [183]
    bp::rule<class block_sequence, seq> const block_sequence = "block_sequence";

    // [184]
    bp::rule<class block_seq_entry, value> const block_seq_entry =
        "block_seq_entry";

    // [185]
    bp::rule<class block_indented, value> const block_indented =
        "block_indented";

    // [186]
    bp::rule<class compact_sequence, seq> const compact_sequence =
        "compact_sequence";

    // 8.2.1. Block Mappings

    // [187]
    bp::rule<class block_mapping, map> const block_mapping = "block_mapping";

    // [188]
    bp::rule<class block_map_entry, map_element> const block_map_entry =
        "block_map_entry";

    // [189]
    bp::rule<class block_map_explicit_entry, map_element> const
        block_map_explicit_entry = "block_map_explicit_entry";

    // [190]
    bp::rule<class block_map_explicit_key, value> const block_map_explicit_key =
        "block_map_explicit_key";

    // [191]
    bp::rule<class block_map_explicit_value, value> const
        block_map_explicit_value = "block_map_explicit_value";

    // [192]
    bp::rule<class block_map_implicit_entry, map_element> const
        block_map_implicit_entry = "block_map_implicit_entry";

    // [193]
    bp::rule<class block_map_implicit_key, value> const block_map_implicit_key =
        "block_map_implicit_key";

    // [194]
    bp::rule<class block_map_implicit_value, value> const
        block_map_implicit_value = "block_map_implicit_value";

    // [195]
    bp::rule<class compact_mapping, map> const compact_mapping =
        "compact_mapping";

    // 8.2.3. Block Nodes

    // [196]
    bp::rule<class block_node, value> const block_node = "block_node";

    // [197]
    bp::rule<class flow_in_block, value> const flow_in_block = "flow_in_block";

    // [198]
    bp::rule<class block_in_block, value> const block_in_block =
        "block_in_block";

    // [199]
    bp::rule<class block_scalar, value> const block_scalar = "block_scalar";

    // [200]
    bp::rule<class block_collection, value> const block_collection =
        "block_collection";


    // [202]
    bp::rule<class document_prefix> const document_prefix = "document_prefix";

    // [205]
    bp::rule<class document_suffix> const document_suffix = "document_suffix";

    // [206]
    bp::rule<class forbidden> const forbidden = "forbidden";

    // [207]
    bp::rule<class bare_document, value> const bare_document = "bare_document";

    // [208]
    bp::rule<class explicit_document, value> const explicit_document =
        "explicit_document";

    // [209]
    bp::rule<class directive_document, value> const directive_document =
        "directive_document";

    // [210]
    bp::rule<class any_document, value> const any_document = "any_document";

    // [211]
    bp::rule<class yaml_stream, std::vector<value>> const yaml_stream =
        "yaml_stream";

    bp::rule<class end_of_input> const end_of_input = "end_of_input";



    // Definitions

    bp::parser_interface<bp::uint_parser<unsigned int, 16, 2, 2>> const hex_2;
    bp::parser_interface<bp::uint_parser<unsigned int, 16, 4, 4>> const hex_4;
    bp::parser_interface<bp::uint_parser<unsigned int, 16, 8, 8>> const hex_8;

    auto const x_escape_seq_def = "\\x" > hex_2;
    auto const u_escape_seq_def = "\\u" > hex_4;
    auto const U_escape_seq_def = "\\U" > hex_8;



    // 5.2. Character Encodings

    // [1]
    auto const printable_def = bp::char_("\t\n\f") | bp::char_('\x20', '\x7e') |
                               bp::char_(0x0085u) | // TODO: char_ -> cp?
                               bp::char_(0x00a0u, 0xd7ffu) |
                               bp::char_(0xe000u, 0xfffdu) |
                               bp::char_(0x00010000u, 0x0010ffffu);

    // [2]
    auto const nb_json_def = bp::char_('\t') | bp::char_(0x0020u, 0x0010ffffu);

    // [3]
    auto const bom_def = bp::char_(0xfeff);

    // 5.4. Line Break Characters

    // [27]
    auto const nb_char_def = printable - bp::eol - bom;

    // 5.5. White Space Characters

    // [34]
    auto const ns_char_def = nb_char_def - bp::ascii::blank;
    auto const raw_ns_char_def = nb_char_def - bp::ascii::blank;

    // 5.6. Miscellaneous Characters

    // [38]
    auto const word_char_def = bp::ascii::alnum | bp::char_('-');

    // [39]
    auto const uri_char_def = bp::char_('%') >> &hex_2 | word_char |
                              bp::char_("#;/?:@&=+$,_.!~*'()[]");

    // [40]
    auto const tag_char_def =
        uri_char - bp::char_("!,[]{}"); // - '!' - flow_indicator [23]

    // 5.7. Escaped Characters

    // [62]
    bp::symbols<uint32_t> const single_escaped_char_def = {{"0", 0x0000u},
                                                           {"a", 0x0007u},
                                                           {"b", 0x0008u},
                                                           {"t", 0x0009u},
                                                           {"\t", 0x0009u},
                                                           {"n", 0x000au},
                                                           {"v", 0x000bu},
                                                           {"f", 0x000cu},
                                                           {"r", 0x000du},
                                                           {"e", 0x001bu},
                                                           {" ", 0x0020u},
                                                           {"\"", 0x0022u},
                                                           {"/", 0x002fu},
                                                           {"\\", 0x005cu},
                                                           {"N", 0x0085u},
                                                           {"_", 0x00a0u},
                                                           {"L", 0x2028u},
                                                           {"P", 0x2029u}};

    auto const esc_char_def = x_escape_seq | u_escape_seq | U_escape_seq |
                              '\\'_l > single_escaped_char;



    // 6.1. Indentation Spaces

    auto indent_ = [](auto & ctx) { return _globals(ctx).indent_; };
    auto indent_minus_1 = [](auto & ctx) { return _globals(ctx).indent_; };

    // [63]
    auto const indent_def = bp::repeat(indent_)[' '_l];

    // [64]
    auto const indent_lt_def = bp::repeat(0, indent_minus_1)[' '_l];

    // [65]
    auto const indent_le_def = bp::repeat(0, indent_)[' '_l];

    // 6.2. Separation Spaces

    auto at_start_of_line = [](auto & ctx) {
        auto const iter_range = _where(ctx);
        if (iter_range.begin() == _globals(ctx).first_)
            return true;
        auto const cp = *std::prev(iter_range.begin());
        return std::find(
                   parser::detail::eol_cps.begin(),
                   parser::detail::eol_cps.end(),
                   cp) == parser::detail::eol_cps.end();
    };

    // [66]
    auto const separate_in_line_def =
        +bp::ascii::blank | bp::eps(at_start_of_line);

    // 6.3. Line Prefixes

    auto context_ = [](auto & ctx) { return _globals(ctx).context_; };

    // [67]
    // clang-format off
    auto const line_prefix_def = bp::switch_(context_)
        (context::block_in, indent)
        (context::block_out, indent)
        (context::flow_in, indent >> -separate_in_line)
        (context::flow_out, indent >> -separate_in_line);
    // clang-format on

    // 6.4 Empty Lines

    // [70]
    auto const l_empty_def = (line_prefix | indent_lt) >> bp::eol >>
                             bp::attr('\n');

    // 6.5 Line Folding

    auto dont_stop_at_doc_delimiter = [](auto & ctx) {
        return !_globals(ctx).stop_at_document_delimiter_;
    };

    // [73]
    auto const b_l_folded_def = bp::eol >>
                                (bp::eps(dont_stop_at_doc_delimiter) |
                                 !(bp::lit("...") | "---")) >>
                                (+l_empty /* b-l-trimmed [71] */
                                 | bp::attr(" "));

    auto set_context = [](context c) {
        return [c](auto & ctx) {
            _globals(ctx).context_ = c;
            return true;
        };
    };

    // [74]
    auto const flow_folded_def = bp::eps(set_context(context::flow_in)) >>
                                 -separate_in_line >> b_l_folded >> line_prefix;

    // 6.6 Comments

    // [75]
    auto const comment_text_def = '#' >> +nb_char;

    // HACK!  This is a dirty, dirty hack that bears explaining.  Many
    // productions in the YAML 1.2 spec include "newline | end-of-input"
    // (e.g. b-comment).  This poses a problem, since many of the uses of this
    // construct (say, using b-comment) are repeated via Kleene star.  The
    // parser consumes a character when parsing a newline (bp::eol), but *not*
    // when parsing end-of-input (bp::eoi).
    //
    // So, when a rule contains, say, *b-comment, infinite looping results,
    // since bp::eoi succeeds without advancing the parser's read position.
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
    auto first_time_eoi = [](auto & ctx) {
        auto & state = _globals(ctx).eoi_state_;
        bool const retval = state == eoi_state::not_at_end;
        state = eoi_state::at_end;
        return retval;
    };

    // [77]
    auto const s_b_comment_def =
        -(separate_in_line >> -comment_text) >>
        (bp::eol | bp::eoi >> bp::eps(first_time_eoi)); // b-comment [77]

    // [78]
    auto const l_comment_def = separate_in_line >> -comment_text >>
                               (bp::eol | bp::eoi >> bp::eps(first_time_eoi));

    // [79]
    auto const s_l_comments_def =
        (s_b_comment | bp::eps(at_start_of_line)) >> *l_comment;

    // 6.7 Separation Lines

    // [80]
    // clang-format off
    auto const separate_def = bp::switch_(context_)
        (context::block_key, separate_in_line)
        (context::flow_key, separate_in_line)
        (context::block_key, separate_lines)
        (context::flow_key, separate_lines);
    // clang-format on

    // [81]
    auto const separate_lines_def =
        s_l_comments >> indent >> -separate_in_line // flow-line-prefix [69]
        | separate_in_line;

    // 6.8 Directives

    auto reserved_directive_warning = [](auto & ctx) {
        auto const & error_handler = _error_handler(ctx);
        auto const where = _where(ctx);
        std::string const & directive = _attr(ctx);
        std::ostringstream oss;
        oss << "All directives except %YAML and %TAG are "
            << "reserved for future use.  The directive '%" << directive
            << "' will be ignored";
        error_handler.warn(
            _globals(ctx).first_, where.begin(), where.end(), oss.str());
    };

    // [82]
    auto const
        directive_def = '%' >>
                        (yaml_directive | tag_directive |
                         reserved_directive[reserved_directive_warning]) >>
                        s_l_comments;

    // [83]
    auto const reserved_directive_def = +ns_char >>
                                        *(+bp::ascii::blank >> +ns_char);

    auto record_yaml_directive = [](auto & ctx) {
        _globals(ctx).latest_yaml_directive_it_ = _where(ctx).begin();
    };

    auto check_yaml_version = [](auto & ctx) {
        auto & globals = _globals(ctx);
        auto const & error_handler = _error_handler(ctx);

        if (globals.yaml_directive_seen_) {
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
            using namespace hana::literals;
            int const major = _attr(ctx)[0_c];
            int const minor = _attr(ctx)[1_c];
            globals.first_yaml_directive_it_ =
                globals.latest_yaml_directive_it_;
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
            } else if (minor != 2) {
                std::ostringstream oss;
                oss << "The current document has a %YAML " << major << '.'
                    << minor
                    << " directive.  This parser recognizes "
                       "YAML 1.2, and so might not work.  "
                       "Trying anyway...";
                auto const where = _where(ctx);
                error_handler.warn(
                    globals.first_, where.begin(), where.end(), oss.str());
            }
            globals.yaml_directive_seen_ = true;
        }
    };

    // [86]
    auto const yaml_directive_def = bp::lit("YAML")[record_yaml_directive] >>
                                    +bp::ascii::blank >>
                                    (bp::uint_ >> '.' >>
                                     bp::uint_)[check_yaml_version];


    struct tag
    {
        std::string prefix_;
        any position_;
        bool default_;
    };

    bp::symbols<tag> const tags = {
        {"!!", tag{"tag:yaml.org,2002:", any(), true}},
        {"!", tag{"!", any(), true}}};

    auto record_tag_handle = [](auto & ctx) {
        _globals(ctx).tag_handle_ = _attr(ctx);
        _globals(ctx).tag_handle_it_ = _where(ctx).begin();
    };

    auto record_tag = [](auto & ctx) {
        auto const & globals = _globals(ctx);

        trie::optional_ref<tag> existing_tag =
            tags.find(ctx, globals.tag_handle_);
        if (existing_tag && existing_tag->default_) {
            tags.erase(ctx, globals.tag_handle_);
            existing_tag = trie::optional_ref<tag>{};
        }

        if (existing_tag) {
#if 0 // TODO
            auto const & error_handler = _error_handler(ctx);
            scoped_multipart_error_t multipart(error_handler.impl());
            std::ostringstream oss;
            oss << "The current document has more than one %TAG "
                << "directive using the handle " << globals.tag_handle_ << ".  "
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
            tags.insert(
                ctx,
                globals.tag_handle_,
                tag{std::move(_attr(ctx)), any(globals.tag_handle_it_), false});
        }
    };

    // [88]
    auto const tag_directive_def = "TAG" >> +bp::ascii::blank >>
                                   tag_handle[record_tag_handle] >>
                                   +bp::ascii::blank >> tag_prefix[record_tag];

    // [89]
    auto const tag_handle_def =
        // "alnum..." below is word_char [38]
        '!' >> +(bp::ascii::alnum | bp::char_('-')) >>
            '!' // named_tag_handle [92]
        | "!!"  // secondary_tag_handle [91]
        | '!'   // primary_tag_handle [90]
        ;

    // [93]
    auto const tag_prefix_def = '!' >> *uri_char | tag_char >> *uri_char;


    // 6.9 Node Properties

    auto assign_tag_property = [](auto & ctx) {
        _globals(ctx).tag_property_ = _attr(ctx);
    };
    auto assign_anchor_property = [](auto & ctx) {
        _globals(ctx).anchor_property_ = _attr(ctx);
    };

    auto make_parser_properties = [](auto & ctx) {
        auto const & globals = _globals(ctx);
        _val(ctx) = parser_properties{std::move(globals.tag_property_),
                                      globals.anchor_property_};
    };

    // [96]
    auto const properties_def =
        (tag_property[assign_tag_property] >> -(separate >> anchor_property) |
         anchor_property >>
             -(separate >>
               tag_property[assign_tag_property]))[make_parser_properties];

    auto shorthand_tag_str = [](auto & ctx) {
        using namespace hana::literals;
        auto & val = _val(ctx);
        val = std::move(_attr(ctx)[1_c]);
        tag const & tag_ = _attr(ctx)[0_c];
        val.insert(val.begin(), tag_.prefix_.begin(), tag_.prefix_.end());
    };

    // [97]
    auto const shorthand_tag_name_def = +tag_char;
    auto const tag_property_def =
        "!<" > +uri_char > '>'                            // verbatim_tag [98]
        | (tags >> shorthand_tag_name)[shorthand_tag_str] // shorthand_tag [99]
        | '!'_l >> "!" // non_specific_tag [100]
        ;

    // [22]
    // auto indicator = char_("-?:,[]{}#&*!|>'\"%@`");

    // [101]
    auto const anchor_property_def =
        '&' >> bp::raw[+(ns_char - bp::char_(",[]{}"))][assign_anchor_property];

    // [102]
    // auto anchor_char = ns_char - char_(",[]{}");

#if 0 // TODO: Appears to be unused.
    // [103]
    auto const anchor_name_def =
        bp::raw[+(ns_char - bp::char_(",[]{}"))][make_iterator_range_any];
#endif

    auto const one_time_eoi_def = bp::eoi >> bp::eps(first_time_eoi);

#if 0
    // 7.1 Alias Nodes

    bp::symbols<anchor> anchors;

    auto alias_from_anchor = [](auto&ctx) {
        _val(ctx) = _attr(ctx).alias_;
    };

    // [104]
    auto const alias_node_def = '*' > anchors[alias_from_anchor];

    // 7.3 Flow Scalar Styles

    // 7.3.1 Double Quoted Style

    // [107]
    auto const nb_double_char_def =
        esc_char[append_utf8] | (nb_json - bp::char_("\"\\"))[append_utf8];

    // [108]
    auto const ns_double_char_def = nb_double_char - bp::blank;

    // [109]
    auto const double_quoted_def = '"' >> double_text >> '"';

    // [110]
    auto const double_text_def =
        bp::eps(flow_context) >> double_multi_line |
        bp::eps(key_context) >> *nb_double_char // double-one-line [111]
        ;

    // [112]
    // TODO: A hold[] was removed here; this may need a fix somewhere else.
    // TODO: Prolly need to push the context here, not set it.
    auto const double_escaped_def = *bp::blank >> '\\' >> bp::omit[bp::eol] >>
                                    bp::eps(set_context(context::flow_in)) >>
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
        bp::eps(set_stop_at_doc_delimiter(false)) >> flow_folded;

    // [114]
    auto const double_in_line_def = *(*bp::blank >> ns_double_char);

    // [115]
    auto const double_next_line_def = double_break >>
                                      -(ns_double_char >> double_in_line >>
                                        (double_next_line | *bp::blank));

    // [116]
    auto const double_multi_line_def = double_in_line >>
                                       (double_next_line | *bp::blank);

    // 7.3.2 Single Quoted Style

    // [118]
    auto const nb_single_char_def = "''" >> bp::attr('\'') |
                                    (nb_json - '\'')[append_utf8];

    // [119]
    auto const ns_single_char_def = nb_single_char - bp::blank;

    // [120]
    auto const single_quoted_def = '\'' >> single_text >> '\'';

    // [121]
    auto const single_text_def = bp::eps(flow_context) >> single_multi_line |
                                 bp::eps(key_context) >> *nb_single_char;

    // [123]
    auto const single_in_line_def = *(*bp::blank >> ns_single_char);

    // [124]
    auto const single_next_line_def =
        bp::eps(set_stop_at_doc_delimiter(false)) >> flow_folded >>
        -(ns_single_char >> single_in_line >> (single_next_line | *bp::blank));

    // [125]
    auto const single_multi_line_def = single_in_line >>
                                       (single_next_line | *bp::blank);

    // 7.3.3 Plain Style

    // [22]
    // auto indicator = char_("-?:,[]{}#&*!|>'\"%@`");

    // [126]
    auto const plain_first_def = (ns_char - bp::char_("-?:,[]{}#&*!|>'\"%@`")) |
                                 (bp::char_("?:-") >> plain_safe);

    auto flow_out_block_key_context = [](auto & rule_ctx) {
        return rule_ctx.get().context_() == context::flow_out ||
               rule_ctx.get().context_() == context::block_key;
    };

    auto flow_in_key_context = [](auto & rule_ctx) {
        return rule_ctx.get().context_() == context::flow_in ||
               rule_ctx.get().context_() == context::flow_key;
    };

    // [127]
    auto const plain_safe_def = bp::eps(flow_out_block_key_context) >> ns_char |
                                bp::eps(flow_in_key_context) >>
                                    (ns_char - bp::char_(",[]{}"));
    auto const not_plain_safe_def =
        !(bp::eps(flow_out_block_key_context) >> raw_ns_char |
          bp::eps(flow_in_key_context) >> (raw_ns_char - bp::char_(",[]{}")));

    // [130]
    auto const plain_char_def =
        ns_char >> bp::char_('#') | bp::char_(':') >> plain_safe
        | plain_safe - bp::char_(":#");

    // [131]
    auto const plain_def = bp::eps(flow_context) >> plain_multi_line |
                           bp::eps(key_context) >> plain_one_line;

    // [132]
    // TODO: Removed hold[].
    auto const plain_in_line_def = *(*bp::blank >> plain_char);

    // [133]
    // TODO: Removed hold[].
    auto const plain_one_line_def = plain_first >> plain_in_line;

    // [134]
    // TODO: Removed hold[].
    auto const plain_next_line_def = bp::eps(set_stop_at_doc_delimiter(true)) >>
                                     flow_folded >> plain_char >> plain_in_line;

    // [135]
    auto const plain_multi_line_def = plain_one_line >> *plain_next_line;

    // 7.4 Flow Collection Styles

    // 7.4.1 Flow Sequences

    auto seq_init = [](auto & ctx) {
        auto & state = bp::get<parser_state_tag>(ctx).get();
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
        (flow_seq_entries | bp::attr(value(seq()))) >> pop_context >> -separate
        >> ']';

    // [138]
    auto const flow_seq_entries_def = bp::eps[seq_init] >> // !
                                      flow_seq_entry[seq_append] %
                                          (-separate >> ',' >> -separate) >>
                                      -(-separate >> ',');

    // [139]
    auto const flow_seq_entry_def = flow_pair | flow_node; // !

    // 7.4.2 Flow Mappings

    auto map_init = [](auto & ctx) {
        auto & state = bp::get<parser_state_tag>(ctx).get();
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
                                  (flow_map_entries | bp::attr(value(map()))) >>
                                  pop_context >> -separate >> '}';

    // [141]
    auto const flow_map_entries_def = bp::eps[map_init] >> // !
                                      flow_map_entry[map_insert] %
                                          (-separate >> ',' >> -separate) >>
                                      -(-separate >> ',');

    // [142]
    auto const flow_map_entry_def = // !
        '?' >> separate >> flow_map_explicit_entry | flow_map_implicit_entry;

    // [143]
    auto const flow_map_explicit_entry_def = // !
        flow_map_implicit_entry | bp::attr(map_element());

    // [144]
    auto const flow_map_implicit_entry_def = flow_map_json_key_entry | // !
                                             flow_map_yaml_key_entry |
                                             flow_map_empty_key_entry;

    // [145]
    auto const flow_map_yaml_key_entry_def = // !
        flow_yaml_node >>
        (-separate >> flow_map_separate_value |
         bp::attr(value()));

    // [146]
    auto const flow_map_empty_key_entry_def = // !
        bp::attr(value()) >> flow_map_separate_value;

    // [147]
    auto const flow_map_separate_value_def = ':' >> not_plain_safe >> // !
                                             (separate >> flow_node |
                                              bp::attr(value()));

    // [148]
    auto const flow_map_json_key_entry_def = flow_json_node >> // !
                                             (-separate >>
                                                  flow_map_adjacent_value |
                                              bp::attr(value()));

    // [149]
    auto const flow_map_adjacent_value_def = ':' >>
                                             (-separate >> flow_node | // !
                                              bp::attr(value()));

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
        bp::eps(push_indent(0)) >> flow_yaml_node >> -separate_in_line >>
        pop_indent;

    // [155]
    auto const implicit_json_key_def = // TODO: Limit to 1024 characters. // !
        bp::eps(push_indent(0)) >> flow_json_node >> -separate_in_line >>
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
    auto const flow_yaml_node_def = bp::attr(value());
#if 0 // TODO
        alias_node | BOOST_YAML_FLOW_YAML_CONTENT |
        (properties >> (separate >> BOOST_YAML_FLOW_YAML_CONTENT |
                        bp::attr(value())))[handle_properties];
#endif

#undef BOOST_YAML_FLOW_YAML_CONTENT

    auto handle_optional_properties = [](auto & ctx) {
        // TODO
    };

    // [160]
    auto const flow_json_node_def = bp::attr(value());
#if 0 // TODO
        (-(properties >> separate) >>
         flow_json_content)[handle_optional_properties];
#endif

    // [161]
    auto const flow_node_def = bp::attr(value());
#if 0 // TODO
        alias_node | flow_content |
        (properties >>
         (separate >> flow_content | bp::attr(value())))[handle_properties];
#endif

#endif



    // Helper rules.
    BOOST_PARSER_DEFINE_RULES(x_escape_seq, u_escape_seq, U_escape_seq);

    // Characters.
    BOOST_PARSER_DEFINE_RULES(
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
    BOOST_PARSER_DEFINE_RULES(
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
        shorthand_tag_name,
        tag_property,
        anchor_property,
        one_time_eoi);
#if 0 // TODO: Appears to be unused.
        anchor_name,
#endif

#if 0
    // Flow styles.
    BOOST_PARSER_DEFINE_RULES(
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
#endif

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

#if 1
        auto test_parser =
            x_escape_seq | u_escape_seq | U_escape_seq | printable | nb_json |
            bom | nb_char | ns_char | raw_ns_char | word_char | uri_char |
            tag_char | single_escaped_char | esc_char | indent | indent_lt |
            indent_le | separate_in_line | line_prefix | l_empty |
            /*b_l_folded | flow_folded | TODO*/ comment_text | s_b_comment |
            l_comment | s_l_comments | separate | separate_lines | /*directive
            | reserved_directive | TODO*/ yaml_directive |
            tag_directive | tag_handle | tag_prefix | properties |
            tag_property | anchor_property | one_time_eoi;
        global_state<iter_t> globals{first, max_recursion};
        auto const parser = bp::with_globals(test_parser, globals);
#endif

#if 0
        global_state<iter_t> globals{first, max_recursion};
        auto const parser = bp::with_globals(value_p, globals);
#endif

        bp::callback_error_handler const error_handler(parse_error);
        try {
            value val;
#if 0
            bool const success =
                bp::parse(first, last, parser, error_handler, val);
#else
            auto const success = bp::parse(first, last, parser, error_handler);
#endif
            if (!success || first != last)
                return {};
            return optional<value>(std::move(val));
        } catch (excessive_nesting<iter_t> const & e) {
            if (parse_error) {
                std::string const message = "error: Exceeded maximum number (" +
                                            std::to_string(max_recursion) +
                                            ") of open arrays and/or objects";
                std::stringstream ss;
                bp::write_formatted_message(
                    ss, "", range.begin(), e.iter, last, message);
                parse_error(ss.str());
            }
        }

        return {};
    }

}}
