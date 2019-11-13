#ifndef BOOST_PARSER_PARSER_FWD_HPP
#define BOOST_PARSER_PARSER_FWD_HPP

#include <boost/parser/error_handling_fwd.hpp>

#include <cstdint>


namespace boost { namespace parser {

    namespace detail {

        // TODO: -> boost::parser namespace
        /** A tag type used to represent the absence of information, value,
            etc., in `boost::parser`.  For instance, a parser with no global
            data will have a `globals_` data member whose type is `nope`. */
        struct nope;

        enum class flags : unsigned int {
            gen_attrs = 1 << 0,
            use_skip = 1 << 1,
            trace = 1 << 2,
            in_apply_parser = 1 << 3
        };

        // Built-in tags for use with the context.
        struct val_tag;
        struct attr_tag;
        struct where_tag;
        struct begin_tag;
        struct end_tag;
        struct pass_tag;
        struct locals_tag;
        struct rule_params_tag;
        struct globals_tag;
        struct trace_indent_tag;
        struct error_handler_tag;
        struct callbacks_tag;
        struct symbol_table_tries_tag;
    }

    /** Repeats the application of another parser of type `Parser p`,
        optionally applying another parser of type `DelimiterParser d` in
        between each pair of applications of `p`.  The parse succeeds if `p`
        succeeds at least the minumum number of times, and `d` succeeds each
        time it is applied. */
    template<
        typename Parser,
        typename DelimiterParser = detail::nope,
        typename MinType = int64_t,
        typename MaxType = int64_t>
    struct repeat_parser;

    /** Repeats the application of another parser of type `Parser [0, Inf)`
        times. */
    template<typename Parser>
    struct zero_plus_parser;

    /** Repeats the application of another parser of type `Parser p [1, Inf)`
        times.  The parse succeeds iff `p` succeeds at least once. */
    template<typename Parser>
    struct one_plus_parser;

    /** Repeats the application of another parser of type `Parser p [1, Inf)`
        times, applying a parser of type `DelimiterParser` in between each
        pair of applications of `p`.  The parse succeeds iff `p` succeeds at
        least once, and `d` succeeds each time it is applied. */
    template<typename Parser, typename DelimiterParser>
    struct delimited_seq_parser;

    /** Repeats the application of another parser of type `Parser [0, 1]`
        times. */
    template<typename Parser>
    struct opt_parser;

    /** Applies each parser in `ParserTuple`, in order, stopping after the
        application of the first one that succeeds.  The parse succeeds iff
        one of the sub-parsers succeeds. */
    template<typename ParserTuple>
    struct or_parser;

    /** Applies each parser in `ParserTuple`, in order.  The parse succeeds
        iff all of the sub-parsers succeeds.  The BacktrackingTuple template
        parameter is a `hana::tuple` of `hana::bool_` values.  The `i`th such
        value indicates whether backtracking is allowed if the `i`th parser
        fails. */
    template<typename ParserTuple, typename BacktrackingTuple>
    struct seq_parser;

    /** Applies the given parser of type `Parser p` and an invocable of type
        `Action a`.  `Action` shall model `semantic_action`, and `a` will only
        be invoked if `p` succeeds.  The parse succeeds iff `p` succeeds. */
    template<typename Parser, typename Action>
    struct action_parser;

    /** Applies the given parser of type `Parser p`; regardless off the
        attribute produced by `Parser`, this parser produces no attributes.
        The parse succeeds iff `p` succeeds. */
    template<typename Parser>
    struct omit_parser;

    /** Applies the given parser of type `Parser p`; regardless off the
        attribute produced by `Parser`, this parser's attribute is produced as
        if by to `_val(ctx) = _where(ctx)` within a semantic action on `p`.
        The parse succeeds iff `p` succeeds. */
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

    template<typename SwitchValue, typename OrParser = detail::nope>
    struct switch_parser;

    /** A wrapper for a parser, with optional global state and optional error
        handler, that provides the interface that all parsers must have --
        operator*(), operator>>(), etc. */
    template<
        typename Parser,
        typename GlobalState = detail::nope,
        typename ErrorHandler = default_error_handler>
    struct parser_interface;

}}

#endif
