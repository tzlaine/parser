/**
 *   Copyright (C) 2010, 2011 Object Modeling Designs : consultomd.com
 *   Copyright (c) 2010 Joel de Guzman
 *   Copyright (C) 2017 Zach Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_YAML_PARSER_ERROR_HANDLER_HPP
#define BOOST_YAML_PARSER_ERROR_HANDLER_HPP

#include <boost/yaml/parser/parser_fwd.hpp>

#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/support_line_pos_iterator.hpp>

#include <string>
#include <sstream>


namespace boost { namespace yaml { namespace parser {

    struct error_handler_impl_t;

    struct scoped_multipart_error_t
    {
        scoped_multipart_error_t (error_handler_impl_t & error_handler)
            : error_handler_ (error_handler)
        {}
        ~scoped_multipart_error_t ();

        error_handler_impl_t & error_handler_;
        std::ostringstream oss_;
    };

    struct error_handler_impl_t
    {
        template <typename, typename, typename, typename>
        struct result { using type = void; };

        void report_error (std::string const & msg) const
        {
            std::ostringstream oss;
            format_error(first_, last_, *current_, msg, oss);
            if (error_fn_)
                error_fn_(oss.str());
            else
                throw parse_error(oss.str());
        }

        void report_error_at (
            iterator_t at,
            std::string const & msg,
            scoped_multipart_error_t & multipart
        ) const {
            format_error(first_, last_, at, msg, multipart.oss_);
        }

        void report_warning_at (iterator_t at, std::string const & msg) const
        {
            std::ostringstream oss;
            format_warning(at, msg, oss);
            if (warning_fn_)
                warning_fn_(oss.str());
        }

        void operator() (
            iterator_t first,
            iterator_t last,
            iterator_t err_pos,
            boost::spirit::info const & what
        ) const {
            std::ostringstream oss;
            format_error(first, last, err_pos, what, what.tag, oss);
            if (error_fn_)
                error_fn_(oss.str());
            else
                throw parse_error(oss.str());
        }

        std::pair<std::string, int> format_prefix (
            iterator_t first,
            iterator_t last,
            iterator_t err_pos,
            bool error,
            std::ostringstream & oss
        ) const {
            iterator_t line_start = boost::spirit::get_line_start(first, err_pos);
            std::pair<std::string, int> retval;
            if (line_start != last && *line_start == '\r')
                ++line_start;
            if (line_start != last && *line_start == '\n')
                ++line_start;
            for (iterator_t it = line_start; it != last; ++it) {
                typename iterator_t::value_type c = *it;
                if (c == '\r' || c == '\n')
                    break;
                retval.first += c;
            }

            typename iterator_t::position_t const pos = err_pos.get_position();
            int const line = pos.line;
            int const column = pos.column;
            retval.second = column;

            if (source_file_ == "")
                oss << "<Unknown source>:";
            else
                oss << source_file_ << ':';

            oss << line << ':' << column << ": " << (error ? "error" : "warning") << ": ";

            return retval;
        }

        template <typename What>
        void format_error (
            iterator_t first,
            iterator_t last,
            iterator_t err_pos,
            What const & what,
            std::string const & tag,
            std::ostringstream & oss
        ) const {
            auto error_line_and_column = format_prefix(first, last, err_pos, true, oss);

            if (tag == "anchors")
                oss << "The anchor referenced by this alias is not yet defined:\n";
            else
                oss << "Expected " << what << ":\n";

            oss << error_line_and_column.first << '\n';
            for (int i = 1; i != error_line_and_column.second; ++i) {
                oss << ' ';
            }

            oss << "^\n";
        }

        void format_error (
            iterator_t first,
            iterator_t last,
            iterator_t err_pos,
            std::string const & msg,
            std::ostringstream & oss
        ) const {
            auto error_line_and_column = format_prefix(first, last, err_pos, true, oss);

            oss << msg;

            oss << error_line_and_column.first << '\n';
            for (int i = 1; i != error_line_and_column.second; ++i) {
                oss << ' ';
            }

            oss << "^\n";
        }

        void format_warning (iterator_t at, std::string const & msg, std::ostringstream & oss) const
        {
            auto error_line_and_column = format_prefix(first_, last_, at, false, oss);

            oss << msg << ":\n";

            oss << error_line_and_column.first << '\n';
            for (int i = 1; i != error_line_and_column.second; ++i) {
                oss << ' ';
            }

            oss << "^\n";
        }

        iterator_t first_;
        iterator_t last_;
        iterator_t * current_;
        std::string source_file_;
        std::function<void (std::string const &)> error_fn_;
        std::function<void (std::string const &)> warning_fn_;
    };

    struct error_handler_t
    {
        void operator() (
            iterator_t first,
            iterator_t last,
            iterator_t err_pos,
            boost::spirit::info const & what
        ) const {
            (*impl_)(first, last, err_pos, what);
        }

        error_handler_impl_t & impl () const
        { return *impl_; }

        boost::shared_ptr<error_handler_impl_t> impl_;
    };

    inline error_handler_t make_error_handler ()
    {
        error_handler_t retval;
        retval.impl_ = boost::shared_ptr<error_handler_impl_t>(new error_handler_impl_t);
        return retval;
    }

    inline scoped_multipart_error_t::~scoped_multipart_error_t ()
    {
        if (error_handler_.error_fn_)
            error_handler_.error_fn_(oss_.str());
        else
            throw parse_error(oss_.str());
    }

}}}

#endif
