#ifndef BOOST_PARSER_ERROR_HANDLING_HPP
#define BOOST_PARSER_ERROR_HANDLING_HPP

#include <boost/text/utf8.hpp>

#include <array>
#include <functional>
#include <iostream>
#include <sstream>


namespace boost { namespace parser {

    namespace detail {

        // All the line break code points from the Unicode Line Break
        // Algorithm; see https://unicode.org/reports/tr14.
        constexpr std::array<int, 7> eol_cps = {
            {0x000a, 0x000b, 0x000c, 0x000d, 0x0085, 0x2028, 0x2029}};

        constexpr int eol_cp_mask =
            0x000a | 0x000b | 0x000c | 0x000d | 0x0085 | 0x2028 | 0x2029;
    }



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
    line_position<Iter> find_line_position(Iter first, Iter it)
    {
        bool prev_cr = false;
        auto retval = line_position<Iter>{first, 0, 0};
        for (Iter pos = first; pos != it; ++pos) {
            auto const c = *pos;
            bool const found =
                (c & detail::eol_cp_mask) == c &&
                std::find(detail::eol_cps.begin(), detail::eol_cps.end(), c) !=
                    detail::eol_cps.end();
            if (found) {
                retval.line_start = std::next(pos);
                retval.column_number = 0;
            } else {
                ++retval.column_number;
            }
            if (found && (!prev_cr || c != 0x000a))
                ++retval.line_number;
            prev_cr = c == 0x000d;
        }
        return retval;
    }

    template<typename Iter>
    Iter find_line_end(Iter it, Iter last)
    {
        return std::find_if(it, last, [](auto c) {
            return (c & detail::eol_cp_mask) == c &&
                   std::find(
                       detail::eol_cps.begin(), detail::eol_cps.end(), c) !=
                       detail::eol_cps.end();
        });
    }

    template<typename Iter>
    std::ostream & write_formatted_message(
        std::ostream & os,
        std::string_view filename,
        Iter first,
        Iter it,
        Iter last,
        std::string_view message,
        int64_t preferred_max_line_length = 80,
        int64_t max_after_caret = 40)
    {
        if (!filename.empty())
            os << filename << ':';
        auto const position = find_line_position(first, it);
        os << (position.line_number + 1) << ':' << position.column_number
           << ": " << message << " here";
        if (it == last)
            os << " (end of input)";
        os << ":\n";

        std::string underlining(std::distance(first, it), ' ');
        if constexpr (sizeof(*first) == 4) {
            for (auto it2 = text::utf8::make_from_utf32_iterator(
                          first, first, it),
                      end = text::utf8::make_from_utf32_iterator(first, it, it);
                 it2 != end;
                 ++it2) {
                os << *it2;
            }
        } else {
            for (Iter it2 = first; it2 != it; ++it2) {
                os << *it2;
            }
        }
        if (it == last) {
            os << '\n' << underlining << "^\n";
            return os;
        }

        underlining += '^';

        int64_t const limit = (std::max)(
            preferred_max_line_length,
            (int64_t)underlining.size() + max_after_caret);

        int64_t i = (int64_t)underlining.size();
        auto const line_end = find_line_end(std::next(it), last);
        if constexpr (sizeof(*first) == 4) {
            for (auto it2 = text::utf8::make_from_utf32_iterator(
                          it, it, line_end),
                      end = text::utf8::make_from_utf32_iterator(
                          it, line_end, line_end);
                 i < limit && it2 != end;
                 ++it2) {
                os << *it2;
            }
        } else {
            for (Iter it2 = it; i < limit && it2 != line_end; ++it2) {
                os << *it2;
            }
        }

        os << '\n' << underlining << '\n';

        return os;
    }


    template<typename Iter>
    std::ostream & write_formatted_expectation_failure_error_message(
        std::ostream & os,
        std::string_view filename,
        Iter first,
        Iter last,
        parse_error<Iter> const & e,
        int64_t preferred_max_line_length = 80,
        int64_t max_after_caret = 40)
    {
        std::string message = "error: Expected ";
        message += e.what();
        return write_formatted_message(
            os,
            filename,
            first,
            e.iter,
            last,
            message,
            preferred_max_line_length,
            max_after_caret);
    }

    struct default_error_handler
    {
        default_error_handler() : os_(std::cerr) {}
        default_error_handler(std::string_view filename) :
            filename_(filename),
            os_(std::cerr)
        {}
        default_error_handler(std::string_view filename, std::ostream & os) :
            filename_(filename),
            os_(os)
        {}

        template<typename Iter>
        error_handler_result
        operator()(Iter first, Iter last, parse_error<Iter> const & e) const
        {
            write_formatted_expectation_failure_error_message(
                os_, filename_, first, last, e);
            return error_handler_result::fail;
        }

        std::string_view filename_;
        std::ostream & os_;
    };

    struct callback_error_handler
    {
        using callback_type = std::function<void(std::string const &)>;

        callback_error_handler() {}
        callback_error_handler(
            callback_type error,
            callback_type warning = callback_type(),
            std::string_view filename = "") :
            error_(error),
            warning_(warning),
            filename_(filename)
        {}

        template<typename Iter>
        error_handler_result
        operator()(Iter first, Iter last, parse_error<Iter> const & e) const
        {
            if (error_) {
                std::stringstream ss;
                write_formatted_expectation_failure_error_message(
                    ss, filename_, first, last, e);
                error_(ss.str());
            }
            return error_handler_result::fail;
        }

        template<typename Iter>
        void
        warn(Iter first, Iter it, Iter last, std::string_view message) const
        {
            if (!warning_)
                return;
            std::stringstream ss;
            write_formatted_message(ss, filename_, first, it, last, message);
            warning_(ss.str());
        }

        callback_type error_;
        callback_type warning_;
        std::string_view filename_;
    };

    struct rethrow_error_handler
    {
        template<typename Iter>
        error_handler_result
        operator()(Iter first, Iter last, parse_error<Iter> const & e) const
        {
            return error_handler_result::rethrow;
        }
    };

}}

#endif
