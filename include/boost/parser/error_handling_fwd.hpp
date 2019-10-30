#ifndef BOOST_PARSER_ERROR_HANDLING_FWD_HPP
#define BOOST_PARSER_ERROR_HANDLING_FWD_HPP

#include <iostream>


namespace boost { namespace parser {

    enum class error_handler_result { fail, rethrow };

    // Contains an iterator to the point of failure, and the name of the
    // failed parser or rule in what().
    template<typename Iter>
    struct parse_error : std::runtime_error
    {
        parse_error(Iter it, std::string const & msg) :
            runtime_error(msg),
            iter(it)
        {}

        Iter iter;
    };

    template<typename Iter>
    struct line_position
    {
        Iter line_start;
        int64_t line_number;
        int64_t column_number;
    };

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

    template<typename Iter>
    std::ostream & write_formatted_expectation_failure_error_message(
        std::ostream & os,
        std::string_view filename,
        Iter first,
        Iter last,
        parse_error<Iter> const & e,
        int64_t preferred_max_line_length = 80,
        int64_t max_after_caret = 40);

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

        template<typename Iter>
        error_handler_result
        operator()(Iter first, Iter last, parse_error<Iter> const & e) const
        {
            std::ostream & os = os_ ? *os_ : std::cout;
            write_formatted_expectation_failure_error_message(
                os, filename_, first, last, e);
            return error_handler_result::fail;
        }

        std::string_view filename_;
        std::ostream * os_;
    };

}}

#endif
