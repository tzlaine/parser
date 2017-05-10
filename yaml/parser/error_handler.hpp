/**
 *   Copyright (C) 2010, 2011 Object Modeling Designs : consultomd.com
 *   Copyright (c) 2010 Joel de Guzman
 *   Copyright (C) 2017 Zach Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef YAML_PARSER_ERROR_HANDLER_HPP
#define YAML_PARSER_ERROR_HANDLER_HPP

#include <yaml/parser/parser_fwd.hpp>

#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/support_line_pos_iterator.hpp>

#include <string>
#include <sstream>


namespace yaml { namespace parser {

    struct error_handler_t
    {
        template <typename, typename, typename, typename>
        struct result { using type = void; };

        error_handler_t (
            std::string const& source_file,
            reporting_fn_t const & errors,
            reporting_fn_t const & warnings
        )
            : source_file_ (source_file)
            , error_fn_ (errors)
            , warning_fn_ (warnings)
        {}

        void report_error (std::string const & msg) const
        {
            // TODO: This really needs file:line:col, regardless of source (ie
            // not just when (*this)() is called).
            if (error_fn_)
                error_fn_(msg);
            else
                throw parse_error(msg);
        }

        void report_warning (std::string const & msg) const
        {
            // TODO: This really needs file:line:col, regardless of source (ie
            // not just when (*this)() is called).
            if (warning_fn_)
                warning_fn_(msg);
        }

        void operator() (
            iterator_t first,
            iterator_t last,
            iterator_t err_pos,
            boost::spirit::info const & what
        ) const {
            iterator_t line_start = boost::spirit::get_line_start(first, err_pos);
            std::string error_line;
            if (line_start != last && *line_start == '\r')
                ++line_start;
            if (line_start != last && *line_start == '\n')
                ++line_start;
            for (iterator_t it = line_start; it != last; ++it) {
                typename iterator_t::value_type c = *it;
                if (c == '\r' || c == '\n')
                    break;
                error_line += c;
            }

            typename iterator_t::position_t const pos = err_pos.get_position();
            int const line = pos.line;
            int const column = pos.column;

            std::ostringstream oss;

            if (source_file_ == "")
                oss << "<Unknown source>:";
            else
                oss << source_file_ << ':';

            oss << line << ':' << column << ": error: ";

            if (what.tag == "anchors")
                oss << "The anchor referenced by this alias is not yet defined:\n";
            else
                oss << "Expected " << what << ":\n";

            oss << error_line << '\n';
            for (int i = 1; i != column; ++i) {
                oss << ' ';
            }

            oss << "^\n";

            report_error(oss.str());
        }

    private:
        std::string source_file_;
        std::function<void (std::string const &)> error_fn_;
        std::function<void (std::string const &)> warning_fn_;
    };

} }

#endif
