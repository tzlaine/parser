#ifndef BOOST_PARSER_ERROR_HANDLING_FWD_HPP
#define BOOST_PARSER_ERROR_HANDLING_FWD_HPP

#include <boost/parser/config.hpp>

#include <iostream>
#include <string_view>


namespace boost { namespace parser {

    /** The possible actions to take when a parse error is handled by an error
        handler. */
    enum class error_handler_result {
        fail,   /// Fail the top-level parse.
        rethrow /// Re-throw the parse error exception.
    };

    /** The exception thrown when a parse error is encountered, consisting of
        an iterator to the point of failure, and the name of the failed parser
        or rule in `what()`. */
    template<typename Iter>
    struct parse_error : std::runtime_error
    {
        parse_error(Iter it, std::string const & msg) :
            runtime_error(msg), iter(it)
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
    template<typename Iter, typename Sentinel>
    std::ostream & write_formatted_message(
        std::ostream & os,
        std::string_view filename,
        Iter first,
        Iter it,
        Sentinel last,
        std::string_view message,
        int64_t preferred_max_line_length = 80,
        int64_t max_after_caret = 40);

#if defined(_MSC_VER) || defined(BOOST_PARSER_DOXYGEN)
    /** Writes a formatted message (meaning prefixed with the file name, line,
        and column number) to `os`.  This overload is Windows-only. */
    template<typename Iter, typename Sentinel>
    std::ostream & write_formatted_message(
        std::ostream & os,
        std::wstring_view filename,
        Iter first,
        Iter it,
        Sentinel last,
        std::string_view message,
        int64_t preferred_max_line_length = 80,
        int64_t max_after_caret = 40);
#endif

    /** Writes a formatted parse-expectation failure (meaning prefixed with
        the file name, line, and column number) to `os`. */
    template<typename Iter, typename Sentinel>
    std::ostream & write_formatted_expectation_failure_error_message(
        std::ostream & os,
        std::string_view filename,
        Iter first,
        Sentinel last,
        parse_error<Iter> const & e,
        int64_t preferred_max_line_length = 80,
        int64_t max_after_caret = 40);

#if defined(_MSC_VER) || defined(BOOST_PARSER_DOXYGEN)
    /** Writes a formatted parse-expectation failure (meaning prefixed with
        the file name, line, and column number) to `os`.  This overload is
        Windows-only. */
    template<typename Iter, typename Sentinel>
    std::ostream & write_formatted_expectation_failure_error_message(
        std::ostream & os,
        std::wstring_view filename,
        Iter first,
        Sentinel last,
        parse_error<Iter> const & e,
        int64_t preferred_max_line_length = 80,
        int64_t max_after_caret = 40);
#endif

    /** The kinds of diagnostics that can be handled by an error handler. */
    enum class diagnostic_kind {
        error,  /// An error diagnostic.
        warning /// A warning diagnostic.
    };

    /** The error handler used when the user does not specify a custom one.
        This error handler prints warnings and errors to `std::cout`, and does
        not have an associcated filename. */
    struct default_error_handler
    {
        constexpr default_error_handler() = default;

        /** Handles a `parse_error` exception thrown during parsing.  A
            formatted parse-expectation failure is printed to `std::cout`.
            Always returns `error_handler_result::fail`. */
        template<typename Iter, typename Sentinel>
        error_handler_result
        operator()(Iter first, Sentinel last, parse_error<Iter> const & e) const
        {
            parser::write_formatted_expectation_failure_error_message(
                std::cout, "", first, last, e);
            return error_handler_result::fail;
        }

        /** Prints `message` to `std::cout`.  The diagnostic is printed with
            the given `kind`, indicating the location as being at `it`.  This
            must be called within a parser semantic action, providing the
            parse context. */
        template<typename Context, typename Iter>
        void diagnose(
            diagnostic_kind kind,
            std::string_view message,
            Context const & context,
            Iter it) const
        {
            parser::write_formatted_message(
                std::cout, "", _begin(context), it, _end(context), message);
        }

        /** Prints `message` to `std::cout`.  The diagnostic is printed with
            the given `kind`, at no particular location.  This must be called
            within a parser semantic action, providing the parse context. */
        template<typename Context>
        void diagnose(
            diagnostic_kind kind,
            std::string_view message,
            Context const & context) const
        {
            diagnose(kind, message, context, _where(context).begin());
        }
    };

    /** Prints warnings and errors to the `std::ostream` provided by the user,
        or `std::cout` if no such stream is specified.  If a filename is
        provided, that is used to print all diagnostics. */
    struct stream_error_handler
    {
        stream_error_handler() : os_(std::cout) {}
        stream_error_handler(std::string_view filename) :
            filename_(filename), os_(std::cout)
        {}
        stream_error_handler(std::string_view filename, std::ostream & os) :
            filename_(filename), os_(os)
        {}
#if defined(_MSC_VER) || defined(BOOST_PARSER_DOXYGEN)
        /** This overload is Windows-only. */
        stream_error_handler(std::wstring_view filename) : os_(std::cout)
        {
            auto const r = text::as_utf8(filename);
            filename_.assign(r.begin(), r.end());
        }
        /** This overload is Windows-only. */
        stream_error_handler(std::wstring_view filename, std::ostream & os) :
            os_(os)
        {
            auto const r = text::as_utf8(filename);
            filename_.assign(r.begin(), r.end());
        }
#endif

        /** Handles a `parse_error` exception thrown during parsing.  A
            formatted parse-expectation failure is printed to `*os_` when
            `os_` is non-null, or `std::cout` otherwise.  Always returns
            `error_handler_result::fail`. */
        template<typename Iter, typename Sentinel>
        error_handler_result
        operator()(Iter first, Sentinel last, parse_error<Iter> const & e) const
        {
            parser::write_formatted_expectation_failure_error_message(
                os_, filename_, first, last, e);
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
            parser::write_formatted_message(
                os_, filename_, _begin(context), it, _end(context), message);
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

    private:
        std::string filename_;
        std::ostream & os_;
    };
}}

#endif
