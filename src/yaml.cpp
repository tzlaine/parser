#include <boost/yaml/yaml.hpp>
#include <boost/parser/parser.hpp>

#include <boost/container/small_vector.hpp>
#include <boost/any.hpp>


namespace boost { namespace yaml {

    namespace bp = ::boost::parser;
    using namespace bp::literals;

    using parser_map_element = hana::tuple<value, value>;

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
        using view_type = parser::view<Iter>;

        global_state(iterator first, int max_recursion) :
            first_(first),
            max_recursive_open_count_(max_recursion)
        {}

        void clear_document_state() { yaml_directive_seen_ = false; }

        iterator const first_;
        int recursive_open_count_ = 0;
        int const max_recursive_open_count_;

        int indent_ = -1;
        context context_ = context::block_in;

        bool stop_at_document_delimiter_ = false;
        eoi_state eoi_state_ = eoi_state::not_at_end;

        bool yaml_directive_seen_ = false;
        iterator first_yaml_directive_it_;
        iterator latest_yaml_directive_it_;

        std::string tag_handle_;
        iterator tag_handle_it_;

        std::string tag_property_;
        view_type anchor_property_;
    };

    auto const reset_eoi_state_ = [](auto & ctx) {
        _globals(ctx).eoi_state_ = eoi_state::not_at_end;
    };

    struct reset_eoi_state
    {
        template<typename Context>
        reset_eoi_state(Context const & context)
        {
            reset_eoi_state_(context);
        }
    };

    struct scoped_eoi_state
    {
        template<typename Context>
        scoped_eoi_state(Context const & context) :
            global_eoi_state_(_globals(context).eoi_state_)
        {}
        ~scoped_eoi_state() { global_eoi_state_ = eoi_state::not_at_end; }

        eoi_state global_eoi_state_;
    };

    struct scoped_indent
    {
        template<typename Context>
        scoped_indent(Context const & context) :
            global_indent_(_globals(context).indent_),
            prev_indent_(global_indent_)
        {}
        ~scoped_indent() { global_indent_ = prev_indent_; }

        int & global_indent_;
        int const prev_indent_;
    };

    struct scoped_context
    {
        template<typename Context>
        scoped_context(Context const & context) :
            global_context_(_globals(context).context_),
            prev_context_(global_context_)
        {}
        ~scoped_context() { global_context_ = prev_context_; }

        context & global_context_;
        context const prev_context_;
    };

    struct scoped_stop_at_doc_delim
    {
        template<typename Context>
        scoped_stop_at_doc_delim(Context const & context) :
            global_stop_at_document_delimiter_(
                _globals(context).stop_at_document_delimiter_),
            prev_stop_at_document_delimiter_(global_stop_at_document_delimiter_)
        {}
        ~scoped_stop_at_doc_delim()
        {
            global_stop_at_document_delimiter_ =
                prev_stop_at_document_delimiter_;
        }

        bool & global_stop_at_document_delimiter_;
        bool const prev_stop_at_document_delimiter_;
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

    bp::rule<class one_time_eoi> const one_time_eoi = "end of input";
    auto const one_time_eoi_def = bp::eoi >> bp::eps(first_time_eoi);

    bp::rule<class blank_string_0> const blank_string_0 = "blank_string_0";
    auto const blank_string_0_def = *bp::ascii::blank;

    bp::rule<class blank_string_1> const blank_string_1 = "blank_string_1";
    auto const blank_string_1_def = +bp::ascii::blank;

    bp::rule<class end_of_input> const end_of_input = "end_of_input";
    auto const end_of_input_def = *(*bp::ascii::blank >>
                                    -('#' >> *(bp::char_ - bp::eol)) >>
                                    bp::eol) >>
                                  *bp::ascii::blank >>
                                  -('#' >> *(bp::char_ - bp::eoi)) >> bp::eoi;



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

    // Convenience variation on indent that indents _p<0> spaces instead of
    // global_indent spaces.
    bp::rule<class indent_n> const indent_n = "indent_n";

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

    // [71]
    bp::rule<class b_l_trimmed, std::string> const b_l_trimmed = "b_l_trimmed";

    // [73]
    bp::rule<class b_l_folded, std::string> const b_l_folded = "b_l_folded";

    // [74]
    bp::rule<class flow_folded, std::string, scoped_context> const flow_folded =
        "flow_folded";

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
    // any as view
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
    bp::rule<class nb_double_char, uint32_t> const nb_double_char =
        "nb_double_char";

    // [108]
    bp::rule<class ns_double_char, uint32_t> const ns_double_char =
        "ns_double_char";

    // [109]
    bp::rule<class double_quoted, std::string> const double_quoted =
        "double_quoted";

    // [110]
    bp::rule<class double_text, std::string> const double_text = "double_text";

    // [112]
    bp::rule<class double_escaped, std::string, scoped_context> const
        double_escaped = "double_escaped";

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
    bp::rule<class nb_single_char, uint32_t> const nb_single_char =
        "nb_single_char";

    // [119]
    bp::rule<class ns_single_char, uint32_t> const ns_single_char =
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
    bp::rule<class flow_seq_entries> const flow_seq_entries =
        "flow_seq_entries";

    // [139]
    bp::rule<class flow_seq_entry, value> const flow_seq_entry =
        "flow_seq_entry";

    // 7.4.2 Flow Mappings

    // [140]
    bp::rule<class flow_mapping, value> const flow_mapping = "flow_mapping";

    // [141]
    bp::rule<class flow_map_entries> const flow_map_entries =
        "flow_map_entries";

    // [142]
    bp::rule<class flow_map_entry, parser_map_element> const flow_map_entry =
        "flow_map_entry";

    // [143]
    bp::rule<class flow_map_explicit_entry, parser_map_element> const
        flow_map_explicit_entry = "flow_map_explicit_entry";

    // [144]
    bp::rule<class flow_map_implicit_entry, parser_map_element> const
        flow_map_implicit_entry = "flow_map_implicit_entry";

    // [145]
    bp::rule<class flow_map_yaml_key_entry, parser_map_element, value> const
        flow_map_yaml_key_entry = "flow_map_yaml_key_entry";

    // [146]
    bp::rule<class flow_map_empty_key_entry, parser_map_element, value> const
        flow_map_empty_key_entry = "flow_map_empty_key_entry";

    // [147]
    bp::rule<class flow_map_separate_value, value> const
        flow_map_separate_value = "flow_map_separate_value";

    // [148]
    bp::rule<class flow_map_json_key_entry, parser_map_element, value> const
        flow_map_json_key_entry = "flow_map_json_key_entry";

    // [149]
    bp::rule<class flow_map_adjacent_value, value> const
        flow_map_adjacent_value = "flow_map_adjacent_value";

    // [150]
    bp::rule<class flow_pair, value> const flow_pair = "flow_pair";

    // [151]
    bp::rule<class flow_pair_entry, parser_map_element> const flow_pair_entry =
        "flow_pair_entry";

    // [152]
    bp::rule<class flow_pair_yaml_key_entry, parser_map_element, value> const
        flow_pair_yaml_key_entry = "flow_pair_yaml_key_entry";

    // [153]
    bp::rule<class flow_pair_json_key_entry, parser_map_element, value> const
        flow_pair_json_key_entry = "flow_pair_json_key_entry";

    // [154]
    bp::rule<class implicit_yaml_key, value, scoped_indent> const
        implicit_yaml_key = "implicit_yaml_key";

    // [155]
    bp::rule<class implicit_json_key, value, scoped_indent> const
        implicit_json_key = "implicit_json_key";

    // 7.5 Flow Nodes

    // [156]
    bp::rule<class flow_yaml_content, value> const flow_yaml_content =
        "flow_yaml_content";

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
    bp::rule<class block_header> const block_header = "block_header";

    // [163]
    bp::rule<class indentation_indicator, int> const indentation_indicator =
        "indentation_indicator";

    // [164]
    bp::rule<class chomping_indicator> const chomping_indicator =
        "chomping_indicator";

    // [165]
    bp::rule<class chomped_last, std::string> const chomped_last =
        "chomped_last";

    // [166]
    bp::rule<class chomped_empty, std::string, scoped_indent> const
        chomped_empty = "chomped_empty";

    // [167]
    bp::rule<class strip_empty> const strip_empty = "strip_empty";

    // [168]
    bp::rule<class keep_empty, std::string, scoped_context> const keep_empty =
        "keep_empty";

    // [169]
    bp::rule<class trail_comments, bp::no_attribute, reset_eoi_state> const
        trail_comments = "trail_comments";

    struct literal_folded_locals : scoped_indent
    {
        template<typename Context>
        literal_folded_locals(Context const & context) : scoped_indent(context)
        {}
        int indent_ = 0;
        chomping chomping_ = chomping::strip;
    };

    // [170]
    bp::rule<class literal, std::string, literal_folded_locals> const literal =
        "literal";

    // [171]
    bp::rule<class literal_text, std::string, scoped_context> const
        literal_text = "literal_text";

    // [172]
    bp::rule<class literal_next, std::string> const literal_next =
        "literal_next";

    bp::rule<class literal_content_optional, std::string, scoped_indent> const
        literal_content_optional = "literal_content_optional";

    // [173]
    bp::rule<class literal_content> const literal_content = "literal_content";

    // 8.1.3. Folded Style

    // [174]
    bp::rule<class folded, std::string, literal_folded_locals> const folded =
        "folded";

    // [175]
    bp::rule<class folded_text, std::string> const folded_text = "folded_text";

    struct folded_lines_locals : scoped_context, scoped_stop_at_doc_delim
    {
        template<typename Context>
        folded_lines_locals(Context const & context) :
            scoped_context(context),
            scoped_stop_at_doc_delim(context)
        {}
    };

    // [176]
    bp::rule<class folded_lines, std::string, folded_lines_locals> const
        folded_lines = "folded_lines";

    // [177]
    bp::rule<class spaced_text, std::string> const spaced_text = "spaced_text";

    // [178]
    bp::rule<class spaced, std::string, scoped_context> const spaced = "spaced";

    // [179]
    bp::rule<class spaced_lines, std::string> const spaced_lines =
        "spaced_lines";

    // [180]
    bp::rule<class same_lines, std::string, std::string> const same_lines =
        "same_lines";

    // [181]
    bp::rule<class diff_lines, std::string> const diff_lines = "diff_lines";

    bp::rule<class folded_content_optional, std::string, scoped_indent> const
        folded_content_optional = "folded_content_optional";

    // [182]
    bp::rule<class folded_content> const folded_content = "folded_content";

    // 8.2.1. Block Sequences

    bp::rule<class auto_detect_indent, int> const auto_detect_indent =
        "auto_detect_indent";

    bp::rule<class scalar_auto_detect_indent, int, int> const
        scalar_auto_detect_indent = "scalar_auto_detect_indent";

    struct indent_locals : scoped_indent
    {
        template<typename Context>
        indent_locals(Context const & context) : scoped_indent(context)
        {}
        int indent_ = 0;
    };

    // [183]
    bp::rule<class block_sequence, value, indent_locals> const block_sequence =
        "block_sequence";

    // [184]
    bp::rule<class block_seq_entry, value> const block_seq_entry =
        "block_seq_entry";

    // [185]
    bp::rule<class block_indented, value, indent_locals> const block_indented =
        "block_indented";

    // [186]
    bp::rule<class compact_sequence, value> const compact_sequence =
        "compact_sequence";

    // 8.2.1. Block Mappings

    // [187]
    bp::rule<class block_mapping, value, indent_locals> const block_mapping =
        "block_mapping";

    // [188]
    bp::rule<class block_map_entry, parser_map_element> const block_map_entry =
        "block_map_entry";

    // [189]
    bp::rule<class block_map_explicit_entry, parser_map_element> const
        block_map_explicit_entry = "block_map_explicit_entry";

    // [190]
    bp::rule<class block_map_explicit_key, value> const block_map_explicit_key =
        "block_map_explicit_key";

    // [191]
    bp::rule<class block_map_explicit_value, value> const
        block_map_explicit_value = "block_map_explicit_value";

    // [192]
    bp::rule<class block_map_implicit_entry, parser_map_element> const
        block_map_implicit_entry = "block_map_implicit_entry";

    // [193]
    bp::rule<class block_map_implicit_key, value> const block_map_implicit_key =
        "block_map_implicit_key";

    // [194]
    bp::rule<class block_map_implicit_value, value> const
        block_map_implicit_value = "block_map_implicit_value";

    // [195]
    bp::rule<class compact_mapping, value> const compact_mapping =
        "compact_mapping";

    // 8.2.3. Block Nodes

    // [196]
    bp::rule<class block_node, value> const block_node = "block_node";

    struct in_block_locals : scoped_context, scoped_indent
    {
        template<typename Context>
        in_block_locals(Context const & context) :
            scoped_context(context),
            scoped_indent(context)
        {}
    };

    // [197]
    bp::rule<class flow_in_block, value, in_block_locals> const flow_in_block =
        "flow_in_block";

    // [198]
    bp::rule<class block_in_block, value, in_block_locals> const
        block_in_block = "block_in_block";

    // [199]
    bp::rule<class block_scalar, value, parser_properties> const block_scalar =
        "block_scalar";

    // [200]
    bp::rule<class block_collection, value> const block_collection =
        "block_collection";

    // 9.1. Documents

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



    // Definitions

    bp::parser_interface<bp::uint_parser<unsigned int, 16, 2, 2>> const hex_2;
    bp::parser_interface<bp::uint_parser<unsigned int, 16, 4, 4>> const hex_4;
    bp::parser_interface<bp::uint_parser<unsigned int, 16, 8, 8>> const hex_8;

    auto const x_escape_seq_def = "\\x" > hex_2;
    auto const u_escape_seq_def = "\\u" > hex_4;
    auto const U_escape_seq_def = "\\U" > hex_8;



    // 5.2. Character Encodings

    // [1]
    auto const printable_def =
        bp::char_("\t\n\f") | bp::char_('\x20', '\x7e') | bp::char_(0x0085u) |
        bp::char_(0x00a0u, 0xd7ffu) | bp::char_(0xe000u, 0xfffdu) |
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
    auto const indent_n_def = bp::repeat(bp::_p<0>)[' '_l];

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

    // [71]
    auto const b_l_trimmed_def = +l_empty;

    // [73]
    auto const b_l_folded_def = bp::eol >>
                                (bp::eps(dont_stop_at_doc_delimiter) |
                                 !(bp::lit("...") | "---")) >>
                                (b_l_trimmed | bp::attr(std::string(" ")));

    auto set_context = [](context c) {
        return [c](auto & ctx) { _globals(ctx).context_ = c; };
    };

    // [74]
    auto const flow_folded_def = bp::eps[set_context(context::flow_in)] >>
                                 -separate_in_line >> b_l_folded >> line_prefix;

    // 6.6 Comments

    // [75]
    auto const comment_text_def = '#' >> +nb_char;

    // [77]
    auto const s_b_comment_def =
        -(separate_in_line >> -comment_text) >>
        (bp::eol | bp::eoi >> bp::eps(first_time_eoi)); // b-comment [77]

    // [78]
    auto const l_comment_def = separate_in_line >> -comment_text >>
                               (bp::eol | bp::eoi >> bp::eps(first_time_eoi));

    // [79]
    auto const s_l_comments_def = bp::eps[reset_eoi_state_] >>
                                  (s_b_comment | bp::eps(at_start_of_line)) >>
                                  *l_comment;

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
        std::string const & directive = _attr(ctx);
        std::ostringstream oss;
        oss << "All directives except %YAML and %TAG are "
            << "reserved for future use.  The directive '%" << directive
            << "' will be ignored";
        _report_warning(ctx, oss.str());
    };

    // [82]
    auto const
        directive_def = '%' >>
                        (yaml_directive | tag_directive |
                         reserved_directive[reserved_directive_warning]) >>
                        s_l_comments;

    // [83]
    auto const reserved_directive_def = +ns_char >>
                                        *(blank_string_1 >> +ns_char);

    auto record_yaml_directive = [](auto & ctx) {
        _globals(ctx).latest_yaml_directive_it_ = _where(ctx).begin();
    };

    auto check_yaml_version = [](auto & ctx) {
        auto & globals = _globals(ctx);

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
                _report_warning(ctx, oss.str());
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

        bool operator==(tag const & rhs) const noexcept
        {
            return prefix_ == rhs.prefix_ && default_ == rhs.default_ &&
                   position_.type() == rhs.position_.type();
        }

        bool operator!=(tag const & rhs) const noexcept
        {
            return !(*this == rhs);
        }
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

        text::optional_ref<tag> existing_tag =
            tags.find(ctx, globals.tag_handle_);
        if (existing_tag && existing_tag->default_) {
            tags.erase(ctx, globals.tag_handle_);
            existing_tag = text::optional_ref<tag>{};
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

    // 7.1 Alias Nodes

    bp::symbols<anchor> const anchors;

    auto alias_from_anchor = [](auto & ctx) { _val(ctx) = _attr(ctx).alias_; };

    // [104]
    auto const alias_node_def = '*' > anchors[alias_from_anchor];

    // 7.3 Flow Scalar Styles

    // 7.3.1 Double Quoted Style

    // [107]
    auto const nb_double_char_def = esc_char | (nb_json - bp::char_("\"\\"));

    // [108]
    auto const ns_double_char_def = nb_double_char - bp::ascii::blank;

    // [109]
    auto const double_quoted_def = '"' >> *nb_json /*double_text*/ >> '"';

    // [110]
    // clang-format off
    auto const double_text_def = bp::switch_(context_)
        (context::flow_out, double_multi_line)
        (context::flow_in, double_multi_line)
        (context::block_key, *nb_double_char) // double-one-line [111]
        (context::flow_key, *nb_double_char)  // double-one-line [111]
        ;
    // clang-format on

    // [112]
    // TODO: A hold[] was removed here; this may need a fix somewhere else.
    auto const double_escaped_def =
        *bp::ascii::blank >> '\\' >> bp::omit[bp::eol] >>
        bp::eps[set_context(context::flow_in)] >> *l_empty >> line_prefix;

    auto set_stop_at_doc_delimiter = [](bool b) {
        return
            [b](auto & ctx) { _globals(ctx).stop_at_document_delimiter_ = b; };
    };

    // [113]
    auto const double_break_def =
        double_escaped |
        bp::eps[set_stop_at_doc_delimiter(false)] >> flow_folded;

    // [114]
    auto const double_in_line_def = *(*bp::ascii::blank >> ns_double_char);

    auto append_utf8 = [](auto & ctx) {
        std::array<uint32_t, 1> const cps = {{_attr(ctx)}};
        auto const r = text::as_utf8(cps);
        _val(ctx).insert(_val(ctx).end(), r.begin(), r.end());
    };

    // [115]
    auto const double_next_line_def = double_break >>
                                      -(ns_double_char[append_utf8] >>
                                        double_in_line >>
                                        (double_next_line | blank_string_0));

    // [116]
    auto const double_multi_line_def = double_in_line >>
                                       (double_next_line | blank_string_0);

    // 7.3.2 Single Quoted Style

    // [118]
    auto const nb_single_char_def = "''" >> bp::attr(uint32_t('\'')) |
                                    (nb_json - '\'');

    // [119]
    auto const ns_single_char_def = nb_single_char - bp::ascii::blank;

    // [120]
    auto const single_quoted_def = '\'' >> single_text >> '\'';

    // [121]
    // clang-format off
    auto const single_text_def = bp::switch_(context_)
        (context::flow_out, single_multi_line)
        (context::flow_in, single_multi_line)
        (context::block_key, *nb_single_char)
        (context::flow_key, *nb_single_char)
        ;
    // clang-format on

    // [123]
    auto const single_in_line_def = *(*bp::ascii::blank >> ns_single_char);

    // [124]
    auto const single_next_line_def =
        bp::eps[set_stop_at_doc_delimiter(false)] >> flow_folded >>
        -(ns_single_char[append_utf8] >> single_in_line >>
          (single_next_line | blank_string_0));

    // [125]
    auto const single_multi_line_def = single_in_line >>
                                       (single_next_line | blank_string_0);

    // 7.3.3 Plain Style

    // [22]
    // auto indicator = char_("-?:,[]{}#&*!|>'\"%@`");

    auto const assign_to_val = [](auto & ctx) { _val(ctx) = _attr(ctx); };

    // [126]
    auto const plain_first_def =
        (ns_char - bp::char_("-?:,[]{}#&*!|>'\"%@`"))[assign_to_val] |
        (bp::cp("?:-")[append_utf8] >> plain_safe);

    // [127]
    // clang-format off
    auto const plain_safe_def = bp::switch_(context_)
        (context::flow_out, ns_char)
        (context::block_key, ns_char)
        (context::flow_in, ns_char - bp::char_(",[]{}"))
        (context::flow_key, ns_char - bp::char_(",[]{}"))
        ;
    // clang-format on

    // [130]
    auto const
        plain_char_def = ns_char >> bp::cu('#') | bp::cu(':') >> plain_safe
                         | plain_safe - bp::char_(":#");

    // [131]
    // clang-format off
    auto const plain_def = bp::switch_(context_)
        (context::flow_out, plain_multi_line)
        (context::flow_in, plain_multi_line)
        (context::block_key, plain_one_line)
        (context::flow_key, plain_one_line)
        ;
    // clang-format on

    // [132]
    // TODO: Removed hold[].
    auto const plain_in_line_def = *(blank_string_0 >> plain_char);

    // [133]
    // TODO: Removed hold[].
    auto const plain_one_line_def = plain_first >> plain_in_line;

    // [134]
    // TODO: Removed hold[].
    auto const plain_next_line_def = bp::eps[set_stop_at_doc_delimiter(true)] >>
                                     flow_folded >> plain_char >> plain_in_line;

    // [135]
    auto const plain_multi_line_def = plain_one_line >> *plain_next_line;

    // 7.4 Flow Collection Styles

    // 7.4.1 Flow Sequences

    auto seq_init = [](auto & ctx) {
        auto & globals = _globals(ctx);
        if (globals.max_recursive_open_count_ < ++globals.recursive_open_count_)
            _pass(ctx) = false;
        else
            _val(ctx) = seq();
    };
    auto seq_append = [](auto & ctx) {
        value & v = _val(ctx);
        get<seq>(v).push_back(std::move(_attr(ctx)));
    };

    // [137]
    auto const flow_sequence_def = '[' >> bp::eps[seq_init] >> -separate >>
                                   flow_seq_entries >> -separate >>
                                   ']'; // TODO: > instead of >> ?  Elsewhere?

    // [138]
    auto const flow_seq_entries_def = flow_seq_entry[seq_append] %
                                          (-separate >> ',' >> -separate) >>
                                      -(-separate >> ',');

    // [139]
    auto const flow_seq_entry_def = flow_pair | flow_node;

    // 7.4.2 Flow Mappings

    auto map_init = [](auto & ctx) {
        auto & globals = _globals(ctx);
        if (globals.max_recursive_open_count_ < ++globals.recursive_open_count_)
            _pass(ctx) = false;
        else
            _val(ctx) = map();
    };
    auto map_insert = [](auto & ctx) {
        value & v = _val(ctx);
        auto & attr = _attr(ctx);
        using namespace hana::literals;
        get<map>(v).try_emplace(std::move(attr[0_c]), std::move(attr[1_c]));
    };

    // [140]
    auto const flow_mapping_def = '{' >> bp::eps[map_init] >> -separate >>
                                  flow_map_entries >> -separate >> '}';

    // [141]
    auto const flow_map_entries_def = flow_map_entry[map_insert] %
                                          (-separate >> ',' >> -separate) >>
                                      -(-separate >> ',');

    // [142]
    auto const flow_map_entry_def =
        '?' >> separate >> flow_map_explicit_entry | flow_map_implicit_entry;

    // [143]
    auto const flow_map_explicit_entry_def =
        flow_map_implicit_entry | bp::attr(parser_map_element());

    // [144]
    auto const flow_map_implicit_entry_def = flow_map_json_key_entry |
                                             flow_map_yaml_key_entry |
                                             flow_map_empty_key_entry;

    auto map_entry_key = [](auto & ctx) { _locals(ctx) = _attr(ctx); };
    auto make_map_entry = [](auto & ctx) {
        _val(ctx) =
            parser_map_element(std::move(_locals(ctx)), std::move(_attr(ctx)));
    };

    // [145]
    auto const
        flow_map_yaml_key_entry_def = flow_yaml_node[map_entry_key] >>
                                      (-separate >> flow_map_separate_value |
                                       bp::attr(value()))[make_map_entry];

    // [146]
    auto const flow_map_empty_key_entry_def =
        flow_map_separate_value[make_map_entry];

    // [147]
    auto const flow_map_separate_value_def = ':' >> !plain_safe >>
                                             (separate >> flow_node |
                                              bp::attr(value()));

    // [148]
    auto const
        flow_map_json_key_entry_def = flow_json_node[map_entry_key] >>
                                      (-separate >> flow_map_adjacent_value |
                                       bp::attr(value()))[make_map_entry];

    // [149]
    auto const flow_map_adjacent_value_def = ':' >> (-separate >> flow_node |
                                                     bp::attr(value()));

    auto value_from_map_from_element = [](auto & ctx) {
        auto & val = _val(ctx);
        val = map();
        parser_map_element & element = _attr(ctx);
        using namespace hana::literals;
        get<map>(val).emplace(std::move(element[0_c]), std::move(element[1_c]));
    };

    // [150]
    auto const flow_pair_def =
        '?' >> separate >>
            flow_map_explicit_entry[value_from_map_from_element] |
        flow_pair_entry[value_from_map_from_element];

    // [151]
    auto const flow_pair_entry_def = flow_pair_yaml_key_entry |
                                     flow_map_empty_key_entry |
                                     flow_pair_json_key_entry;

    // [152]
    auto const flow_pair_yaml_key_entry_def =
        implicit_yaml_key[map_entry_key] >>
        flow_map_separate_value[make_map_entry];

    // [153]
    auto const flow_pair_json_key_entry_def =
        implicit_json_key[map_entry_key] >>
        flow_map_adjacent_value[make_map_entry];

    auto set_indent = [](int i) {
        return [i](auto & ctx) { _globals(ctx).indent_ = i; };
    };

    // [154]
    auto const implicit_yaml_key_def = // TODO: Limit to 1024 characters.
        bp::eps[set_indent(0)] >> flow_yaml_node >> -separate_in_line;

    // [155]
    auto const implicit_json_key_def = // TODO: Limit to 1024 characters.
        bp::eps[set_indent(0)] >> flow_json_node >> -separate_in_line;

    // 7.5 Flow Nodes

    // [156]
    auto const flow_yaml_content_def = plain;

    // [157]
    auto const flow_json_content_def =
        flow_sequence | flow_mapping | single_quoted | double_quoted;

    // [158]
    auto const flow_content_def = flow_json_content | flow_yaml_content;

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

        if (properties) {
            return ast::value_t(
                ast::properties_node_t(properties, ast::value_t(x)));
        }

        return ast::value_t(x);
#endif
    };

    // [159]
    auto const flow_yaml_node_def =
        alias_node | flow_yaml_content |
        (properties >> (separate >> flow_yaml_content |
                        bp::attr(value())))[handle_properties];

    // [160]
    auto const flow_json_node_def =
        (-(properties >> separate) >> flow_json_content)[handle_properties];

    // [161]
    auto const flow_node_def =
        alias_node | flow_content |
        (properties >>
         (separate >> flow_content | bp::attr(value())))[handle_properties];


    // 8.1 Block Scalar Styles

    // [162]
    auto const block_header_def =
        (indentation_indicator >> chomping_indicator |
         chomping_indicator >> indentation_indicator) >>
        s_b_comment >> bp::eps[reset_eoi_state_];

    auto set_local_indent_from_cp = [](auto & ctx) {
        _locals(ctx).indent_ = _attr(ctx) - uint32_t('0');
    };

    // [163]
    // TODO: For round-tripping, a number like this must sometimes be placed
    // in the output (as in, when a scalar has leading spaces)
    auto const indentation_indicator_def =
        (bp::ascii::digit | bp::attr(0x30u))[set_local_indent_from_cp];

    auto set_chomping = [](chomping c) {
        return [c](auto & ctx) { _locals(ctx).chomping_ = c; };
    };

    // [164]
    auto const chomping_indicator_def = '-'_l[set_chomping(chomping::strip)] |
                                        '+'_l[set_chomping(chomping::keep)] |
                                        bp::eps[set_chomping(chomping::clip)];

    auto indent_param = [](auto & ctx) {
        using namespace hana::literals;
        return _params(ctx)[0_c];
    };
    auto chomping_param = [](auto & ctx) {
        using namespace hana::literals;
        return _params(ctx)[1_c];
    };

    // [165]
    // clang-format off
    auto const chomped_last_def = bp::switch_(chomping_param)
        (chomping::strip, bp::eol)
        (chomping::keep, bp::eol >> bp::attr('\n'))
        (chomping::clip, bp::eol >> bp::attr('\n')) |
        bp::eoi;
    // clang-format on

    auto set_indent_from_param = [](auto & ctx) {
        _globals(ctx).indent_ = indent_param(ctx);
    };

    // [166]
    // clang-format off
    auto const chomped_empty_def =
        bp::eps[set_indent_from_param] >>
        bp::switch_(chomping_param)
            (chomping::strip, strip_empty)
            (chomping::keep, keep_empty)
            (chomping::clip, strip_empty);
    // clang-format on

    // [167]
    auto const strip_empty_def = *(indent_le >> bp::eol) >> -trail_comments;

    // [168]
    auto const keep_empty_def =
        bp::eps[set_context(context::block_in)] >> *l_empty >> -trail_comments;

    // [169]
    auto const trail_comments_def = indent_lt >> '#' >> *nb_char >>
                                    (bp::eol | bp::eoi) >> *l_comment;

    auto set_local_indent = [](auto & ctx) {
        _locals(ctx).indent_ = _attr(ctx);
    };

    auto local_indent_zero = [](auto & ctx) {
        return _locals(ctx).indent_ == 0;
    };
    auto local_indent_nonzero = [](auto & ctx) {
        return _locals(ctx).indent_ != 0;
    };
    auto local_indent_greater_than_global = [](auto & ctx) {
        return _globals(ctx).indent_ < _locals(ctx).indent_;
    };

    auto local_indent = [](auto & ctx) { return _locals(ctx).indent_; };
    auto local_chomping = [](auto & ctx) { return _locals(ctx).chomping_; };
    auto summed_indent = [](auto & ctx) {
        return indent_(ctx) + local_indent(ctx);
    };

    auto const append_str = [](auto & ctx) { _val(ctx) += _attr(ctx); };

    // [170]
    // clang-format off
    auto const literal_def =
            '|'
        >>  block_header
        >>  (
                bp::eps(local_indent_zero)
            >>  scalar_auto_detect_indent[set_local_indent]
                // This parenthesized expression is a modified version of
                // literal_content that only expects the optional portion
                // if positive indentation is detected.
            >>  (
                    (
                        bp::eps(local_indent_greater_than_global)
                    >   literal_content_optional.with(
                            local_indent, local_chomping
                        )[append_str]
                    |   bp::eps
                    )
                >>  chomped_empty.with(local_indent, local_chomping)
                    [append_str]
                )
            |   bp::eps(local_indent_nonzero)
            >>  literal_content.with(summed_indent, local_chomping)
            )
        ;
    // clang-format on

    // [171]
    auto const literal_text_def = bp::eps[set_context(context::block_in)] >>
                                  *l_empty >> indent >> nb_char >> *nb_char;

    auto const append_newline_and_str = [](auto & ctx) {
        _val(ctx) += "\n";
        _val(ctx) += _attr(ctx);
    };

    // [172]
    auto const literal_next_def =
        bp::eol >> !(bp::lit("...") | "---") >> literal_text;

    // TODO: hold[] removed here.
    auto const
        literal_content_optional_def = bp::eps[set_indent_from_param] >>
                                       literal_text >> *literal_next >>
                                       chomped_last.with(0, chomping_param);

    // [173]
    auto const literal_content_def =
        -literal_content_optional.with(
            indent_param, chomping_param)[append_str] >>
        chomped_empty.with(indent_param, chomping_param)[append_str];

    // 8.1.3. Folded Style

    // [174]
    // clang-format off
    auto const folded_def =
            '>'
        >>  block_header
        >>  (
                bp::eps(local_indent_zero)
            >>  scalar_auto_detect_indent[set_local_indent]
                // This parenthesized expression is a modified version of
                // folded_content that only expects the optional portion if
                // positive indentation is detected.
            >>  (
                    (
                        bp::eps(local_indent_greater_than_global)
                    >   folded_content_optional.with(
                            local_indent, local_chomping
                        )[append_str]
                    |   bp::eps
                    )
                >>  chomped_empty.with(local_indent, local_chomping)
                    [append_str]
                )
            |   bp::eps(local_indent_nonzero)
            >>  folded_content.with(summed_indent, local_chomping)
            )
        ;
    // clang-format on

    // [175]
    auto const folded_text_def = indent >> ns_char >> *nb_char[append_utf8];

    // [176]
    auto const folded_lines_def = folded_text >>
                                  bp::eps[set_context(context::block_in)] >>
                                  bp::eps[set_stop_at_doc_delimiter(true)] >>
                                  *(b_l_folded >> folded_text);

    // [177]
    auto const spaced_text_def =
        indent >> bp::ascii::blank[append_str] >> *nb_char;

    auto const append_newline = [](auto & ctx) { _val(ctx) += '\n'; };

    // [178]
    auto const spaced_def = bp::eol[append_newline] >>
                            bp::eps[set_context(context::block_in)] >>
                            *l_empty[append_newline];

    // [179]
    auto const spaced_lines_def = spaced_text >> *(spaced >> spaced_text);

    auto const append_to_locals = [](auto & ctx) {
        _locals(ctx) += _attr(ctx);
    };
    auto const append_local_and_attr = [](auto & ctx) {
        _val(ctx) += _locals(ctx);
        _val(ctx) += _attr(ctx);
    };

    // [180]
    auto const same_lines_def = bp::eps[set_context(context::block_in)] >>
                                *l_empty[append_to_locals] >>
                                (folded_lines |
                                 spaced_lines)[append_local_and_attr];

    // [181]
    auto const diff_lines_def = same_lines[append_str] >>
                                *(bp::eol >>
                                  same_lines[append_newline_and_str]);

    // TODO: hold[] removed.
    auto const
        folded_content_optional_def = bp::eps[set_indent_from_param] >>
                                      diff_lines >>
                                      chomped_last.with(0, chomping_param);

    // [182]
    auto const folded_content_def =
        -folded_content_optional.with(
            indent_param, chomping_param)[append_str] >>
        chomped_empty.with(indent_param, chomping_param)[append_str];

    // 8.2.1. Block Sequences

    auto const incr = [](auto & ctx) { ++_val(ctx); };

    auto const auto_detect_indent_def = bp::eps >> &(*' '_l[incr]);

    auto const zero_local = [](auto & ctx) { _locals(ctx) = 0; };
    auto const incr_local = [](auto & ctx) { ++_locals(ctx); };
    auto const update_max = [](auto & ctx) {
        _val(ctx) = (std::max)(_val(ctx), _locals(ctx));
    };
    auto const check_scalar_indentation = [](auto & ctx) {
        if (_val(ctx) <= _locals(ctx)) {
            _val(ctx) = _locals(ctx);
        } else {
            auto const where = _where(ctx);
            (void)where; // TODO
#if 0
            scoped_multipart_error_t multipart(error_handler.impl());
            std::ostringstream oss;
            oss << "The first non-space character of a block-scalar "
                << "(text beginning with '|' or '>') must be at least "
                << "as indented as all its leading empty lines.  "
                << "This line is indented " << this_line_indent
                << " spaces, but a previous line was indented " << max_indent
                << " spaces:\n";
            error_handler.impl().report_error_at(
                range.begin(), oss.str(), multipart);
#endif
            _pass(ctx) = false;
        }
    };

    auto const scalar_auto_detect_indent_def =
        bp::eps >>
        &(*(bp::eps[zero_local] >> *' '_l[incr_local] >> bp::eol[update_max]) >>
          bp::eps[zero_local] >> *' '_l[incr_local] >>
          bp::eps[check_scalar_indentation]);

    auto const set_global_indent = [](auto & ctx) {
        _globals(ctx).indent_ = _attr(ctx);
    };
    auto global_indent = [](auto & ctx) { return _globals(ctx).indent_; };
    auto param0_lt_indent = [](auto & ctx) {
        using namespace hana::literals;
        return _params(ctx)[0_c] < _globals(ctx).indent_;
    };

    // [183]
    auto const block_sequence_def =
        auto_detect_indent[set_global_indent] >>
        bp::eps(param0_lt_indent)[seq_init] >>
        +(indent >> block_seq_entry.with(global_indent)[seq_append]);

    // [184]
    auto const
        block_seq_entry_def = '-' >> !ns_char >>
                              block_indented.with(bp::_p<0>, context::block_in);

    auto const block_compact_indent = [](auto & ctx) {
        return bp::_p<0>(ctx) + 1 + _globals(ctx).indent_;
    };

    // [185]
    auto const
        block_indented_def = auto_detect_indent[set_global_indent] >> indent >>
                                 (compact_sequence.with(block_compact_indent) |
                                  compact_mapping.with(block_compact_indent)) |
                             block_node.with(bp::_p<0>, bp::_p<1>) |
                             bp::attr(yaml::value()) >> s_l_comments;

    // [186]
    auto const compact_sequence_def =
        bp::eps[seq_init] >>
        block_seq_entry.with(bp::_p<0>)[seq_append] % indent_n.with(bp::_p<0>);

    // 8.2.1. Block Mappings

    // [187]
    auto const block_mapping_def =
        auto_detect_indent[set_global_indent] >>
        bp::eps(param0_lt_indent)[map_init] >>
        +(indent >> block_map_entry.with(global_indent)[map_insert]);

    // [188]
    auto const block_map_entry_def = block_map_explicit_entry.with(bp::_p<0>) |
                                     block_map_implicit_entry.with(bp::_p<0>);

    // [189]
    auto const block_map_explicit_entry_def =
        block_map_explicit_key.with(bp::_p<0>) >>
        (block_map_explicit_value.with(bp::_p<0>) | bp::attr(yaml::value()));

    // [190]
    auto const block_map_explicit_key_def =
        '?' >> block_indented.with(bp::_p<0>, context::block_out);

    // [191]
    auto const block_map_explicit_value_def =
        indent_n.with(bp::_p<0>) >> ':' >>
        block_indented.with(bp::_p<0>, context::block_out);

    // [192]
    auto const block_map_implicit_entry_def =
        (block_map_implicit_key | bp::attr(yaml::value())) >>
        block_map_implicit_value.with(bp::_p<0>);

    // [193]
    auto const block_map_implicit_key_def =
        implicit_json_key.with(context::block_key) |
        implicit_yaml_key.with(context::block_key);

    // [194]
    auto const block_map_implicit_value_def =
        ':' >> (block_node.with(bp::_p<0>, context::block_out) |
                bp::attr(yaml::value()) >> s_l_comments);

    // [195]
    auto const compact_mapping_def =
        bp::eps[map_init] >>
        block_map_entry.with(bp::_p<0>)[map_insert] % indent.with(bp::_p<0>);

    // 8.2.3. Block Nodes

    // [196]
    auto const block_node_def = block_in_block | flow_in_block;

    auto const incr_indent = [](auto & ctx) { ++_globals(ctx).indent_; };

    // [197]
    auto const flow_in_block_def = bp::eps[incr_indent] >>
                                   bp::eps[set_context(context::flow_out)] >>
                                   separate >> flow_node >> s_l_comments;

    // [198]
    auto const block_in_block_def = block_scalar | block_collection;

    auto const move_to_local = [](auto & ctx) {
        _locals(ctx) = std::move(_attr(ctx));
    };

    // [199]
    auto const
        block_scalar_def = bp::eps[incr_indent] >> separate >>
                           -bp::omit[properties[move_to_local] >> separate] >>
                           (literal | folded)[handle_properties];

    auto const seq_spaces = [](auto & ctx) {
        return indent_(ctx) - (context_(ctx) == context::block_out ? 1 : 0);
    };

    // [200]
    auto const block_collection_def =
        // clang-format off
            s_l_comments
        >>  (
                block_sequence.with(seq_spaces)
            |   block_mapping
            )
        |   bp::eps[incr_indent]
        >>  bp::omit[separate >> properties]
        >>  s_l_comments
        >>  (
                block_sequence.with(seq_spaces)
            |   block_mapping
            )[handle_properties]
        // clang-format on
        ;

    // 9.1. Documents

    auto not_at_end = [](auto & ctx) {
        return _globals(ctx).eoi_state_ == eoi_state::not_at_end;
    };

    // [202]
    auto const document_prefix_def = !bom // BOM is read prior to each document.
                                     >> bp::eps[reset_eoi_state_] >>
                                     +l_comment >> bp::eps(not_at_end);

    // [205]
    auto const document_suffix_def = "..." >> s_l_comments;

    // [206]
    auto const forbidden_def = bp::eps(at_start_of_line) >>
                               (-bom >> "---" | "...") >>
                               (bp::eol | bp::ascii::blank | bp::eoi);

    // [207]
    auto const
        bare_document_def = !bom // BOM is read prior to each document.
                            >>
                            block_node.with(-1, context::block_in) - forbidden;

    // [208]
    auto const explicit_document_def =
        !bom // BOM is read prior to each document.
        >> "---" >> (bare_document | bp::attr(yaml::value()) >> s_l_comments);

    // [209]
    auto const directive_document_def =
        !bom // BOM is read prior to each document.
        >> +directive >> explicit_document;

    // [210]
    auto const any_document_def =
        directive_document | explicit_document | bare_document;

    auto const clear_document_state = [](auto & ctx) {
        _globals(ctx).clear_document_state();
    };

    auto const push_document = [](auto & ctx) {
        _val(ctx).push_back(std::move(_attr(ctx)));
        _globals(ctx).clear_document_state();
    };

    // [211]
    auto const yaml_stream_def = bp::eps[clear_document_state] >>
                                 *document_prefix >>
                                 -any_document[push_document] >>
                                 *(+(document_suffix >> !bom) >>
                                       *document_prefix >>
                                       any_document[push_document] |
                                   *document_prefix >>
                                       explicit_document[push_document]) >>
                                 *(document_suffix >> !bom) >> *document_prefix;

    // Helper rules.
    BOOST_PARSER_DEFINE_RULES(
        x_escape_seq,
        u_escape_seq,
        U_escape_seq,
        one_time_eoi,
        blank_string_0,
        blank_string_1,
        end_of_input);

    // Characters.
    BOOST_PARSER_DEFINE_RULES(
        printable,
        nb_json,
        bom,
        nb_char,
        ns_char,
        word_char,
        uri_char,
        tag_char,
        single_escaped_char,
        esc_char);

    // Basic structures.
    BOOST_PARSER_DEFINE_RULES(
        indent,
        indent_n,
        indent_lt,
        indent_le,
        separate_in_line,
        line_prefix,
        l_empty,
        b_l_trimmed,
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
        anchor_property);
#if 0 // TODO: Appears to be unused.
        anchor_name,
#endif

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
        flow_yaml_content,
        flow_json_content,
        flow_content,
        flow_yaml_node,
        flow_json_node,
        flow_node);

    // Block styles.
    BOOST_PARSER_DEFINE_RULES(
        block_header,
        indentation_indicator,
        chomping_indicator,
        chomped_last,
        chomped_empty,
        strip_empty,
        keep_empty,
        trail_comments,
        literal,
        literal_text,
        literal_next,
        literal_content_optional,
        literal_content,
        folded,
        folded_text,
        folded_lines,
        spaced_text,
        spaced,
        spaced_lines,
        same_lines,
        diff_lines,
        folded_content_optional,
        folded_content,
        auto_detect_indent,
        scalar_auto_detect_indent,
        block_sequence,
        block_seq_entry,
        block_indented,
        compact_sequence,
        block_mapping,
        block_map_entry,
        block_map_explicit_entry,
        block_map_explicit_key,
        block_map_explicit_value,
        block_map_implicit_entry,
        block_map_implicit_key,
        block_map_implicit_value,
        compact_mapping,
        block_node,
        flow_in_block,
        block_in_block,
        block_scalar,
        block_collection);

    // Documents
    BOOST_PARSER_DEFINE_RULES(
        document_prefix,
        document_suffix,
        forbidden,
        bare_document,
        explicit_document,
        directive_document,
        any_document,
        yaml_stream);

    namespace detail {
        template<typename Iter>
        encoding read_bom_8(Iter it, int & size)
        {
            auto retval = encoding::utf8;

            if (size == 4 && *it == '\x00' && *std::next(it, 1) == '\x00' &&
                *std::next(it, 2) == '\xfe' && *std::next(it, 3) == '\xff') {
                size = 4;
                retval = encoding::utf32_be;
            } else if (
                size == 4 && *it == '\x00' && *std::next(it, 1) == '\x00' &&
                *std::next(it, 2) == '\x00' /* anything */) {
                size = 4;
                retval = encoding::utf32_be;
            } else if (
                size == 4 && *it == '\xff' && *std::next(it, 1) == '\xfe' &&
                *std::next(it, 2) == '\x00' && *std::next(it, 3) == '\x00') {
                size = 4;
                retval = encoding::utf32_le;
            } else if (
                size == 4 && /* anything */ *std::next(it, 1) == '\x00' &&
                *std::next(it, 2) == '\x00' && *std::next(it, 3) == '\x00') {
                size = 4;
                retval = encoding::utf32_le;
            } else if (
                size >= 2 && *it == '\xfe' && *std::next(it, 1) == '\xff') {
                size = 2;
                retval = encoding::utf16_be;
            } else if (size >= 2 && *it == '\x00' /* anything */) {
                size = 2;
                retval = encoding::utf16_be;
            } else if (
                size >= 2 && *it == '\xff' && *std::next(it, 1) == '\xfe') {
                size = 2;
                retval = encoding::utf16_le;
            } else if (
                size >= 2 && /* anything */ *std::next(it, 1) == '\x00') {
                size = 2;
                retval = encoding::utf16_le;
            } else if (
                size >= 3 && *it == '\xef' && *std::next(it, 1) == '\xbb' &&
                *std::next(it, 2) == '\xbf') {
                size = 3;
                retval = encoding::utf8;
            } else {
                size = 0;
            }

            return retval;
        }

        template<typename ErrorFn>
        bool check_encoding(encoding encoding, ErrorFn const & error_fn)
        {
            if (encoding != encoding::utf8) {
                std::stringstream oss;
                oss << "BOM for encoding " << encoding
                    << " was encountered in the stream, but only "
                    << encoding::utf8 << " encoding is supported.\n";
                error_fn(oss.str());
                return false;
            }
            return true;
        }

        template<typename Iter>
        encoding read_bom(Iter & cp_first, Iter cp_last)
        {
            auto const r = text::as_utf8(cp_first, cp_last);
            auto first = r.begin();
            auto const last = r.end();
            int size = 0;
            {
                auto cu_first = r.begin();
                while (cu_first != last && size < 4) {
                    ++cu_first;
                }
            }
            auto const retval = detail::read_bom_8(first, size);
            first += size;
            cp_first = text::utf32_iterator(first, first, last);
            return retval;
        }
    }

    // TODO: This needs to change; it cannot parse a rope; there should also
    // be interfaces that accept CPIters and CPRanges.
    std::optional<std::vector<value>> parse(
        string_view const & str,
        diagnostic_function errors_callback,
        int max_recursion)
    {
        std::optional<std::vector<value>> retval;

        auto const range = text::as_utf32(str);
        using iter_t = decltype(range.begin());
        auto first = range.begin();
        auto last = range.end();

        if (max_recursion <= 0)
            max_recursion = INT_MAX;

        try {
            auto const first_encoding = detail::read_bom(first, last);
            auto const encoding_ok =
                detail::check_encoding(first_encoding, errors_callback);
            if (!encoding_ok)
                return retval;

            global_state<iter_t> globals{first, max_recursion};
            bp::callback_error_handler error_handler(errors_callback);
            auto const parser = bp::with_error_handler(
                bp::with_globals(yaml_stream, globals), error_handler);

            std::vector<value> documents;
            std::vector<value> temp_documents;
            bool success = true;
            do {
                auto initial = first;
                bool success = bp::parse(first, last, parser, temp_documents);

                if (!success || first == initial)
                    break;

                auto const prev_size = documents.size();
                documents.resize(prev_size + temp_documents.size());
                std::move(
                    temp_documents.begin(),
                    temp_documents.end(),
                    documents.begin() + prev_size);
                temp_documents.clear();

                bool doc_boundary = bp::parse(
                    first, last, bp::with_globals(+document_suffix, globals));

                auto const encoding = detail::read_bom(first, last);
                auto const encoding_ok =
                    detail::check_encoding(encoding, errors_callback);

                if (!encoding_ok)
                    success = false;

                if (!doc_boundary)
                    doc_boundary = bp::parse(first, last, &bp::lit("---"));

                // If there's not a ... or --- separator, don't keep reading
                // documents.  However, this is not an error by itself.
                if (!doc_boundary)
                    break;
            } while (success);

            if (success) {
                success = bp::parse(first, last, end_of_input);

                if (!success) {
                    error_handler(
                        first,
                        last,
                        bp::parse_error<iter_t>(
                            first,
                            "Expected end of input, next map element, or next "
                            "seq "
                            "element here:\n"));
                }
            }

            if (success)
                retval = std::move(documents);
        } catch (excessive_nesting<iter_t> const & e) {
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
        return retval;
    }

}}
