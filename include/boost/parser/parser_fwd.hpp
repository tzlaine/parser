#ifndef BOOST_PARSER_PARSER_FWD_HPP
#define BOOST_PARSER_PARSER_FWD_HPP

// TODO: For testing only.
#include <boost/mpl/assert.hpp>
#include <boost/mpl/print.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/any.hpp>


namespace boost { namespace parser {

    namespace detail {

        struct nope;

        enum class flags : unsigned int {
            gen_attrs = 1 << 0,
            use_skip = 1 << 1,
            trace = 1 << 2
        };

        // Built-in tags for use with the context.
        struct val_tag;
        struct attr_tag;
        struct where_tag;
        struct pass_tag;
        struct locals_tag;
        struct rule_params_tag;
        struct globals_tag;
        struct trace_indent_tag;
        struct error_handler_tag;
        struct callbacks_tag;
        struct symbol_table_tries_tag;
    }

    template<typename Parser, typename DelimiterParser = detail::nope>
    struct repeat_parser;

    template<typename Parser>
    struct zero_plus_parser;

    template<typename Parser>
    struct one_plus_parser;

    template<typename Parser, typename DelimiterParser>
    struct delimited_seq_parser;

    template<typename Parser>
    struct opt_parser;

    template<typename ParserTuple>
    struct or_parser;

    template<typename ParserTuple, typename BacktrackingTuple>
    struct seq_parser;

    template<typename Parser, typename Action>
    struct action_parser;

    template<typename Parser>
    struct omit_parser;

    template<typename Parser>
    struct raw_parser;

    template<typename Parser>
    struct lexeme_parser;

    template<typename Parser, typename SkipParser = detail::nope>
    struct skip_parser;

    template<typename Parser, bool FailOnMatch>
    struct expect_parser;

    template<typename T>
    struct symbol_parser;

    template<
        bool UseCallbacks,
        typename Parser,
        typename Attribute,
        typename LocalState,
        typename ParamsTuple>
    struct rule_parser;

    template<typename T>
    struct ref_parser;

    template<typename Parser, typename GlobalState = detail::nope>
    struct parser_interface;

    template<typename Predicate>
    struct eps_parser;

    struct eoi_parser;

    template<typename Attribute>
    struct attr_parser;

    template<typename Expected, typename AttributeType = void>
    struct char_parser;

    struct string_parser;

    struct eol_parser;

    struct bool_parser;

    template<
        typename T,
        int Radix = 10,
        int MinDigits = 1,
        int MaxDigits = -1,
        typename Expected = detail::nope>
    struct uint_parser;

    template<
        typename T,
        int Radix = 10,
        int MinDigits = 1,
        int MaxDigits = -1,
        typename Expected = detail::nope>
    struct int_parser;

    template<typename T>
    struct float_parser;

    enum class error_handler_result { fail, rethrow };

}}

#endif
