#ifndef BOOST_PARSER_ERROR_HANDLING_FWD_HPP
#define BOOST_PARSER_ERROR_HANDLING_FWD_HPP

#include <iostream>


namespace boost { namespace parser {

    /** The possible actions to take when a parse error is handled by an error
        handler. */
    enum class error_handler_result {
        fail,   /// Fail the top-level parse.
        rethrow /// Re-throw the parse error eexception.
    };

    /** The exception thrown when a parse error is encountered, consisting an
        iterator to the point of failure, and the name of the failed parser or
        rule in `what()`. */
    template<typename Iter>
    struct parse_error : std::runtime_error
    {
        parse_error(Iter it, std::string const & msg) :
            runtime_error(msg),
            iter(it)
        {}

        Iter iter;
    };

    /** A position within a line, consisting of an iterator to the start of
        the line, the line number, and the column number. */
    template<typename Iter>
    struct line_position
    {
        Iter line_start;
        int64_t line_number;
        int64_t column_number;
    };

    /** Writes a formatted message (meaning prefixed with the file name, line,
        and column number) to `os`. */
    template<typename Iter>
    std::ostream & write_formatted_message(
        std::ostream & os,
        std::string_view filename,
        Iter first,
        Iter it,
        Iter last,
        std::string_view message,
        int64_t preferred_max_line_length = 80,
        int64_t max_after_caret = 40);

    /** Writes a formatted parse-expectation failure (meaning prefixed with
        the file name, line, and column number) to `os`. */
    template<typename Iter>
    std::ostream & write_formatted_expectation_failure_error_message(
        std::ostream & os,
        std::string_view filename,
        Iter first,
        Iter last,
        parse_error<Iter> const & e,
        int64_t preferred_max_line_length = 80,
        int64_t max_after_caret = 40);

    // TODO: Add info kind as well?

    /** The kinds of diagnostics that can be handled by an error handler. */
    enum class diagnostic_kind {
        error,  /// An error diagnostic.
        warning /// A warning diagnostic.
    };

    // TODO: error_handler concept.
#if 0
#if defined(__cpp_lib_concepts) && defined(__cpp_lib_ranges)
    template<typename T>
    BOOST_PARSER_CONCEPT cp_iterator =
        ranges::forward_iterator<T> &&
        requires (T & t, T const & ct) {
            { *t } -> std::convertible_to<uint32_t>;
            { *ct } -> std::convertible_to<uint32_t>;
        };
    template<typename T>
    BOOST_PARSER_CONCEPT error_handler = requires (T const & t) {
        
    };
#endif
#endif

    /** The error handler used when the user does not specify a custom one. */
    struct default_error_handler
    {
        constexpr default_error_handler() : os_(nullptr) {}
        constexpr default_error_handler(std::string_view filename) :
            filename_(filename),
            os_(nullptr)
        {}
        constexpr default_error_handler(
            std::string_view filename, std::ostream & os) :
            filename_(filename),
            os_(&os)
        {}

        /** Handles a `parse_error` exception thrown during parsing.  A
            formatted parse-expectation failure is printed to `*os_` when
            `os_` is non-null, or `std::cout` otherwise.  Always returns
            `error_handler_result::fail`. */
        template<typename Iter>
        error_handler_result
        operator()(Iter first, Iter last, parse_error<Iter> const & e) const
        {
            std::ostream & os = os_ ? *os_ : std::cout;
            parser::write_formatted_expectation_failure_error_message(
                os, filename_, first, last, e);
            return error_handler_result::fail;
        }

        /** Prints `message` to `*os_` when `os_` is non-null, or `std::cout`
            otherwise.  The diagnostic is printed with the given `kind`,
            indicating the location as being at `it`.  This must be called
            within a parser semantic action, providing the parse context. */
        template<typename Context, typename Iter>
        void diagnose(
            diagnostic_kind kind,
            std::string_view message,
            Context const & context,
            Iter it) const
        {
            std::ostream & os = os_ ? *os_ : std::cout;
            parser::write_formatted_message(
                os, filename_, _begin(context), it, _end(context), message);
        }

        /** Prints `message` to `*os_` when `os_` is non-null, or `std::cout`
            otherwise.  The diagnostic is printed with the given `kind`, at no
            particular location.  This must be called within a parser semantic
            action, providing the parse context. */
        template<typename Context>
        void diagnose(
            diagnostic_kind kind,
            std::string_view message,
            Context const & context) const
        {
            diagnose(kind, message, context, _where(context).begin());
        }

        std::string_view filename_;
        std::ostream * os_;
    };

}}

#endif
