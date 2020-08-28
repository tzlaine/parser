#ifndef BOOST_PARSER_PARSER_FWD_HPP
#define BOOST_PARSER_PARSER_FWD_HPP

#include <boost/parser/config.hpp>
#include <boost/parser/error_handling_fwd.hpp>

#include <boost/any.hpp>

#include <cstdint>
#include <map>


namespace boost { namespace parser {

    /** A placeholder type used to represent the absence of information,
        value, etc., in `boost::parser`.  For instance, a parser with no
        global data will have a `globals_` data member whose type is `nope`.
        `nope` is designed to satisfy all requirements of any type that it
        might replace, where convenient.  For instance, it has an implicit
        conversion to `std::nullopt_t`, so that it be assigned to a
        `std::optional<T>`. */
    struct nope;

    namespace detail {
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

        using symbol_table_tries_t = std::map<void *, any, std::less<void *>>;

        template<typename Iter, typename Sentinel, typename ErrorHandler>
        inline auto make_context(
            Iter first,
            Sentinel last,
            bool & success,
            int & indent,
            ErrorHandler const & error_handler,
            nope &,
            symbol_table_tries_t & symbol_table_tries) noexcept;

        struct skip_skipper;
    }

    /** Repeats the application of another parser `p` of type `Parser`,
        optionally applying another parser `d` of type `DelimiterParser` in
        between each pair of applications of `p`.  The parse succeeds if `p`
        succeeds at least the minumum number of times, and `d` succeeds each
        time it is applied.  The attribute produced is a sequence of the type
        of attribute produced by `Parser`. */
    template<
        typename Parser,
        typename DelimiterParser = nope,
        typename MinType = int64_t,
        typename MaxType = int64_t>
    struct repeat_parser;

    /** Repeats the application of another parser `p` of type `Parser`, `[0,
        Inf)` times.  The parse always succeeds.  The attribute produced is a
        sequence of the type of attribute produced by `Parser`. */
    template<typename Parser>
    struct zero_plus_parser;

    /** Repeats the application of another parser `p` of type `Parser`, `[1,
        Inf)` times.  The parse succeeds iff `p` succeeds at least once.  The
        attribute produced is a sequence of the type of attribute produced by
        `Parser`. */
    template<typename Parser>
    struct one_plus_parser;

    /** Repeats the application of another parser `p` of type `Parser`, `[1,
        Inf)` times, applying a parser `d` of type `DelimiterParser` in
        between each pair of applications of `p`.  The parse succeeds iff `p`
        succeeds at least once, and `d` succeeds each time it is applied.  The
        attribute produced is a sequence of the type of attribute produced by
        `Parser`. */
    template<typename Parser, typename DelimiterParser>
    struct delimited_seq_parser;

    /** Repeats the application of another parser of type `Parser`, `[0, 1]`
        times.  The parse always succeeds.  The attribute produced is a
        `std::optional<T>`, where `T` is the type of attribute produced by
        `Parser`. */
    template<typename Parser>
    struct opt_parser;

    /** Applies each parser in `ParserTuple`, in order, stopping after the
        application of the first one that succeeds.  The parse succeeds iff
        one of the sub-parsers succeeds.  The attribute produced is a
        `std::variant` over the types of attribute produced by the parsers in
        `ParserTuple`. */
    template<typename ParserTuple>
    struct or_parser;

    /** Applies each parser in `ParserTuple`, in order.  The parse succeeds
        iff all of the sub-parsers succeeds.  The attribute produced is a
        `std::tuple` over the types of attribute produced by the parsers in
        `ParserTuple`.  The BacktrackingTuple template parameter is a
        `hana::tuple` of `hana::bool_` values.  The `i`th such value indicates
        whether backtracking is allowed if the `i`th parser fails. */
    template<typename ParserTuple, typename BacktrackingTuple>
    struct seq_parser;

    /** Applies the given parser `p` of type `Parser` and an invocable `a` of
        type `Action`.  `Action` shall model `semantic_action`, and `a` will
        only be invoked if `p` succeeds.  The parse succeeds iff `p` succeeds.
        Produces no attribute. */
    template<typename Parser, typename Action>
    struct action_parser;

    /** Applies the given parser `p` of type `Parser`.  This parser produces
        no attribute, and suppresses the production of any attributes that
        would otherwise be produced by `p`.  The parse succeeds iff `p`
        succeeds. */
    template<typename Parser>
    struct omit_parser;

    /** Applies the given parser `p` of type `Parser`; regardless of the
        attribute produced by `Parser`, this parser's attribute is equivalent
        to `_where(ctx)` within a semantic action on `p`.  The parse succeeds
        iff `p` succeeds. */
    template<typename Parser>
    struct raw_parser;

    /** Applies the given parser `p` of type `Parser`, disabling the current
        skipper in use, if any.  The parse succeeds iff `p` succeeds.  The
        attribute produced is the type of attribute produced by `Parser`. */
    template<typename Parser>
    struct lexeme_parser;

    /** Applies the given parser `p` of type `Parser`, using a parser of type
        `SkipParser` as the skipper.  The parse succeeds iff `p` succeeds.
        The attribute produced is the type of attribute produced by
        `Parser`. */
    template<typename Parser, typename SkipParser = nope>
    struct skip_parser;

    /** Applies the given parser `p` of type `Parser`, producing no attributes
        and consuming no input.  The parse succeeds iff `p` succeeds. */
    template<typename Parser, bool FailOnMatch>
    struct expect_parser;

    /** Matches one of a set S of possible inputs, each of which is associated
        with an attribute value of type `T`, forming a symbol table.  New
        elements and their associated attributes may be added to or removed
        from S dynamically, during parsing; any such changes are reverted at
        the end of parsing.  The parse succeeds iff an element of S is
        matched.  \see `symbols` */
    template<typename T>
    struct symbol_parser;

    /** Applies another parser `p`, associated with this parser via `TagType`.
        The attribute produced is `Attribute`.  Both a default-constructed
        object of type `LocalState`, and a default-constructed object of type
        `ParamsTuple`, are added to the parse context before the associated
        parser is applied.  The parse succeeds iff `p` succeeds.  If
        `UseCallbacks` is `true`, the attribute is produced via callback;
        otherwise, the attribute is produced as normal (as a return value, or
        as an out-param).  The rule may be constructed with a user-friendly
        name that will appear if the top-level parse is executed with
        `trace_mode == boost::parser::trace::on`. */
    template<
        bool UseCallbacks,
        typename TagType,
        typename Attribute,
        typename LocalState,
        typename ParamsTuple>
    struct rule_parser;

    /** Matches anything, and consumes no input.  If `Predicate` is anything
        other than `nope`, and `pred_(ctx)` evaluates to false, where `ctx` is
        the parser context, the parse fails. */
    template<typename Predicate>
    struct eps_parser;

    /** Matches only the end of input.  Produces no attribute. */
    struct eoi_parser;

    /** Matches anything, consumes no input, and produces an attribute of type
        `Attribute`. */
    template<typename Attribute>
    struct attr_parser;

    /** Matches a single code point.  If `AttributeType` is not `void`,
        `AttributeType` is the attribute type produced; otherwise, the
        attribute type is the decayed type of the matched code point.  The
        parse fails only if the parser is constructed with a specific set of
        expected code point values that does not include the matched code
        point `CP`. */
    template<typename Expected, typename AttributeType = void>
    struct char_parser;

    /** Maches a particular string, delimited by an iterator sentinel pair;
        produces no attribute. */
    template<typename StrIter, typename StrSentinel>
    struct string_parser;

    /** Maches an end-of-line in the input; produces no attribute.
        End-of-line is considered to be "\r\n", or any one of the line break
        code points from the Unicode Line Break Algorithm, described in
        https://unicode.org/reports/tr14. */
    struct eol_parser;

    /** Maches the strings "true" and "false", producing an attribute of
        `true` or `false`, respectively, and fails on any other input. */
    struct bool_parser;

    /** Matches an unsigned number of radix `Radix`, of at least `MinDigits`
        and at most `MaxDigits`, producing an attribute of type `T`.  Fails on
        any other input.  The parse will also fail if `Expected` is anything
        but `nope`, and the produced attribute is not equal to `expected_`.
        `Radix` must be in `[2, 36]`. */
    template<
        typename T,
        int Radix = 10,
        int MinDigits = 1,
        int MaxDigits = -1,
        typename Expected = nope>
    struct uint_parser;

    /** Matches a signed number of radix `Radix`, of at least `MinDigits` and
        at most `MaxDigits`, producing an attribute of type `T`.  Fails on any
        other input.  The parse will also fail if `Expected` is anything but
        `nope`, and the produced attribute is not equal to `expected_`.
        `Radix` must be one of `2`, `8`, `10`, or `16`. */
    template<
        typename T,
        int Radix = 10,
        int MinDigits = 1,
        int MaxDigits = -1,
        typename Expected = nope>
    struct int_parser;

    /** Matches a floating point number, producing an attribute of type
        `T`. */
    template<typename T>
    struct float_parser;

    /** Applies at most one of the parsers in `OrParser`.  If `switch_value_`
        matches one or more of the values in the parsers in `OrParser`, the
        first such parser is applied, and the success or failure and attribute
        of the parse are those of the applied parser.  Otherwise, the parse
        fails. */
    template<typename SwitchValue, typename OrParser = nope>
    struct switch_parser;

    /** A wrapper for a parser, with optional global state and optional error
        handler, that provides the interface that all parsers must have:
        `operator*()`, `operator>>()`, etc. */
    template<
        typename Parser,
        typename GlobalState = nope,
        typename ErrorHandler = default_error_handler>
    struct parser_interface;

}}

#endif
