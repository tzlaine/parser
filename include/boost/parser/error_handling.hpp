#ifndef BOOST_PARSER_ERROR_HANDLING_HPP
#define BOOST_PARSER_ERROR_HANDLING_HPP

#include <boost/parser/error_handling_fwd.hpp>
#include <boost/parser/detail/printing.hpp>

#include <boost/text/transcode_iterator.hpp>

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
        int64_t preferred_max_line_length,
        int64_t max_after_caret)
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
        detail::trace_input(os, first, it, false, 1u << 31);
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
        detail::trace_input(os, it, line_end, false, limit - i);

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
        int64_t preferred_max_line_length,
        int64_t max_after_caret)
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

        template<typename Context, typename Iter>
        void diagnose(
            diagnostic_kind kind,
            std::string_view message,
            Context const & context,
            Iter it) const
        {
            callback_type const & cb =
                kind == diagnostic_kind::error ? error_ : warning_;
            if (!cb)
                return;
            std::stringstream ss;
            parser::write_formatted_message(
                ss, filename_, _begin(context), it, _end(context), message);
            cb(ss.str());
        }

        template<typename Context>
        void diagnose(
            diagnostic_kind kind,
            std::string_view message,
            Context const & context) const
        {
            diagnose(kind, message, context, _where(context).begin());
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
